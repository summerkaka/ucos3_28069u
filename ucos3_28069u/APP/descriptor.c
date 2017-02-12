/*
 * descriptor.c
 *
 *  Created on: Feb 12, 2017
 *      Author: xiatian
 */

#include "os_include.h"
#include "app_include.h"

//                           buffe: 0      1       2       3         4        5
// target src length cmdcl cmdnum  r/w   length devaddr regaddr_h regaddr_l payload

INT8U
descriptor_handler(tMSG *cmd)
{
    INT8U os_err;
    INT8U *mem_ptr;
    OS_EVENT *eromsem = OSSemCreate(0);
    tEepromTask erom_ops;

    erom_ops.length = cmd->Buffer[1];
    erom_ops.operation = (kEromOps)cmd->Buffer[0];
    erom_ops.dev_addr = cmd->Buffer[2];
    erom_ops.reg_addr = (cmd->Buffer[3] << 8) | (cmd->Buffer[4]);
    if (erom_ops.operation == EROM_WRITE) {
        memcpy(erom_ops.buffer, &cmd->Buffer[5], erom_ops.length);
    }

    mem_ptr = OSMemGet(pPartition256, &os_err);        // apply partition

    memcpy(mem_ptr, &erom_ops, sizeof(tEepromTask));    // copy msg to partition

    OSSemPend(EromIdleSem, 0, &os_err);             // wait for eeprom idle

    OSQPost(pEepromQ, (void*)mem_ptr);                  // post os_msg queue

    OSSemPend(EromOverSem, 0, &os_err);             // wait for eeprom r/w finish

    OSMemPut(pPartition256, (void *)mem_ptr);          // return partition
    //todo
    return 0;
}
