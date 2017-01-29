//###########################################################################
//
// FILE:   usb_bulk_structs.h
//
// TITLE:  USB Bulk device structure definitions.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V151 $
// $Release Date: February  2, 2016 $
// $Copyright: Copyright (C) 2011-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef __USB_BULK_STRUCTS_H__
#define __USB_BULK_STRUCTS_H__

//*****************************************************************************
//
// The size of the transmit and receive buffers used. 256 is chosen pretty
// much at random though the buffer should be at least twice the size of
// a maxmum-sized USB packet.
//
//*****************************************************************************
#define BULK_BUFFER_SIZE        256

//#define USB_PID_AXIO			0x0758
//#define USB_VID_AXIO			0x1001

#define USB_VID_AXIO			0x0758
#define USB_PID_AXIOLAB			0x6000
#define USB_PID_AXIOSCOPE		0x6001

extern uint32_t RxHandler(void *pvCBData, uint32_t ulEvent,
                               uint32_t ulMsgValue, void *pvMsgData);
extern uint32_t TxHandler(void *pvlCBData, uint32_t ulEvent,
                               uint32_t ulMsgValue, void *pvMsgData);

extern const tUSBBuffer g_sTxBuffer;
extern const tUSBBuffer g_sRxBuffer;
extern tUSBDBulkDevice g_sBulkDevice;
extern uint8_t g_pui8USBTxBuffer[];
extern uint8_t g_pui8USBRxBuffer[];

#endif // __USB_BULK_STRUCTS_H__
