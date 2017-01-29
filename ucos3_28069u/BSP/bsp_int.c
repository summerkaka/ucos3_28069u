/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                             (c) Copyright 2015; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                         BOARD SUPPORT PACKAGE
*
*                                             Delfino 28335
*                                                on the
*                                             TMDSDOCK28335
*                                            Experimenter Kit
*
* Filename      : bsp_int.c
* Version       : V1.00
* Programmer(s) : JFT
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define    BSP_INT_MODULE
#include  "bsp.h"

#include  <os.h>


/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/

#define BSP_INT_GROUP_SHIFT                               3u
#define BSP_INT_GROUPL_OFFSET                          0x04u
#define BSP_INT_GROUPH_OFFSET                          0x10u
#define BSP_INT_CHANNEL_MASK            DEF_BIT_FIELD(3u, 0u)


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
*                                           GLOBAL VARIABLES
*********************************************************************************************************
*/
                                                                /* Set address to 0x000D00 with linker script.         */
#pragma DATA_SECTION(__BSP_VectorTable, "pie_vram");
CPU_FNCT_VOID  __BSP_VectorTable[BSP_INT_SRC_NBR];


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              BSP_IntAck()
*
* Description : Acknowledge interrupt.
*
* Argument(s) : int_id      Interrupt to acknowledge.
*
* Return(s)   : none.
*
* Caller(s)   : ISRs.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntAck (CPU_DATA  int_id)
{
    CPU_DATA  group;


    if ((int_id > BSP_INT_ID_RESET) &&
        (int_id < BSP_INT_SRC_NBR)) {

        if (int_id <= BSP_INT_ID_INT12) {                       /* Int between [BSP_INT_ID_INT1, BSP_INT_ID_INT12]      */
            group = int_id - 1;
        } else if (int_id <= BSP_INT_ID_USER12) {               /* Int between [BSP_INT_ID_INT13, BSP_INT_ID_USER12]    */
            return;
#if BSP_INT_SRC_NBR <= 128u
        } else {                                                /* Int between [BSP_INT_ID_INT1_1, BSP_INT_ID_INT12_8]  */
#else
        } else if (int_id <= BSP_INT_ID_INT12_8) {
#endif
            group = (int_id >> BSP_INT_GROUP_SHIFT) - (BSP_INT_GROUPL_OFFSET);
#if BSP_INT_SRC_NBR <= 128u
        }
#else
        } else {                                                /* Int above    BSP_INT_ID_INT12_8                      */
            group = (int_id >> BSP_INT_GROUP_SHIFT) - (BSP_INT_GROUPH_OFFSET);
        }
#endif
        BSP_PIE_ACK |= (1u << group);
        BSP_IntEn(group + 1);
    }
}


/*
*********************************************************************************************************
*                                              BSP_IntEn()
*
* Description : Enables interrupt source.
*
* Argument(s) : int_id      Interrupt source to enable.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntEn (CPU_DATA  int_id)
{
    CPU_DATA  group;
    CPU_DATA  channel;
    CPU_SR_ALLOC();


    if (int_id < BSP_INT_SRC_NBR) {

        if (int_id <= BSP_INT_ID_RTOSINT) {                     /* Int between [0, BSP_INT_ID_RTOSINT]                  */
        	CPU_IntSrcEn(int_id);

        } else if (int_id <= BSP_INT_ID_USER12) {               /* Int between [BSP_INT_ID_EMUINT, BSP_INT_ID_USER12]   */
            return;
#if BSP_INT_SRC_NBR <= 128u
        } else {                                                /* Int between [BSP_INT_ID_INT1_1, BSP_INT_ID_INT12_8]  */
#else
        } else if (int_id <= BSP_INT_ID_INT12_8) {
#endif
            CPU_CRITICAL_ENTER();
            group   = (int_id >> BSP_INT_GROUP_SHIFT) - (BSP_INT_GROUPL_OFFSET);
            channel = (int_id & BSP_INT_CHANNEL_MASK);

            BSP_PIE_IER_BASE[group << 1] |= (1u << channel);
            CPU_CRITICAL_EXIT();
#if BSP_INT_SRC_NBR <= 128u
        }
#else
        } else {                                                /* Int above    BSP_INT_ID_INT12_8                      */
            CPU_CRITICAL_ENTER();
            group   = (int_id >> BSP_INT_GROUP_SHIFT) - (BSP_INT_GROUPH_OFFSET);
            channel = (int_id & BSP_INT_CHANNEL_MASK);

            BSP_PIE_IER_BASE[group << 1] |= (8u << channel);
            CPU_CRITICAL_EXIT();
        }
#endif
    }
}


