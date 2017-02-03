/*
 * I2C.h
 *
 *  Created on: 2015��5��14��
 *      Author: xiatian
 */

#ifndef SOURCE_I2C_H_
#define SOURCE_I2C_H_

#define ICMDR_NACK	0x8000
#define ICMDR_FREE	0x4000
#define ICMDR_STT	0x2000
#define ICMDR_STP	0x0800
#define ICMDR_MST	0x0400
#define ICMDR_TRX	0x0200
#define ICMDR_XA	0x0100
#define ICMDR_RM	0x0080
#define ICMDR_DLB	0x0040
#define ICMDR_IRS	0x0020
#define ICMDR_STB	0x0010
#define ICMDR_FDF	0x0008

#define ERROR_TRYTIMES  5

#define ICFLAG_ADDR16   0x0001
#define ICFLAG_ADDRSENT 0x0002

extern Uint16 I2cBuffer[];

extern struct I2CMSG *g_pI2cMsg;

void I2c_Init(void);
__interrupt void i2c_int1a_isr(void);
void I2c_Thread(void *p_arg);

#endif /* SOURCE_I2C_H_ */
