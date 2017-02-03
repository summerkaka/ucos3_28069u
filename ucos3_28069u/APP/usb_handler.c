/*
 * usb_handler.c
 *
 *  Created on: 2017��1��31��
 *      Author: ZCTIAXIA
 */

#include "os_include.h"
#include "app_include.h"



static uint8_t
MsgCoding(uint8_t *buffer, const uint8_t *origin, uint8_t origin_len)
{
    uint8_t write_index = 0;
    uint8_t read_index = 0;
    for (read_index = 0; read_index < origin_len; read_index++) {
        buffer[write_index] = *(origin + read_index);
        if (buffer[write_index] == 0x10) {
            buffer[++write_index] = 0x10;
        }
        if (buffer[write_index] == 0x0D) {
            buffer[write_index] = 0x10;
            buffer[++write_index] = 0x0D;
        }
        write_index++;
    }
    return write_index;
}


#if 0
INT8U
App_TaskUsbMsgProcess(void *p_arg)
{
    CPU_INT08U  os_err, *ptr;
                                                                /* Prevent compiler warning for not using 'p_arg'       */
   (void)&p_arg;

                                                                /* Task body, always written as an infinite loop.       */
    while (DEF_TRUE) {
        ptr = (INT8U *)OSQPend( pTaskQ, 0, &os_err );
        UsbTransmit(ptr);
    }
}
#endif


void
App_TaskUsbRx (void  *p_arg)
{
    CPU_INT08U  os_err;
    INT8U *cmd, *ptr, *msg_header, length, i, writeindex;
    INT8U buffer[BULK_BUFFER_SIZE];
                                                                /* Prevent compiler warning for not using 'p_arg'       */
   (void)&p_arg;

                                                                /* Task body, always written as an infinite loop.       */
    while (DEF_TRUE) {

        // wait for usbRx Queue available
        ptr = (INT8U *)OSQPend( pUsbMsgQ, 0, &os_err);


        // 1st byte is length
        length = *ptr - 4;

        // 3rd byte is tMSG header
        msg_header = ptr + 3;  // length, 0x10, 0x02, ...

        // store the usb msg to local buffer, decode CAN29 DLE
        i = 0;
        writeindex = 0;
        while(length--) {
            buffer[writeindex] = *(msg_header + i++);
            if (buffer[writeindex] == 0x10) {
                if(*(msg_header + i) == 0x10) { // 0x10 0x10
                    i++;
                    length--;
                }else if (*(msg_header + i) == 0x0D) { // 0x10 0x0d
                    buffer[writeindex] = 0x0D;
                    i++;
                    length--;
                }else if (*(msg_header + i + 1) != 0x02 && *(msg_header + i + 1) != 0x03) {
                    //todo send error report;   //msg has error, directly return
                }
            }
            writeindex = (++writeindex == BULK_BUFFER_SIZE) ? 0 : writeindex; // prevent overflow
        }

        // assign memory for task ongoing
        cmd = OSMemGet(pTaskPartition, &os_err);

        // copy data to this memory
        memcpy(cmd, buffer, i);

        // post TaskQueue
        OSQPost(pTaskQ, (void*)cmd);

        // return memory of UsbRx
        OSMemPut(pUsbPartition, (void *)ptr);
    }
}

void
App_TaskUsbTx (void  *p_arg)
{
    CPU_INT08U  os_err;
    INT8U i, length, buffer[BULK_BUFFER_SIZE];
    tMSG *msg;
    uint32_t ulSpace, ulWriteIndex;
    tUSBRingBufObject sTxRing;

                                                                /* Prevent compiler warning for not using 'p_arg'       */
   (void)&p_arg;

                                                                /* Task body, always written as an infinite loop.       */
    while (DEF_TRUE) {
        msg = (tMSG *)OSQPend( pTaskQ, 0, &os_err );
        buffer[0] = 0x10;
        buffer[1] = 0x02;
        length = MsgCoding((uint8_t *)(buffer + 2), (const uint8_t *)msg, msg->Length + 5) + 2;
        buffer[length++] = 0x10;
        buffer[length++] = 0x03;
#if DEBUG
        buffer[length++] = msg->Length;
        buffer[length++] = (uint32_t)msg >> 24;
        buffer[length++] = (uint32_t)msg >> 16;
        buffer[length++] = (uint32_t)msg >> 8;
        buffer[length++] = (uint32_t)msg;
#endif
        while (DEF_TRUE) {
            USBBufferInfoGet(&g_sTxBuffer, &sTxRing);
            ulSpace = USBBufferSpaceAvailable(&g_sTxBuffer);
            if (ulSpace >= length) {  // check if space available
                OSMemPut(pTaskPartition, (void *)msg);
                break;
            }
            OSTimeDlyHMSM(0, 0, 1, 0);
        }

        ulWriteIndex = sTxRing.ui32WriteIndex;
        for (i = 0; i < length; i++) {
            g_pui8USBTxBuffer[ulWriteIndex++] = buffer[i];
            ulWriteIndex = (ulWriteIndex == BULK_BUFFER_SIZE) ? 0 : ulWriteIndex;
        }
        USBBufferDataWritten(&g_sTxBuffer, length);
    }
}
