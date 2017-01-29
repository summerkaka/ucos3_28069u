/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                             (c) Copyright 2015; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                         BOARD SUPPORT PACKAGE
*                                             uCOS-II LAYER
*
*                                             Delfino 28335
*                                                on the
*                                             TMDSDOCK28335
*                                            Experimenter Kit
*
* Filename      : bsp_os.h
* Version       : V1.00
* Programmer(s) : JFT
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_OS_PRESENT
#define  BSP_OS_PRESENT


/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/

#include  <ucos_ii.h>


/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   BSP_OS_MODULE
#define  BSP_OS_EXT
#else
#define  BSP_OS_EXT  extern
#endif


/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/
                                                                /* TIMER2 Registers.                                    */
#define  BSP_OS_TIMER2_ADDR_BASE                               (0x00000C10u)
#define  BSP_OS_TIMER2_TIM                      *((CPU_INT32U *)(BSP_OS_TIMER2_ADDR_BASE + 0x0))
#define  BSP_OS_TIMER2_PRD                      *((CPU_INT32U *)(BSP_OS_TIMER2_ADDR_BASE + 0x2))
#define  BSP_OS_TIMER2_TCR                      *((CPU_INT16U *)(BSP_OS_TIMER2_ADDR_BASE + 0x4))
#define  BSP_OS_TIMER2_TPR                      *((CPU_INT16U *)(BSP_OS_TIMER2_ADDR_BASE + 0x6))
#define  BSP_OS_TIMER2_TPRH                     *((CPU_INT16U *)(BSP_OS_TIMER2_ADDR_BASE + 0x7))

                                                                /* TIMER2 Register bits.                                */
#define  BSP_OS_TIMER2_TCR_TIF                                  0x8000u
#define  BSP_OS_TIMER2_TCR_TIE                                  0x4000u
#define  BSP_OS_TIMER2_TCR_FREE                                 0x0800u
#define  BSP_OS_TIMER2_TCR_SOFT                                 0x0400u
#define  BSP_OS_TIMER2_TCR_TRB                                  0x0020u
#define  BSP_OS_TIMER2_TCR_TSS                                  0x0010u

#define  BSP_OS_TIMER2_TPR_PSC_MASK                             0xFF00u
#define  BSP_OS_TIMER2_TPR_TDDR_MASK                            0x00FFu

#define  BSP_OS_TIMER2_TPRH_PSCH_MASK                           0xFF00u
#define  BSP_OS_TIMER2_TPRH_TDDRH_MASK                          0x00FFu


/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                                MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/


void  BSP_OS_TIMER2_TickInit   (CPU_INT32U  cnts);

void  BSP_OS_TIMER2_TickHandler(void);


/*
*********************************************************************************************************
*                                          CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of module include.                               */

