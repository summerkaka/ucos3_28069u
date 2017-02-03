/*
 * I2C.c
 *
 *  Created on: 2015��5��14��
 *      Author: xiatian
 */

#include "os_include.h"
#include "app_include.h"

static INT8U I2c_Server(void);
__interrupt void i2c_int1a_isr(void);

static Uint16 I2C_err;

#if 0
// Global variables
struct I2CMSG g_I2cMsg={I2C_MSGSTAT_INACTIVE,
						  0,
						  0,
                          0x0000,
                          0x0000,
						  0x0000,
						  0x0000,
						 };

void I2cMsg_Reset(void)
{
    Uint16 i = 0;
    g_I2cMsg.ErrNum = 0;
    g_I2cMsg.NackNum = 0;
    g_I2cMsg.DevAddr = 0;
    g_I2cMsg.RegAddr.all = 0;
    g_I2cMsg.LongRegAddrFlag = 0;
    g_I2cMsg.Status = I2C_MSGSTAT_INACTIVE;
    g_I2cMsg.Len = 0;
    g_I2cMsg.pBuf = I2cBuffer;
    for (i=0; i < I2C_MAX_BUFFER_SIZE; i++){
        g_I2cMsg.pBuf[i] = 0;
    }
}
#endif

struct I2CMSG *g_pI2cMsg;
Uint16 I2cBuffer[I2C_MAX_BUFFER_SIZE];

void
StartI2cTask(struct I2CMSG *tcb)
{
    INT8U os_err;

    OSSemPend(I2cOverSem, 0, &os_err);

    OSMutexPend(I2cTcbMutex, 0, &os_err);
    g_pI2cMsg = tcb;
    OSMutexPost(I2cTcbMutex);

    OSSemPost(I2cRunSem);
}

void I2c_Init(void)
{
	// Initialize I2C
	I2caRegs.I2CSAR = 0x0000;		// Slave address - EEPROM control code

	I2caRegs.I2CPSC.all = 8;		// Prescaler - need 7-12 Mhz on module clk
	I2caRegs.I2CCLKL = 10;			// NOTE: must be non zero
	I2caRegs.I2CCLKH = 5;			// NOTE: must be non zero
	I2caRegs.I2CIER.all = 0x3C;		// 0011 1100,Enable SCD & ARDY & XRDY & RRDY interrupts

	I2caRegs.I2CMDR.all = ICMDR_IRS;	// Take I2C out of reset
										// Stop I2C when suspended

	I2caRegs.I2CFFTX.all = 0x0000;	// Enable FIFO mode and TXFIFO
	I2caRegs.I2CFFRX.all = 0x0000;	// Enable RXFIFO, clear RXFFINT,
}

static Uint16
I2CA_WriteData(struct I2CMSG *msg)
{
	if (I2caRegs.I2CMDR.bit.STP == 1) {  // STP is automatically cleared after the STOP condition has been generated.
		return I2C_STP_NOT_READY_ERROR;
	}
	// Setup slave address
	I2caRegs.I2CSAR = msg->DevAddr;
	// Check if bus busy
	if (I2caRegs.I2CSTR.bit.BB == 1) {
		return I2C_BUS_BUSY_ERROR;
	}
	if (msg->LongRegAddrFlag == true) {
		I2caRegs.I2CCNT = msg->Len + 2; // Data and MemoryLowAddr,MemoryHighAddr (total times for writing DXR reg)
		I2caRegs.I2CDXR = msg->RegAddr.Bytes.H_byte;
	}else if (msg->LongRegAddrFlag == false) {
		I2caRegs.I2CCNT = msg->Len + 1;
		I2caRegs.I2CDXR = msg->RegAddr.Bytes.L_byte;
	}
	I2caRegs.I2CMDR.all = ICMDR_STT | ICMDR_STP | ICMDR_MST | ICMDR_TRX | ICMDR_IRS;
	return I2C_SUCCESS;
}

static Uint16
I2CA_ReadData(struct I2CMSG *msg)
{
	if (I2caRegs.I2CMDR.bit.STP == 1) {  // STP is automatically cleared after the STOP condition has been generated
		return I2C_STP_NOT_READY_ERROR;
	}
	I2caRegs.I2CSAR = msg->DevAddr;
	if (msg->Status == I2C_MSGSTAT_SEND_NOSTOP) {
		// Check if bus busy
		if (I2caRegs.I2CSTR.bit.BB == 1) {
			return I2C_BUS_BUSY_ERROR;
		}
		I2caRegs.I2CCNT = (msg->LongRegAddrFlag)? 2:1;  // Write MemoryHighAddr and MemoryLowAddr
		I2caRegs.I2CDXR = (msg->LongRegAddrFlag)? msg->RegAddr.Bytes.H_byte : msg->RegAddr.Bytes.L_byte;
		I2caRegs.I2CMDR.all = ICMDR_STT | ICMDR_MST | ICMDR_TRX | ICMDR_IRS;
	}else if (msg->Status == I2C_MSGSTAT_RESTART) {
		I2caRegs.I2CCNT = msg->Len;		// Setup how many bytes to expect
		I2caRegs.I2CMDR.all = ICMDR_STT | ICMDR_MST | ICMDR_STP | ICMDR_IRS;
	}
	return I2C_SUCCESS;
}

