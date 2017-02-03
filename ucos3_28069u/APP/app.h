/*
 * app.h
 *
 *  Created on: 2017��1��31��
 *      Author: ZCTIAXIA
 */

#ifndef APP_APP_H_
#define APP_APP_H_



extern OS_EVENT        *pUsbMsgQ;
extern OS_EVENT        *pTaskQ;
extern OS_MEM          *pUsbPartition;
extern OS_MEM          *pTaskPartition;

extern OS_EVENT        *I2cRunSem;
extern OS_EVENT        *I2cOverSem;
extern OS_EVENT        *I2cTcbMutex;

#endif /* APP_APP_H_ */
