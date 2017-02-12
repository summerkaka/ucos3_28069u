/*
 * usb_handler.h
 *
 *  Created on: 2017��1��31��
 *      Author: ZCTIAXIA
 */

#ifndef APP_USB_HANDLER_H_
#define APP_USB_HANDLER_H_


typedef struct {
    uint8_t Target;
    uint8_t Src;
    uint8_t Length;
    uint8_t CmdCl;
    uint8_t CmdNum;
    uint8_t Buffer[256]; // begin from pid, subid, devid....
} tMSG;


void App_TaskUsbRx (void  *p_arg);
void App_TaskUsbTx (void  *p_arg);


#endif /* APP_USB_HANDLER_H_ */
