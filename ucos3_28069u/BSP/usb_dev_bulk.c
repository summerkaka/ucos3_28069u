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


//#include "DSP28x_Project.h"
#include <stdbool.h>
//#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
//#include "inc/hw_ints.h"
//#include "driverlib/debug.h"
//#include "driverlib/interrupt.h"
//#include "driverlib/sysctl.h"
//#include "driverlib/systick.h"
//#include "driverlib/rom.h"
#include "usblib/usblib.h"
#include "usb.h"
//#include "usb_hal.h"
#include "inc/hw_usb.h"
//#include "usblib/usb-ids.h"
#include "usblib/device/usbdevice.h"
#include "usblib/device/usbdbulk.h"
//#include "utils/uartstdio.h"
#include "usb_bulk_structs.h"

#include "F2806x_Device.h"

//#include "include.h"


//*****************************************************************************
//
// The system tick rate expressed both as ticks per second and a millisecond
// period.
//
//*****************************************************************************
#define SYSTICKS_PER_SECOND     100
#define SYSTICK_PERIOD_MS       (1000 / SYSTICKS_PER_SECOND)

//*****************************************************************************
//
// The global system tick counter.
//
//*****************************************************************************
//volatile uint32_t g_ulSysTickCount = 0;

//*****************************************************************************
//
// Variables tracking transmit and receive counts.
//
//*****************************************************************************
//volatile uint32_t g_ulTxCount = 0;
//volatile uint32_t g_ulRxCount = 0;

//*****************************************************************************
//
// Global flag indicating that a USB configuration has been set.
//
//*****************************************************************************
//static volatile tBoolean g_bUSBConfigured = false;

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ulLine)
{
}
#endif

#if 0
//*****************************************************************************
//
// Interrupt handler for the system tick counter.
//
//*****************************************************************************
__interrupt void
SysTickIntHandler(void)
{
    //
    // Update our system tick counter.
    //
    g_ulSysTickCount++;
    PieCtrlRegs.PIEACK.all |= 1;
}
#endif

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


/* ****************************************************************************
 * Usb message handler
 * ****************************************************************************/
static uint32_t
MsgHandler(tUSBDBulkDevice *psDevice, uint8_t *pcData,
                  uint32_t ulNumBytes)
{
    uint32_t ulLoop, ulSpace, ulCount;
    uint32_t ulReadIndex;
    uint32_t ulWriteIndex;
    tUSBRingBufObject sTxRing;

    USBBufferInfoGet(&g_sTxBuffer, &sTxRing);
    ulSpace = USBBufferSpaceAvailable(&g_sTxBuffer);
    ulLoop = (ulSpace < ulNumBytes) ? ulSpace : ulNumBytes;
    ulCount = ulLoop;
    //g_ulRxCount += ulNumBytes;
    ulReadIndex = (uint32_t)(pcData - g_pui8USBRxBuffer);
    ulWriteIndex = sTxRing.ui32WriteIndex;

    while(ulLoop--)
    {
        if((g_pui8USBRxBuffer[ulReadIndex] >= 'a') &&
                (g_pui8USBRxBuffer[ulReadIndex] <= 'z'))
        {
            g_pui8USBTxBuffer[ulWriteIndex] =
                (g_pui8USBRxBuffer[ulReadIndex] - 'a') + 'A';
        }
        else
        {
            if((g_pui8USBRxBuffer[ulReadIndex] >= 'A') &&
                    (g_pui8USBRxBuffer[ulReadIndex] <= 'Z'))
            {
                g_pui8USBTxBuffer[ulWriteIndex] =
                    (g_pui8USBRxBuffer[ulReadIndex] - 'Z') + 'z';
            }
            else
            {
                g_pui8USBTxBuffer[ulWriteIndex] = g_pui8USBRxBuffer[ulReadIndex];
            }
        }

        ulWriteIndex++;
        ulWriteIndex = (ulWriteIndex == BULK_BUFFER_SIZE) ? 0 : ulWriteIndex;
        ulReadIndex++;
        ulReadIndex = (ulReadIndex == BULK_BUFFER_SIZE) ? 0 : ulReadIndex;
    }
    USBBufferDataWritten(&g_sTxBuffer, ulCount);
    return(ulCount);
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

#if 0
//*****************************************************************************
//
// This is the main application entry function.
//
//*****************************************************************************
int
main(void)
{
	//
    // Section .ebss was initialized to 0x0000 in
	// F2806x_CodeStartBranch_ebss_init.asm. This was to ensure that all global
	// variables of the usblib are initialized to 0x0000 on the F2806x.
	//

    uint32_t ulTxCount;
    uint32_t ulRxCount;


    //
    // Set the clocking to run from the PLL
    //
    //SysCtrlInit();
    Device_Init();

    //
    // Initialize interrupt controller and vector table
    //
    InitPieCtrl();
    InitPieVectTable();

    //
    // Enable Device Mode
    //
    EALLOW;
    HWREG(USBMODESEL) = USBMODESEL_DEV;
    HWREG(USB0_BASE + USB_O_GPCS) = USBGPCS_DEV;
    EDIS;

    //
    // Setup UART GPIOS and enable the UART.
    //
    EALLOW;
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;
    GpioCtrlRegs.GPADIR.bit.GPIO28 = 0;

    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO29 = 1;
    EDIS;

    UARTStdioInit(0);
    UARTprintf("\033[2JBulk device application\n");

    //
    // Not configured initially.
    //
    g_bUSBConfigured = false;

    //
    // Enable the system tick.
    //
    SysTickPeriodSet(SysCtlClockGet(SYSTEM_CLOCK_SPEED) /
    		SYSTICKS_PER_SECOND);
    SysTickIntEnable();
    SysTickEnable();

    //
    // Enable the GPIO peripheral used for USB, and configure the USB
    // pins.
    //
    USBGPIOEnable();

    //
    // Register Interrupt Handlers
    //
    IntRegister(INT_TINT0, SysTickIntHandler);
    USBIntRegister(USB0_BASE, f28x_USB0DeviceIntHandler);
    IntMasterEnable();

    //
    // Initialize the transmit and receive buffers.
    //
    USBBufferInit(&g_sTxBuffer);
    USBBufferInit(&g_sRxBuffer);

    //
    // Pass our device information to the USB library and place the device
    // on the bus.
    //
    USBDBulkInit(0, &g_sBulkDevice);

    //
    // Wait for initial configuration to complete.
    //
    UARTprintf("Waiting for host...\n");

    //
    // Clear our local byte counters.
    //
    ulRxCount = 0;
    ulTxCount = 0;

    //
    // Main application loop.
    //
    while(1)
    {
        //
        // See if any data has been transferred.
        //
        if((ulTxCount != g_ulTxCount) || (ulRxCount != g_ulRxCount))
        {
            //
            // Take a snapshot of the latest transmit and receive counts.
            //
            ulTxCount = g_ulTxCount;
            ulRxCount = g_ulRxCount;

            //
            // Update the display of bytes transferred.
            //
            UARTprintf("\rTx: %d  Rx: %d", ulTxCount, ulRxCount);
        }
    }
}
#endif

