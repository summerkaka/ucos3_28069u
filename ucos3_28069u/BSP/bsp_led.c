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
* Filename      : bsp_led.c
* Version       : V1.00
* Programmer(s) : JFT
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define    BSP_LED_MODULE
#include  "bsp.h"

#include  <os.h>
#include  "../include/F2806x_Device.h"

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
*                                           GLOBAL VARIABLES
*********************************************************************************************************
*/


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
*                                             BSP_LED_On()
*
* Description : Turns on a LED.
*
* Argument(s) : led         LED to turn on.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_On (CPU_DATA  led)
{
    switch (led) {
        case BSP_LED_ALL:
             GpioDataRegs.GPBCLEAR.bit.GPIO56 = 1;
             GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
             break;

        case BSP_LED_LD2:
             GpioDataRegs.GPBCLEAR.bit.GPIO56 = 1;
             break;

        case BSP_LED_LD3:
             GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
             break;

        default:                                                /* 'default' case intentionally empty.                  */
             break;
    }
}


/*
*********************************************************************************************************
*                                             BSP_LED_Off()
*
* Description : Turns off a LED.
*
* Argument(s) : led         LED to turn off.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Off (CPU_DATA  led)
{
    switch (led) {
        case BSP_LED_ALL:
             GpioDataRegs.GPBSET.bit.GPIO56 = 1;
             GpioDataRegs.GPASET.bit.GPIO2 = 1;
             break;

        case BSP_LED_LD2:
             GpioDataRegs.GPBSET.bit.GPIO56 = 1;
             break;

        case BSP_LED_LD3:
             GpioDataRegs.GPASET.bit.GPIO2 = 1;
             break;

        default:                                                /* 'default' case intentionally empty.                  */
             break;
    }
}


/*
*********************************************************************************************************
*                                            BSP_LED_Toggle()
*
* Description : Toggles the state of a a LED.
*
* Argument(s) : led         LED to toggle.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Toggle (CPU_DATA  led)
{
    switch (led) {
        case BSP_LED_ALL:
             GpioDataRegs.GPBTOGGLE.bit.GPIO56 = 1;
             GpioDataRegs.GPATOGGLE.bit.GPIO2 = 1;
             break;

        case BSP_LED_LD2:
             GpioDataRegs.GPBTOGGLE.bit.GPIO56 = 1;
             break;

        case BSP_LED_LD3:
            GpioDataRegs.GPATOGGLE.bit.GPIO2 = 1;
             break;

        default:                                                /* 'default' case intentionally empty.                  */
             break;
    }
}

