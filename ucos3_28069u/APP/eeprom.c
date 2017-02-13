/*
 * eeprom.c
 *
 *  Created on: Feb 12, 2017
 *      Author: xiatian
 */

#include "os_include.h"
#include "app_include.h"

void
Eeprom_Thread(void *p_arg)
{
    INT8U os_err;
    struct I2CMSG i2ctcb;
    tEepromTask *erom;

    (void)&p_arg;

    while (DEF_TRUE) {

        erom = (tEepromTask *)OSQPend(pEepromQ, 0, &os_err);

        i2ctcb.DevAddr = erom->dev_addr;
        i2ctcb.Len = erom->length;
        i2ctcb.LongRegAddrFlag = true;
        i2ctcb.RegAddr.all = erom->reg_addr;
        i2ctcb.NackNum = 0;
        i2ctcb.ErrNum = 0;
        i2ctcb.pBuf = erom->buffer;

        if (erom->operation == EROM_READ) {       // read
            i2ctcb.Status = I2C_MSGSTAT_SEND_NOSTOP;
        }
        else if (erom->operation == EROM_WRITE) {  // write
            i2ctcb.Status = I2C_MSGSTAT_SEND_WITHSTOP;
        }

        StartI2cTask(&i2ctcb);

        OSSemPend(I2cOverSem, 0, &os_err);  // wait for i2c operate finish

        OSSemPost(EromOverSem);
    }
}
