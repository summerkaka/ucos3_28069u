/*
 * usb_handler.c
 *
 *  Created on: 2017��1��31��
 *      Author: ZCTIAXIA
 */

#include "os_include.h"
#include "app_include.h"


/*
*********************************************************************************************************
*                                    SendUsbMsg()
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

    buffer = OSMemGet(pPartition256, &os_err);   // apply partition to store usb msg
    if (buffer == NULL)
        return 1;

    memcpy(buffer, cmd, cmd->Length + 5);       // target src len cmdcl cmdnum payload

    os_err = OSQPost(pUsbTxQ, (void*)buffer);   // post os_msg queue
    return os_err;
}


static uint8_t
MsgCoding(uint8_t *buffer, const uint8_t *origin, uint8_t origin_len)
{
    uint8_t write_index = 0;
    uint8_t read_index = 0;
    for (read_index = 0; read_index < origin_len; read_index++) {
        buffer[write_index] = *(origin + read_index);
        if (buffer[write_index] == 0x10) {
            buffer[++write_index] = 0x10;
        }
        if (buffer[write_index] == 0x0D) {
            buffer[write_index] = 0x10;
            buffer[++write_index] = 0x0D;
        }
        write_index++;
    }
    return write_index;
}

void
App_TaskUsbRx (void  *p_arg)
{
    CPU_INT08U  os_err;
    INT8U *msgq_ptr, *msg_header, length, readindex, writeindex;
    INT8U *buffer;
                                                                /* Prevent compiler warning for not using 'p_arg'       */
   (void)&p_arg;

                                                                /* Task body, always written as an infinite loop.       */
    while (DEF_TRUE) {

        // wait for usbRx Queue available
        msgq_ptr = (INT8U *)OSQPend( pUsbRxQ, 0, &os_err);

        // 1st byte is length
        length = *msgq_ptr - 5;     // remove length & sof & eof

        if (length > BULK_BUFFER_SIZE) {
            goto end;
        }

        // buffer for decoding message
        buffer = OSMemGet(pPartition256, &os_err);

        // 3rd byte is tMSG header
        msg_header = msgq_ptr + 3;  // length, 0x10, 0x02, ...

        // store the usb msg to local buffer, decode CAN29 DLE
        readindex = writeindex = 0;
        while(readindex < length) {
            buffer[writeindex] = *(msg_header + readindex++);
            if (buffer[writeindex] == 0x10) {
                if(*(msg_header + readindex) == 0x10) { // 0x10 0x10
                    readindex++;
                }else if (*(msg_header + readindex) == 0x0D) { // 0x10 0x0d
                    buffer[writeindex] = 0x0D;
                    readindex++;
                }else if (*(msg_header + readindex) != 0x02 && *(msg_header + readindex) != 0x03) {
                    // msg has error, directly return
                    goto end;
                }
            }
            writeindex++;
        }

        // post TaskQueue
        OSQPost(pTaskQ, (void*)buffer);

end:
        // return partition applied in MsgHandler()
        OSMemPut(pPartition256, (void *)msgq_ptr);
    }
}

void
App_TaskUsbTx (void  *p_arg)
{
    CPU_INT08U  os_err;
    INT8U i, length, buffer[BULK_BUFFER_SIZE];
    tMSG *msg;
    uint32_t ulSpace, ulWriteIndex;
    tUSBRingBufObject sTxRing;

                                                                /* Prevent compiler warning for not using 'p_arg'       */
   (void)&p_arg;

                                                                /* Task body, always written as an infinite loop.       */
    while (DEF_TRUE) {
        msg = (tMSG *)OSQPend( pUsbTxQ, 0, &os_err );

        buffer[0] = 0x10;
        buffer[1] = 0x02;
        length = MsgCoding((uint8_t *)(buffer + 2), (const uint8_t *)msg, msg->Length + 5) + 4;  // +4 is for all data with sof & eof
        buffer[length - 2] = 0x10;
        buffer[length - 1] = 0x03;
#if DEBUG
        buffer[length++] = msg->Length;
        buffer[length++] = (uint32_t)msg >> 24;
        buffer[length++] = (uint32_t)msg >> 16;
        buffer[length++] = (uint32_t)msg >> 8;
        buffer[length++] = (uint32_t)msg;
#endif
        while (DEF_TRUE) {
            USBBufferInfoGet(&g_sTxBuffer, &sTxRing);
            ulSpace = USBBufferSpaceAvailable(&g_sTxBuffer);
            if (ulSpace >= length) {  // check if space available
                OSMemPut(pPartition256, (void *)msg);
                break;
            }
            OSTimeDlyHMSM(0, 0, 0, 20);
        }

        ulWriteIndex = sTxRing.ui32WriteIndex;
        for (i = 0; i < length; i++) {
            g_pui8USBTxBuffer[ulWriteIndex++] = buffer[i];
            ulWriteIndex = (ulWriteIndex == BULK_BUFFER_SIZE) ? 0 : ulWriteIndex;
        }
        USBBufferDataWritten(&g_sTxBuffer, length);
    }
}
