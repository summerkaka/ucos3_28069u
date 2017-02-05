/*
*********************************************************************************************************
*                                            EXAMPLE CODE
*
*                          (c) Copyright 2009-2015; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           APPLICATION CODE
*
*                                             Delfino 28335
*                                                on the
*                                             TMDSDOCK28335
*                                            Experimenter Kit
*
* Filename      : app.c
* Version       : V1.00
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/


#include  <ucos_ii.h>
#include  <cpu_core.h>
#include  <lib_def.h>

#include "app_include.h"


/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                            LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

CPU_STK_SIZE  App_TaskStartStk[APP_CFG_TASK_STK_SIZE];      /* Start Task's stack.            */
CPU_STK_SIZE  App_TaskPendStk[APP_CFG_TASK_STK_SIZE];       /* Ping Task's stack.             */
CPU_STK_SIZE  App_TaskPostStk[APP_CFG_TASK_STK_SIZE];       /* Pong Task's stack.             */
CPU_STK_SIZE  App_TaskI2cThreadStk[APP_CFG_TASK_STK_SIZE];      // i2c
CPU_STK_SIZE  App_TaskEepromThreadStk[APP_CFG_TASK_STK_SIZE];   // eeprom
CPU_STK_SIZE  App_TaskUsbRxStk[APP_CFG_TASK_USB_STK_SIZE];      // usbtx
CPU_STK_SIZE  App_TaskUsbTxStk[APP_CFG_TASK_USB_STK_SIZE];      // usbrx

OS_EVENT        *AppTaskObjSem;

// i2c thread mutex, sem
OS_EVENT        *I2cServerRunSem, *I2cIdleSem, *I2cOverSem;
OS_EVENT        *I2cTcbMutex;

// usb msg queue
OS_EVENT        *pUsbRxQ;
OS_EVENT        *pUsbTxQ;
void            *UsbRxQTb[APP_CFG_USBTXQ_NUM];
void            *UsbTxQTb[APP_CFG_USBRXQ_NUM];

// usb msg partition
OS_MEM          *pUsbPartition;
INT8U           UsbPartition[APP_CFG_USBRXQ_NUM + APP_CFG_USBTXQ_NUM][APP_CFG_PARTITION_SIZE];  // 5 x 256

// eeprom
OS_EVENT        *pEepromQ;
OS_EVENT        *EromIdleSem, *EromOverSem;
void            *EepromQTb[APP_CFG_EROMQ_NUM];

// task queue
OS_EVENT        *pTaskQ;
void            *TaskQTb[APP_CFG_TASKQ_NUM];

// general partition
OS_MEM          *pTaskPartition;
INT8U           TaskPartition[APP_CFG_TASKQ_NUM][APP_CFG_PARTITION_SIZE];  // 10 x 256


/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/
                                                                /* Start Task.*/
static  void  App_TaskStart(void  *p_arg);
                                                                /* Ping Task. */
static  void  App_TaskPing (void  *p_arg);
                                                                /* Pong Task. */
static  void  App_TaskPong (void  *p_arg);


/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none.
*
* Returns     : none.
*
* Note(s)     : (1) This main is called by c_int00 which is itself called by BSP_RAM_StartHere when
*                   loading from the debugger.
*********************************************************************************************************
*/

