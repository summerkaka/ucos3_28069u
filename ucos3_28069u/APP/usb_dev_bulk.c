//###########################################################################
//
// FILE:    usb_dev_bulk.c
//
// TITLE:   F2806x USB Bulk Device Example.
//
// ASSUMPTIONS:
//
//    This program requires:
//        - the F2806x header files 
//        - Driverlib (/ControlSUITE/device_support/f2806x/version/MWare/
//                                      driverlib/Debug/driverlib.lib)
//        - Usblib (/ControlSUITE/device_support/f2806x/version/MWare/
//                                      lib/usblib.lib)
//        - USB Capable F2806x
//
// Description:
//
//! \addtogroup f2806x_example_list
//! <h1>USB Generic Bulk Device (usb_dev_bulk)</h1>
//!
//! This example provides a generic USB device offering simple bulk data
//! transfer to and from the host.  The device uses a vendor-specific class ID
//! and supports a single bulk IN endpoint and a single bulk OUT endpoint.
//! Data received from the host is assumed to be ASCII text and it is
//! echoed back with the case of all alphabetic characters swapped.
//!
//! UART0, connected to the FTDI virtual COM port and running at 115,200,
//! 8-N-1, is used to display messages from this application.
//!
//! A Windows INF file for the device is provided on the installation CD.  This
//! INF contains information required to install the WinUSB subsystem on
//! WindowsXP and Vista PCs.  WinUSB is a Windows subsystem allowing user mode
//! applications to access the USB device without the need for a
//! vendor-specific kernel mode driver.
//!
//! A sample Windows command-line application, usb_bulk_example, illustrating
//! how to connect to and communicate with the bulk device is also provided.
//! Project files are included to allow the examples to be built using Microsoft
//! VisualStudio.  Source code for this application can be found in directory
//! MWare/tools/usb_bulk_example.
//
//  Section .ebss was initialized to 0x0000 in
//  F2806x_CodeStartBranch_ebss_init.asm. This was to ensure that all global
//  variables of the usblib are initialized to 0x0000 on the F2806x.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V151 $ 
// $Release Date: February  2, 2016 $ 
// $Copyright: Copyright (C) 2011-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "os_include.h"
#include "app_include.h"


#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ulLine)
{
}
#endif

uint8_t MsgIndex = 0;
bool HeaderFlag = false;
bool DLEflag = false;
//UsbRingBuf UsbRxBuffer;

void
USB_Init(void)
{
    // Enable Device Mode
    HWREG(USBMODESEL) = USBMODESEL_DEV;
    HWREG(USB0_BASE + USB_O_GPCS) = USBGPCS_DEV;
    //Enable PHY
    GpioCtrlRegs.GPACTRL2.bit.USB0IOEN = 1;
}

void
USB_Bulk_Init(void)
{
    USBBufferInit(&g_sTxBuffer);
    USBBufferInit(&g_sRxBuffer);
    USBDBulkInit(0, &g_sBulkDevice);
    // Wait for initial configuration to complete.
    //UARTprintf("Waiting for host...\n");
}

#if 0
static void
UsbRingBufInit(void)
{
    //uint8_t i = 0;
    UsbRxBuffer.ReadIndex = 0;
    UsbRxBuffer.WriteIndex = 0;
    memset(UsbRxBuffer.Buffer, 0, BULK_BUFFER_SIZE);
    //for (i = 0; i < BULK_BUFFER_SIZE; i++)
        //UsbRxBuffer.Buffer[i] = 0;
}
#endif


/* ****************************************************************************
 * Usb message handler
 * ****************************************************************************/