void
I2c_Thread(void *p_arg)
{
	INT8U os_err;

	(void)&p_arg;

    while (DEF_TRUE) {
	    OSSemPend(I2cRunSem,
	              0,
	              &os_err);

	    if (!I2c_Server())            // return I2C_MSGSTAT_INACTIVE
	        OSSemPost(I2cOverSem);
	}
}

static INT8U
I2c_Server()
{
    if (g_pI2cMsg->Status == I2C_MSGSTAT_INACTIVE) {
		return I2C_MSGSTAT_INACTIVE;
	}

	// write event
	if (g_pI2cMsg->Status == I2C_MSGSTAT_SEND_WITHSTOP) {
		I2C_err = I2CA_WriteData(g_pI2cMsg);
		if (I2C_err == I2C_SUCCESS){
			//g_pI2cMsg = &I2cMsg;
		    g_pI2cMsg->Status = I2C_MSGSTAT_WRITE_BUSY;
		}
	}

	// read event
	if (g_pI2cMsg->Status == I2C_MSGSTAT_SEND_NOSTOP) {
		// EEPROM address setup portion
		while (I2CA_ReadData(g_pI2cMsg) != I2C_SUCCESS) {
			//TODO call canbus nack
		    g_pI2cMsg->ErrNum++;
			if (g_pI2cMsg->ErrNum >= ERROR_TRYTIMES) {
				//I2cMsg_Reset();
				return I2C_MSGSTAT_INACTIVE;
			}
		}
		g_pI2cMsg->Status = I2C_MSGSTAT_SEND_NOSTOP_BUSY;
	}else if (g_pI2cMsg->Status == I2C_MSGSTAT_RESTART) {
		// Read data portion
		while (I2CA_ReadData(g_pI2cMsg) != I2C_SUCCESS) {
			// call CAN_NACK after try number of times,
		    g_pI2cMsg->ErrNum++;
			if (g_pI2cMsg->ErrNum >= ERROR_TRYTIMES) {
				//I2cMsg_Reset();
				return I2C_MSGSTAT_INACTIVE;
			}
		}
		g_pI2cMsg->Status = I2C_MSGSTAT_READ_BUSY;
	}
	return g_pI2cMsg->Status;
}

__interrupt void i2c_int1a_isr(void)     // I2C-A
{
    CPU_SR_ALLOC();

    CPU_CRITICAL_ENTER();
    OSIntEnter();                                           /* Tell uC/OS-II that we are starting an ISR              */
    CPU_CRITICAL_EXIT();

    Uint16 IntSource;

    // Read interrupt source
    IntSource = I2caRegs.I2CISRC.all;

    // stop condition interrupt
    if (IntSource == I2C_SCD_ISRC)
    {
        g_pI2cMsg->NackNum = 0;
        // If completed message was writing data, reset msg to inactive state
        if (g_pI2cMsg->Status == I2C_MSGSTAT_WRITE_BUSY){
            g_pI2cMsg->Status = I2C_MSGSTAT_INACTIVE;
        }else{
            if (g_pI2cMsg->Status == I2C_MSGSTAT_SEND_NOSTOP_BUSY) {
                g_pI2cMsg->Status = I2C_MSGSTAT_SEND_NOSTOP;
            }else if (g_pI2cMsg->Status == I2C_MSGSTAT_READ_BUSY) {
                g_pI2cMsg->Status = I2C_MSGSTAT_INACTIVE;
            }
        }
    }

    // ardy interrupt,
    // In the nonrepeat mode (RM = 0 in I2CMDR): If STP = 0 in I2CMDR, the ARDY bit is set when the internal data counter counts down to 0.
    else if (IntSource == I2C_ARDY_ISRC)
    {
        if (I2caRegs.I2CSTR.bit.NACK == 1) {
            I2caRegs.I2CMDR.bit.STP = 1;
            I2caRegs.I2CSTR.all = I2C_CLR_NACK_BIT;
            //TODO call canbus nack
            g_pI2cMsg->NackNum++;
            if (g_pI2cMsg->NackNum >= ERROR_TRYTIMES) {
                //I2cMsg_Reset();  // Reset status after several times of NACK
                g_pI2cMsg->Status = I2C_MSGSTAT_INACTIVE;
            }
        }else if (g_pI2cMsg->Status == I2C_MSGSTAT_SEND_NOSTOP_BUSY) {
            g_pI2cMsg->Status = I2C_MSGSTAT_RESTART;
        }
    }

    // tx interrupt
    else if(IntSource == I2C_TX_ISRC)
    {
        if (g_pI2cMsg->LongRegAddrFlag == true) {
            I2caRegs.I2CDXR = g_pI2cMsg->RegAddr.Bytes.L_byte;
            g_pI2cMsg->LongRegAddrFlag = false;
        }
        else
            I2caRegs.I2CDXR = *(g_pI2cMsg->pBuf++);
    }

    // rx interrupt
    else if(IntSource == I2C_RX_ISRC)
    {
        *(g_pI2cMsg->pBuf++) = I2caRegs.I2CDRR;
    }

    else
    {
        // Generate some error due to invalid interrupt source
        __asm("   ESTOP0");
    }

                                                            /* Re-enable the interrupt.                               */
    BSP_IntAck(BSP_INT_ID_INT8_1);
    BSP_IntEn(BSP_INT_ID_INT8_1);
    OSIntExit();

    OSSemPost(I2cRunSem);
}