int  main (void)
{
                                                                /* Initialize the CPU and Board.                        */
    CPU_Init();
    BSP_Init();
                                                                /* Initialize "uC/OS-II, The Real-Time Kernel".         */
    OSInit();

                                                                /* Create the Start task.                               */
    OSTaskCreateExt(App_TaskStart,
                    (void    *)0,
                    (CPU_STK *)&App_TaskStartStk[0],
                    (INT8U    )APP_CFG_TASK_START_PRIO,
                    (INT16U   )APP_CFG_TASK_START_PRIO,
                    (CPU_STK *)&App_TaskStartStk[APP_CFG_TASK_STK_SIZE - 1u],
                    (INT32U   )APP_CFG_TASK_STK_SIZE,
                    (void    *)0,
                    (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

                                                                /* Start multitasking (i.e. give control to uC/OS-II).  */
    OSStart();

                                                                /* Should never get here.                               */
    while (DEF_TRUE) {
        ;
    }
}


/*
*********************************************************************************************************
*                                            App_TaskStart()
*
* Description : First task to be scheduled. Creates the application tasks.
*
* Argument(s) : p_arg       the argument passed by 'OSTaskCreateExt()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*
* Note(s)     : (1) This task creates the application task. The application is a simple LED blinking
*                   demo where LD1 and LD4 blink at a 4:3 polyrhythm.
*********************************************************************************************************
*/

static  void  App_TaskStart (void *p_arg)
{
    CPU_INT08U  os_err;
                                                                /* Prevent compiler warning for not using 'p_arg'       */
   (void)&p_arg;

                                                                /* Clear the LEDs.                                      */
    BSP_LED_Off(BSP_LED_ALL);
                                                                /* Start the Ticker.                                    */
    BSP_Tick_Init();

    USB_Bulk_Init();

                                                                /* I2c related application                              */
    I2cServerRunSem = OSSemCreate(0);
    I2cIdleSem = OSSemCreate(1);
    I2cOverSem = OSSemCreate(0);
    I2cTcbMutex = OSMutexCreate(2, &os_err);

    OSTaskCreateExt(I2c_Thread,
                    (void    *)0,
                    (CPU_STK *)&App_TaskI2cThreadStk[0],
                    (INT8U    )APP_CFG_TASK_I2C_PRIO,
                    (INT16U   )APP_CFG_TASK_I2C_PRIO,
                    (CPU_STK *)&App_TaskI2cThreadStk[APP_CFG_TASK_STK_SIZE - 1u],
                    (INT32U   )APP_CFG_TASK_STK_SIZE,
                    (void    *)0,
                    (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

                                                                /* eeprom related application                           */
    pEepromQ = OSQCreate(&EepromQTb[0], APP_CFG_EROMQ_NUM);
    EromIdleSem = OSSemCreate(1);
    EromOverSem = OSSemCreate(0);

    OSTaskCreateExt(Eeprom_Thread,
                    (void    *)0,
                    (CPU_STK *)&App_TaskEepromThreadStk[0],
                    (INT8U    )APP_CFG_TASK_EROM_PRIO,
                    (INT16U   )APP_CFG_TASK_EROM_PRIO,
                    (CPU_STK *)&App_TaskEepromThreadStk[APP_CFG_TASK_STK_SIZE - 1u],
                    (INT32U   )APP_CFG_TASK_STK_SIZE,
                    (void    *)0,
                    (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));


                                                                /* Create the Ping task.                                */
    AppTaskObjSem = OSSemCreate(0);

    OSTaskCreateExt(App_TaskPing,
                    (void    *)0,
                    (CPU_STK *)&App_TaskPendStk[0],
                    (INT8U    )APP_CFG_TASK_PEND_PRIO,
                    (INT16U   )APP_CFG_TASK_PEND_PRIO,
                    (CPU_STK *)&App_TaskPendStk[APP_CFG_TASK_STK_SIZE - 1u],
                    (INT32U   )APP_CFG_TASK_STK_SIZE,
                    (void    *)0,
                    (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

                                                                /* Create the Pong task.                                */
    OSTaskCreateExt(App_TaskPong,
                    (void    *)0,
                    (CPU_STK *)&App_TaskPostStk[0],
                    (INT8U    )APP_CFG_TASK_POST_PRIO,
                    (INT16U   )APP_CFG_TASK_POST_PRIO,
                    (CPU_STK *)&App_TaskPostStk[APP_CFG_TASK_STK_SIZE - 1u],
                    (INT32U   )APP_CFG_TASK_STK_SIZE,
                    (void    *)0,
                    (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

                                                                /* UsbRx related application.                           */
    pUsbRxQ = OSQCreate(&UsbRxQTb[0], APP_CFG_USBRXQ_NUM);

    pUsbPartition = OSMemCreate(UsbPartition,
                                APP_CFG_USBRXQ_NUM + APP_CFG_USBRXQ_NUM,
                                APP_CFG_PARTITION_SIZE,
                                &os_err);

    OSTaskCreateExt(App_TaskUsbRx,
                    (void    *)0,
                    (CPU_STK *)&App_TaskUsbRxStk[0],
                    (INT8U    )APP_CFG_TASK_USBRX_PRIO,
                    (INT16U   )APP_CFG_TASK_USBRX_PRIO,
                    (CPU_STK *)&App_TaskUsbRxStk[APP_CFG_TASK_USB_STK_SIZE - 1u],
                    (INT32U   )APP_CFG_TASK_USB_STK_SIZE,
                    (void    *)0,
                    (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

                                                                /* UsbTx related application                            */
    pUsbTxQ = OSQCreate(&UsbTxQTb[0], APP_CFG_USBTXQ_NUM);

    OSTaskCreateExt(App_TaskUsbTx,
                    (void    *)0,
                    (CPU_STK *)&App_TaskUsbTxStk[0],
                    (INT8U    )APP_CFG_TASK_USBTX_PRIO,
                    (INT16U   )APP_CFG_TASK_USBTX_PRIO,
                    (CPU_STK *)&App_TaskUsbTxStk[APP_CFG_TASK_USB_STK_SIZE - 1u],
                    (INT32U   )APP_CFG_TASK_USB_STK_SIZE,
                    (void    *)0,
                    (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

    pTaskQ = OSQCreate(&TaskQTb[0], APP_CFG_TASKQ_NUM);

    pTaskPartition = OSMemCreate(TaskPartition, APP_CFG_TASKQ_NUM, APP_CFG_PARTITION_SIZE, &os_err);

                                                                /* All tasks should be written as an infinite loop.     */
    while (DEF_TRUE) {
        os_err = OSSemPost(AppTaskObjSem);
        OSTimeDlyHMSM(0, 0, 0, 1);
    }
}


/*
*********************************************************************************************************
*                                            App_TaskPing()
*
* Description : 'Ping' task, toggles LD1.
*
* Argument(s) : p_arg       the argument passed by 'OSTaskCreateExt()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*********************************************************************************************************
*/

static  void  App_TaskPing (void *p_arg)
{
    CPU_INT08U  os_err;
                                                                /* Prevent compiler warning for not using 'p_arg'       */
   (void)&p_arg;

                                                                /* Task body, always written as an infinite loop.       */
    while (DEF_TRUE) {
        OSSemPend( AppTaskObjSem,
                   0,
                  &os_err);
    }
}


/*
*********************************************************************************************************
*                                            App_TaskPong)
*
* Description : 'Pong' task, toggles LD4.
*
* Argument(s) : p_arg       the argument passed by 'OSTaskCreateExt()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*********************************************************************************************************
*/

static  void  App_TaskPong (void *p_arg)
{
                                                                /* Prevent compiler warning for not using 'p_arg'       */
   (void)&p_arg;

                                                                /* Task body, always written as an infinite loop.       */
    while (DEF_TRUE) {
        OSTimeDlyHMSM(0, 0, 0, 300);
        BSP_LED_Toggle(BSP_LED_LD3);
    }
}

