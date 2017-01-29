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
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define    BSP_OS_MODULE
#include  "../../bsp.h"
#include  "bsp_os.h"

#include  <cpu_core.h>
#include  <ucos_ii.h>


/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                        BSP_OS_TIMER2_TickInit()
*
* Description : Initialize TIMER2 to generate OS_CFG_TICK_RATE_HZ ticks per second.
*
* Argument(s) : cnts        Number of CPU ticks before one OS tick.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Tick_Init().
*
* Note(s)     : 1) This function MUST be called after OSStart() & after processor initialization.
*********************************************************************************************************
*/

void  BSP_OS_TIMER2_TickInit (CPU_INT32U  cnts)
{
                                                                /* Stop TIMER2.                                         */
    BSP_OS_TIMER2_TCR |= BSP_OS_TIMER2_TCR_TSS;
                                                                /* Set the Prescaler.                                   */
    BSP_OS_TIMER2_TPR  &= ~BSP_OS_TIMER2_TPR_PSC_MASK;
    BSP_OS_TIMER2_TPRH &= ~BSP_OS_TIMER2_TPRH_PSCH_MASK;
                                                                /* Set the Period.                                      */
    BSP_OS_TIMER2_PRD = cnts;
                                                                /* Set Debug mode.                                      */
    BSP_OS_TIMER2_TCR &= ~(BSP_OS_TIMER2_TCR_FREE | BSP_OS_TIMER2_TCR_SOFT);
                                                                /* Reload counter with period.                          */
    BSP_OS_TIMER2_TCR |= BSP_OS_TIMER2_TCR_TRB;
                                                                /* Enable TIMER2 interrupts.                            */
    BSP_OS_TIMER2_TCR |= BSP_OS_TIMER2_TCR_TIE;

    BSP_IntEn(BSP_INT_ID_INT14);
                                                                /* Start TIMER2.                                        */
    BSP_OS_TIMER2_TCR &= ~BSP_OS_TIMER2_TCR_TSS;
}


/*
*********************************************************************************************************
*                                      BSP_OS_TIMER2_TickHandler()
*
* Description : Handle the TIMER2 tick interrupt, which is used to generate the uC/OS-II tick.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : 1) This function MUST be placed in entry 14 (for INT14/TIMER2) of the C28x interrupt table.
*********************************************************************************************************
*/

interrupt  void  BSP_OS_TIMER2_TickHandler (void)
{
    CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();
    OSIntEnter();                                           /* Tell uC/OS-II that we are starting an ISR              */
    BSP_OS_TIMER2_TCR |= BSP_OS_TIMER2_TCR_TIF;
    CPU_CRITICAL_EXIT();

    OSTimeTick();                                           /* Call uC/OS-II's OSTimeTick()                           */

                                                            /* Re-enable the interrupt.                               */
    BSP_IntEn(BSP_INT_ID_INT14);
    OSIntExit();                                            /* Tell uC/OS-II that we are leaving the ISR              */
}

