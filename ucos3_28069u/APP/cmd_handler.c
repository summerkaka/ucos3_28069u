/*
 * cmd_handler.c
 *
 *  Created on: Feb 4, 2017
 *      Author: xiatian
 */

#include "os_include.h"
#include "app_include.h"

/*
*********************************************************************************************************
*                                    DELAY TASK FOR SPECIFIED TIME
*
* Description: This function is called to answer commands
*
* Arguments  : *cmd     pointer to the command to answer
*
* Returns    :  0   success
*               1   fail
*
* Note(s)    :
*********************************************************************************************************
*/
INT8U
SendUsbMsg(tMSG *cmd)
{
    INT8U *buffer, os_err;

    buffer = OSMemGet(pPartition32, &os_err);   // allocate memory to store usb msg
    if (buffer == NULL)
        return 1;

    memcpy(buffer, cmd, cmd->Length + 5);       // target src len cmdcl cmdnum payload

    os_err = OSQPost(pUsbTxQ, (void*)buffer);   // post os_msg queue
    return os_err;
}


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

        if (cmd->Target != 0x19) {
            // convey msg to CAN bus
            continue;
        }

        switch (cmd->CmdNum) {
        case 0x15 : // descriptor
            descriptor_handler(cmd);
            SendUsbMsg(cmd);
            break;
        case 0x20: // changer
            changer_handler(cmd);
            break;
        default : break;
        }
    }
}
