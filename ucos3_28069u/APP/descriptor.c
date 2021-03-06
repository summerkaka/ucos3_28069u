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
    tEepromTask erom_ops;

    erom_ops.length = cmd->buffer[1];
    erom_ops.operation = (kEromOps)cmd->buffer[0];
    erom_ops.dev_addr = cmd->buffer[2];
    erom_ops.reg_addr = (cmd->buffer[3] << 8) | (cmd->buffer[4]);
    if (erom_ops.operation == EROM_WRITE) {
        memcpy(erom_ops.buffer, &cmd->buffer[5], erom_ops.length);
    }

    mem_ptr = OSMemGet(pPartition256, &os_err);         // apply partition

    memcpy(mem_ptr, &erom_ops, sizeof(tEepromTask));    // copy msg to partition

    OSQPost(pEepromQ, (void*)mem_ptr);                  // post os_msg queue

    OSSemPend(EromOverSem, 0, &os_err);                 // wait for eeprom r/w finish

    if (erom_ops.operation == EROM_READ) {              // make up answer msg
        memcpy(&cmd->buffer[5], ((tEepromTask *)mem_ptr)->buffer, erom_ops.length);
        cmd->length = 5 + erom_ops.length;
    }else if (erom_ops.operation == EROM_WRITE) {
        cmd->length = 5;
    }

    OSMemPut(pPartition256, (void *)mem_ptr);           // return partition

    return 0;
}