/*
*********************************************************************************************************
*                                             BSP_IntDis()
*
* Description : Disables interrupt source.
*
* Argument(s) : int_id      Interrupt source to disable.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntDis (CPU_DATA  int_id)
{
    CPU_DATA  group;
    CPU_DATA  channel;
    CPU_SR_ALLOC();


    if (int_id < BSP_INT_SRC_NBR) {

        if (int_id <= BSP_INT_ID_RTOSINT) {                     /* Int between [0, BSP_INT_ID_RTOSINT]                  */
        	CPU_IntSrcDis(int_id);

        } else if (int_id <= BSP_INT_ID_USER12) {               /* Int between [BSP_INT_ID_EMUINT, BSP_INT_ID_USER12]   */
            return;
#if BSP_INT_SRC_NBR <= 128u
        } else {                                                /* Int between [BSP_INT_ID_INT1_1, BSP_INT_ID_INT12_8]  */
#else
        } else if (int_id <= BSP_INT_ID_INT12_8) {
#endif
            CPU_CRITICAL_ENTER();
            group   = (int_id >> BSP_INT_GROUP_SHIFT) - (BSP_INT_GROUPL_OFFSET);
            channel = (int_id & BSP_INT_CHANNEL_MASK);

            BSP_PIE_IER_BASE[group << 1] &= ~(1u << channel);
            CPU_CRITICAL_EXIT();
#if BSP_INT_SRC_NBR <= 128u
        }
#else
        } else {                                                /* Int above    BSP_INT_ID_INT12_8                      */
            CPU_CRITICAL_ENTER();
            group   = (int_id >> BSP_INT_GROUP_SHIFT) - (BSP_INT_GROUPH_OFFSET);
            channel = (int_id & BSP_INT_CHANNEL_MASK);

            BSP_PIE_IER_BASE[group << 1] &= ~(8u << channel);
            CPU_CRITICAL_EXIT();
        }
#endif
    }
}


/*
*********************************************************************************************************
*                                             BSP_ExtIntEn()
*
* Description : Enables external interrupt source.
*
* Argument(s) : xint_id     External interrupt source to enable.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_ExtIntEn (CPU_DATA  xint_id)
{
    CPU_SR_ALLOC();


    if (xint_id <= BSP_XINT_ID_XNMI) {
        CPU_CRITICAL_ENTER();
        BSP_XINT_REG_BASE[xint_id] |= BSP_XINT_ENABLE;
        CPU_CRITICAL_EXIT();
    }
}


/*
*********************************************************************************************************
*                                            BSP_ExtIntDis()
*
* Description : Disables external interrupt source.
*
* Argument(s) : xint_id     External interrupt source to enable.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_ExtIntDis (CPU_DATA  xint_id)
{
    CPU_SR_ALLOC();


    if (xint_id <= BSP_XINT_ID_XNMI) {
        CPU_CRITICAL_ENTER();
        BSP_XINT_REG_BASE[xint_id] &= ~BSP_XINT_ENABLE;
        CPU_CRITICAL_EXIT();
    }
}


#if 0
                                                                /* TODO: BSP_ExtIntSetPol() BSP_ExtIntSetSrc()          */
/*
*********************************************************************************************************
*                                          BSP_ExtIntSetPol()
*
* Description : Set the external interrupt polarity.
*
* Argument(s) : xint_id     External interrupt.
*
*               pol         External interrupt polarity.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_ExtIntSetPol (CPU_DATA  xint_id,
                        CPU_DATA  pol)
{

}


/*
*********************************************************************************************************
*                                          BSP_ExtIntSetPol()
*
* Description : Set the external interrupt source.
*
* Argument(s) : xint_id     External interrupt.
*
*               src         External interrupt source.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  BSP_ExtIntSetSrc (CPU_DATA  xint_id,
                        CPU_DATA  src)
{

}
#endif


/*
*********************************************************************************************************
*                                           BSP_IntVectSet()
*
* Description : Assign ISR handler.
*
* Argument(s) : int_id      Interrupt for which vector will be set.
*
*               isr         Handler to assign
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntVectSet (CPU_DATA       int_id,
                      CPU_FNCT_VOID  isr)
{
    CPU_SR_ALLOC();


    if ((int_id > BSP_INT_ID_RESET) &&
        (int_id < BSP_INT_SRC_NBR)) {
        CPU_CRITICAL_ENTER();
    	__BSP_VectorTable[int_id] = isr;
    	CPU_CRITICAL_EXIT();
    }
}


/*
*********************************************************************************************************
*                                        BSP_IntHandlerDummy()
*
* Description : Dummy interrupt handler, serves as a template for other interrupt handlers.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

interrupt  void  BSP_IntHandlerDummy (void)
{
    CPU_INT32U  vector;
    CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();
    OSIntEnter();
    CPU_CRITICAL_EXIT();
                                                                /* If Interrupt passes through the PIE, it should be ...*/
                                                                /*  ... acknowledged with BSP_IntAck() here.            */
    vector   = BSP_PIE_CTRL & ~0x1;                             /* Get Vector Table Address. Mask LSB                   */
    vector  -= (CPU_INT32U)__BSP_VectorTable;                   /* Get Byte offset from start of table.                 */
    vector >>= 1;                                               /* Get interrupt source ID.                             */
    BSP_IntAck((CPU_DATA)vector);

    OSIntExit();
}

