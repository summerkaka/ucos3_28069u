/*
 * cmd_handler.h
 *
 *  Created on: Feb 4, 2017
 *      Author: xiatian
 */

#ifndef APP_CMD_HANDLER_H_
#define APP_CMD_HANDLER_H_

typedef enum {
    EROM_READ,
    EROM_WRITE
} kEromOps;

typedef struct {
    kEromOps   operation;
    Uint8      length;
    Uint8      dev_addr;
    Uint16     reg_addr;
    Uint8      buffer[128];  // no larger than eeprom bank size
} tEepromTask;

void Eeprom_Thread(void *p_arg);


#endif /* APP_CMD_HANDLER_H_ */
