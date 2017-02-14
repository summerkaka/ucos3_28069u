/*
 * usb_handler.h
 *
 *  Created on: 2017��1��31��
 *      Author: ZCTIAXIA
 */

#ifndef APP_USB_HANDLER_H_
#define APP_USB_HANDLER_H_


typedef struct {
    uint8_t target;
    uint8_t src;
    uint8_t length;
    uint8_t cmdCl;
    uint8_t cmdnum;
    uint8_t buffer[256]; // begin from pid, subid, devid....
} tMSG;


void    UsbPrintf       (char *pdata, Uint8 length);
INT8U   SendUsbMsg      (tMSG *msg);
void    App_TaskUsbRx   (void  *p_arg);
void    App_TaskUsbTx   (void  *p_arg);


#endif /* APP_USB_HANDLER_H_ */
