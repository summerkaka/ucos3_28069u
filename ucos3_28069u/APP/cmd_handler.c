/*
 * cmd_handler.c
 *
 *  Created on: Feb 4, 2017
 *      Author: xiatian
 */

#include "os_include.h"
#include "app_include.h"

INT8U
App_CmdHandler(void *p_arg)
{
    CPU_INT08U  os_err;
    tMSG *cmd;
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
