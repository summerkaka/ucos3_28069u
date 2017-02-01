/*
 * usb_dev_bulk.h
 *
 *  Created on: 2017Äê1ÔÂ27ÈÕ
 *      Author: ZCTIAXIA
 */

#ifndef USB_DEV_BULK_H_
#define USB_DEV_BULK_H_

typedef struct {
    uint8_t WriteIndex;
    uint8_t ReadIndex;
    uint8_t Buffer[BULK_BUFFER_SIZE];
} UsbRingBuf;

void USB_Init(void);
void USB_Bulk_Init(void);

#endif /* USB_DEV_BULK_H_ */
