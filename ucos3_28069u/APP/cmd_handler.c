/*
 * cmd_handler.c
 *
 *  Created on: Feb 4, 2017
 *      Author: xiatian
 */

#include "os_include.h"
#include "app_include.h"




void
App_CmdHandler(void *p_arg)
{
    CPU_INT08U  os_err;
    tMSG *cmd;
                                                                /* Prevent compiler warning for not using 'p_arg'       */
   (void)&p_arg;

                                                                /* Task body, always written as an infinite loop.       */
    while (DEF_TRUE) {
        cmd = (tMSG *)OSQPend( pTaskQ, 0, &os_err );

        if (cmd->target != 0x19) {
            // convey msg to CAN bus
            continue;
        }

        switch (cmd->cmdnum) {
        case 0x15 : // descriptor
            descriptor_handler(cmd);
            SendUsbMsg(cmd);
            OSMemPut(pPartition256, (void *)cmd);       // return partition applied in UsbRx
            break;
        case 0x20: // changer
            changer_handler(cmd);
            OSMemPut(pPartition256, (void *)cmd);
            break;
        default : break;
        }
    }
}