static uint32_t
MsgHandler(tUSBDBulkDevice *psDevice, uint8_t *pcData,
                  uint32_t ulNumBytes)
{
    uint32_t ulLoop = ulNumBytes;
    uint32_t ulCount = ulLoop;
    uint32_t ulReadIndex = (uint32_t)(pcData - g_pui8USBRxBuffer);
    INT8U os_err, write_index, *buffer;

    if (ulReadIndex > 255)
        return ulCount;

    if (HeaderFlag == false) {
        do {
            if (g_pui8USBRxBuffer[ulReadIndex] == 0x10) {
                if (DLEflag) {
                    ulReadIndex = (++ulReadIndex == BULK_BUFFER_SIZE) ? 0 : ulReadIndex;
                    DLEflag = false;
                    continue;
                }
                if ( (g_pui8USBRxBuffer[ulReadIndex + 1] == 0x02 && ulReadIndex != 255) ||
                        (g_pui8USBRxBuffer[0] == 0x02 && ulReadIndex == 255) ) {
                    HeaderFlag = true;
                    break;
                }else {
                    ulReadIndex = (++ulReadIndex == BULK_BUFFER_SIZE) ? 0 : ulReadIndex;
                    DLEflag = true;
                }
            }else {
                ulReadIndex = (++ulReadIndex == BULK_BUFFER_SIZE) ? 0 : ulReadIndex;
            }
        } while (ulLoop--);
    }

    if (HeaderFlag) {
        buffer = OSMemGet(pPartition256, &os_err);         // allocate memory to store usb msg
        write_index = 1;

        while (ulLoop--) {
            buffer[write_index++] = g_pui8USBRxBuffer[ulReadIndex++];
            ulReadIndex = (ulReadIndex == BULK_BUFFER_SIZE) ? 0 : ulReadIndex;
        }
        if (write_index > 255) {
            MsgIndex = 0;
            HeaderFlag = false;
            return ulCount;
        }
        if (buffer[write_index - 2] == 0x10 && buffer[write_index - 1] == 0x03) {
            //todo use counter to judge eof
            if ( buffer[write_index - 3] != 0x10 ||
                    (buffer[write_index - 3] == 0x10 && buffer[write_index - 4] == 0x10) ) {
                buffer[0] = write_index;                  // 1st byte is the data length

                OSQPost(pUsbRxQ, (void*)buffer);                  // post os_msg queue

                MsgIndex = 0;
                HeaderFlag = false;
            }
        }else {
            MsgIndex++;
        }
    }
    return ulCount;
}

//*****************************************************************************
//
// Handles bulk driver notifications related to the transmit channel (data to
// the USB host).
//
// \param pvCBData is the client-supplied callback pointer for this channel.
// \param ulEvent identifies the event that has been sent.
// \param ulMsgValue is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the bulk driver to notify us of any events
// related to operation of the transmit data channel (the IN channel carrying
// data to the USB host).
//
// \return The return value is event-specific.
//
//*****************************************************************************
uint32_t
TxHandler(void *pvCBData, uint32_t ulEvent, uint32_t ulMsgValue,
          void *pvMsgData)
{
    //
    // No action is required in response to any transmit event in this example.
    // All that is done is to update the transmit counter.
    //
    if(ulEvent == USB_EVENT_TX_COMPLETE)
    {
        ;//g_ulTxCount += ulMsgValue;
    }

    return(0);
}

//*****************************************************************************
//
// Handles bulk driver notifications related to the receive channel (data from
// the USB host).
//
// \param pvCBData is the client-supplied callback pointer for this channel.
// \param ulEvent identifies the event that has been sent.
// \param ulMsgValue is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the bulk driver to notify us of any events
// related to operation of the receive data channel (the OUT channel carrying
// data from the USB host).
//
// \return The return value is event-specific.
//
//*****************************************************************************
uint32_t
RxHandler(void *pvCBData, uint32_t ulEvent, uint32_t ulMsgValue,
          void *pvMsgData)
{
    //
    // Which event was sent?
    //
    switch(ulEvent)
    {
    case USB_EVENT_CONNECTED:
    {
        //g_bUSBConfigured = true;
        //UARTprintf("Host connected.\n");

        USBBufferFlush(&g_sTxBuffer);
        USBBufferFlush(&g_sRxBuffer);

        break;
    }
    case USB_EVENT_DISCONNECTED:
    {
        //g_bUSBConfigured = false;
        //UARTprintf("Host disconnected.\n");
        break;
    }
    case USB_EVENT_RX_AVAILABLE:
    {
        tUSBDBulkDevice *psDevice;
        psDevice = (tUSBDBulkDevice *)pvCBData;
        return(MsgHandler(psDevice, pvMsgData, ulMsgValue));
    }
    case USB_EVENT_SUSPEND:
    case USB_EVENT_RESUME:
    {
        break;
    }
    default:
    {
        break;
    }
    }

    return(0);
}

