/*
 * app.h
 *
 *  Created on: 2017��1��31��
 *      Author: ZCTIAXIA
 */

#ifndef APP_APP_H_
#define APP_APP_H_



extern OS_EVENT         *pUsbRxQ;
extern OS_EVENT         *pUsbTxQ;
extern OS_EVENT         *pTaskQ;
extern OS_MEM           *pUsbPartition;
extern OS_MEM           *pTaskPartition;

extern OS_EVENT         *I2cServerRunSem;
extern OS_EVENT         *I2cIdleSem;
extern OS_EVENT         *I2cOverSem;
extern OS_EVENT         *EromIdleSem;
extern OS_EVENT         *EromOverSem;
extern OS_EVENT         *I2cTcbMutex;

extern OS_EVENT         *pEepromQ;

#endif /* APP_APP_H_ */
