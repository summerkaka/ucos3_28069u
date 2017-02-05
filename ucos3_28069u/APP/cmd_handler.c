/*
 * cmd_handler.c
 *
 *  Created on: Feb 4, 2017
 *      Author: xiatian
 */

#include "os_include.h"
#include "app_include.h"

//                           buffer 0      1       2       3         4         5
// target src length cmdcl cmdnum  r/w   length devaddr regaddr_h regaddr_l *payload

INT8U
descriptor_handler(tMSG *cmd)
{
    INT8U os_err;
    INT8U *ptr;
    OS_EVENT *eromsem = OSSemCreate(0);
    tEepromTask erom_ops;

    erom_ops.length = cmd->Buffer[0];
    erom_ops.operation = cmd->Buffer[1];
    erom_ops.dev_addr = cmd->Buffer[2];
    erom_ops.reg_addr = (cmd->Buffer[3] << 8) | (cmd->Buffer[4]);
    if (erom_ops.operation == EROM_WRITE) {
        memcpy(erom_ops.buffer, &cmd->Buffer[5], erom_ops.length);
    }

    ptr = OSMemGet(pTaskPartition, &os_err);        // apply partition

    memcpy(ptr, &erom_ops, sizeof(tEepromTask));    // copy msg to partition

    OSSemPend(EromIdleSem, 0, &os_err);             // wait for eeprom idle

    OSQPost(pEepromQ, (void*)ptr);                  // post os_msg queue

    OSSemPend(EromOverSem, 0, &os_err);             // wait for eeprom r/w finish

    OSMemPut(pTaskPartition, (void *)ptr);          // return partition
    //todo
}

void
Eeprom_Thread(void *p_arg)
{
    INT8U os_err;
    struct I2CMSG i2ctcb;
    tEepromTask *erom;
    INT8U requirement;  // 0: read with answer; 1: read without answer; 2: write with answer; 3: write without answer;
    INT8U *ptr;

    (void)&p_arg;

    while (DEF_TRUE) {
        OSSemPend(I2cIdleSem, 0, &os_err);
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
            requirement = 0;
        }
        else if (erom->operation == EROM_WRITE) {  // write
            i2ctcb.Status = I2C_MSGSTAT_SEND_WITHSTOP;
            requirement = 2;
        }

        StartI2cTask(&i2ctcb);
        OSSemPend(I2cOverSem, 0, &os_err);  // wait for i2c operate finish

        OSSemPost(EromOverSem);
        OSSemPost(EromIdleSem);
    }
}

INT8U
changer_handler(tMSG *cmd)
{

    return 0;
}




INT8U
App_CmdHandler(void *p_arg)
{
    CPU_INT08U  os_err;
    tMSG *cmd, *ptr;
                                                                /* Prevent compiler warning for not using 'p_arg'       */
   (void)&p_arg;

                                                                /* Task body, always written as an infinite loop.       */
    while (DEF_TRUE) {
        cmd = (tMSG *)OSQPend( pTaskQ, 0, &os_err );

        if (cmd->Target != 0x19) {
            // convey msg to CAN bus
            continue;
        }

        switch (cmd->CmdNum) {
        case 0x15 : // descriptor
            descriptor_handler(cmd);
            break;
        case 0x20: // changer
            changer_handler(cmd);
            break;
        default : break;
        }
    }
}
