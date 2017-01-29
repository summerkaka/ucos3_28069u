/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                             (c) Copyright 2014; Micrium, Inc.; Weston, FL
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
*
*                                             Delfino 28335
*                                                on the
*                                             TMDSDOCK28335
*                                            Experimenter Kit
*
* Filename      : bsp.c
* Version       : V1.00
* Programmer(s) : JFT
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define    BSP_MODULE
#include  "bsp.h"
#include  <bsp_os.h>

#include  <os.h>
#include  "../include/F2806x_Device.h"
#include  "driverlib/usb_hal.h"
#include  "usb_dev_bulk.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  BSP_Int_Init(void);

static  void  BSP_Gpio_Init(void);

static  void  BSP_PLL_Init(void);

static  void  BSP_PeripheralClock_Init(void);

static  void  BSP_Hardware_Init(void);


/*
*********************************************************************************************************
*                                             REGISTERS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            REGISTER BITS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/

#if ((CPU_CFG_TS_TMR_EN          != DEF_ENABLED) && \
     (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED) && \
     (OS_PROBE_HOOKS_EN          == 1))
#error  "CPU_CFG_TS_EN                  illegally #define'd in 'cpu.h'"
#error  "                              [MUST be  DEF_ENABLED] when    "
#error  "                               using uC/Probe COM modules    "
#endif


/*
*********************************************************************************************************
*                                               BSP_Init()
*
* Description : Initialize the Board Support Package (BSP).
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) This function SHOULD be called before any other BSP function is called.
*********************************************************************************************************
*/

void  BSP_Init (void)
{
                                                                /* Allow access to protected registers and regions.     */
    asm(" EALLOW");
                                                                /* Disable interrupts.                                  */
    CPU_IntDis();
                                                                /* Debugger can access registers and memory.            */
    asm(" CLRC DBGM");
                                                                /* Configure interrupts.                                */
    BSP_Int_Init();
                                                                /* Configure system clock.                              */
    BSP_PLL_Init();

    BSP_PeripheralClock_Init();

    BSP_Hardware_Init();
                                                                /* Initialize LEDs.                                     */
    BSP_Gpio_Init();

    CPU_IntEn();
}


/*
*********************************************************************************************************
*                                            BSP_Tick_Init()
*
* Description : Initialize all the peripherals that required OS Tick services (OS initialized)
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void BSP_Tick_Init (void)
{
#if (!defined(OS_CFG_DYN_TICK_EN) || (OS_CFG_DYN_TICK_EN != DEF_ENABLED))
    CPU_INT32U  cpu_clk_freq;
    CPU_INT32U  cnts;
#endif


#if (defined(OS_CFG_DYN_TICK_EN) && (OS_CFG_DYN_TICK_EN == DEF_ENABLED))
    BSP_OS_Dyn_TickInit();                                      /* Init uC/OS dynamic time source.                      */
#else
    cpu_clk_freq = BSP_CPU_ClkFreq();                           /* Determine TIMER2 reference freq.                     */

#if (OS_VERSION >= 30000u)
    cnts = cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz;        /* Determine nbr TIMER2 increments.                     */
#else
    cnts = cpu_clk_freq / (CPU_INT32U)OS_TICKS_PER_SEC;         /* Determine nbr TIMER2 increments.                     */
#endif
    BSP_OS_TIMER2_TickInit(cnts);                               /* Init uC/OS periodic time src (TIMER2).               */
#endif
}


/*
*********************************************************************************************************
*                                            BSP_CPU_ClkFreq()
*
* Description : Read CPU registers to determine the CPU clock frequency of the chip.
*
* Argument(s) : none.
*
* Return(s)   : The CPU clock frequency, in Hz.
*
* Caller(s)   : Application, BSP_Tick_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_ClkFreq (void)
{
  return ((CPU_INT32U)90000000UL);                             /* The board runs the CPU at 150 MHz.                   */
}


/*
*********************************************************************************************************
*                                             BSP_Int_Init()
*
* Description : Initializes the default vector table and moves it to PIE Vector RAM.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_Int_Init (void)
{
    CPU_DATA  intid;

                                                                /* Enable PIE. */
    BSP_PIE_CTRL |= BSP_PIE_CTRL_ENPIE;
                                                                /* Build vector table in PIE RAM.                       */
                                                                /*   Set Dummy Handler for all interrupts.              */
    for (intid = 1; intid < BSP_INT_SRC_NBR; ++intid) {
        BSP_IntVectSet(intid, BSP_IntHandlerDummy);
    }
                                                                /*   Set TIMER2 (Tick) Interrupt handler.               */
    BSP_IntVectSet(BSP_INT_ID_INT14  , BSP_OS_TIMER2_TickHandler);
                                                                /*   Set RTOSINT (Context Switch) Interrupt handler.    */
    BSP_IntVectSet(BSP_INT_ID_RTOSINT, OS_CPU_RTOSINT_Handler);

    //BSP_IntVectSet(BSP_INT_ID_INT8_1, i2c_int1a_isr);

    BSP_IntVectSet(BSP_INT_ID_INT5_8, f28x_USB0DeviceIntHandler);

    PieCtrlRegs.PIEIER5.bit.INTx8 = 1;      // Enable PIE Group 5 INT8  USB0 INT
    //PieCtrlRegs.PIEIER8.bit.INTx1 = 1;      // Enable PIE Group 8 INT1  I2CA NONE FIFO INT
    IER |= M_INT5;
}


/*
*********************************************************************************************************
*                                             BSP_LED_Init()
*
* Description : Initializes GPIO-A and GPIO-B to drive the four LEDs.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_Gpio_Init (void)
{
    GpioCtrlRegs.GPAMUX1.all = 0x0000;
    GpioCtrlRegs.GPAMUX2.all = 0x0000;
    GpioCtrlRegs.GPBMUX1.all = 0x0000;
    GpioCtrlRegs.GPBMUX2.all = 0x0000;
    GpioCtrlRegs.AIOMUX1.all = 0x0000;

    GpioCtrlRegs.GPADIR.all = 0x0000;
    GpioCtrlRegs.GPBDIR.all = 0x0000;
    GpioCtrlRegs.AIODIR.all = 0x0000;

    GpioCtrlRegs.GPAQSEL1.all = 0x0000;
    GpioCtrlRegs.GPAQSEL2.all = 0x0000;
    GpioCtrlRegs.GPBQSEL1.all = 0x0000;
    GpioCtrlRegs.GPBQSEL2.all = 0x0000;

    GpioCtrlRegs.GPAPUD.all = 0x0000;
    GpioCtrlRegs.GPBPUD.all = 0x0000;

    // GPIO-2 - LED Indicator on board
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;      // Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;     // 0=GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;      // 1=OUTput,  0=INput
    GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;      // uncomment if --> Set Low initially

    // GPIO-56 - LED INDICATOR on board
    GpioCtrlRegs.GPBPUD.bit.GPIO56 = 1;     // Disable pull-up
    GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 0;    // 0=GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO56 = 1;     // 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO56 = 1;     // uncomment if --> Set Low initially
}

/*
*********************************************************************************************************
*                                             BSP_PLL_Init()
*
* Description : Sets the core's operating frequency at (30 MHz*10)/2 = 150 MHz.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_PLL_Init (void)
{
    SysCtrlRegs.CLKCTL.bit.XCLKINOFF = 1;
    SysCtrlRegs.CLKCTL.bit.XTALOSCOFF = 0;
    SysCtrlRegs.CLKCTL.bit.OSCCLKSRC2SEL = 0;
    SysCtrlRegs.CLKCTL.bit.OSCCLKSRCSEL = 1;
                                                                /* Check if OSCCLK is missing.                          */
    while ((BSP_PLL_STS & BSP_PLL_STS_MCLKSTS) > 0u) {
        ;
    }
                                                                /* Set CLKIN divider to 4.                              */
    BSP_PLL_STS = (BSP_PLL_STS & ~BSP_PLL_STS_DIVSEL_MASK) | BSP_PLL_STS_DIVSEL_DIV4;

                                                                /* Disable OSCCLK failure detection.                    */
    BSP_PLL_STS |= BSP_PLL_STS_MCLKOFF;
                                                                /* Set multiplier to 10.                                */
    BSP_PLL_CR = (BSP_PLL_CR & ~BSP_PLL_CR_DIV_MASK) | BSP_PLL_CR_DIV_NINE;
                                                                /* Wait until PLL locks.                                */
    while ((BSP_PLL_STS & BSP_PLL_STS_PLLLOCKS) == 0u) {
        ;
    }
                                                                /* Set CLKIN divider to 2.                              */
    BSP_PLL_STS = (BSP_PLL_STS & ~BSP_PLL_STS_DIVSEL_MASK) | BSP_PLL_STS_DIVSEL_DIV2;

                                                                /* Enable OSCCLK failure detection.                     */
    BSP_PLL_STS &= ~BSP_PLL_STS_MCLKOFF;
                                                                /* Wait until PLL locks.                                */
    while ((BSP_PLL_STS & BSP_PLL_STS_PLLLOCKS) == 0u) {
        ;
    }
                                                                /* C28x CLKIN = OSCCLK*10/2 = 20 MHz*9/2 = 90 MHz.      */

    BSP_PLL2_CTL = BSP_PLL2_CTL | BSP_PLL2_CLKSRCSEL_X1;

    BSP_PLL2_CTL = BSP_PLL2_CTL | BSP_PLL2_EN;

    BSP_PLL2_MULT |= BSP_PLL2MULT_SIX;

    while ((BSP_PLL2_STS & BSP_PLL2STS_LOCKS) == 0u) {
        ;
    }                                                         /* C28x CLKIN = OSCCLK*10/2 = 30 MHz*10/2 = 150 MHz.    */
}


/*
*********************************************************************************************************
*                                             BSP_PeripheralClock_Init()
*
* Description : Initializes MCU hardware modules register
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void BSP_PeripheralClock_Init(void)
{
    SysCtrlRegs.LOSPCP.all = 0x0002;     // Low-Speed Peripheral Clock Prescaler Register (LOSPCP). Low speed clock= SYSCLKOUT/4 (reset default)
    SysCtrlRegs.XCLK.bit.XCLKOUTDIV=2;   // Clocking (XCLK), 2: XCLKOUT = SYSCLKOUT
    //SysCtrlRegs.PCLKCR0.bit.ECANAENCLK= 1;
    //SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1;
    //SysCtrlRegs.PCLKCR0.bit.SPIBENCLK = 1;
    //SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = 1;
    //SysCtrlRegs.PCLKCR0.bit.SCIBENCLK = 1;
    //SysCtrlRegs.PCLKCR1.bit.EQEP1ENCLK = 1;
    //SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;
    //SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;
    //SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 1;
    SysCtrlRegs.PCLKCR3.bit.USB0ENCLK = 1;
}


/*
*********************************************************************************************************
*                                             BSP_Hardware_Init()
*
* Description : Initializes MCU hardware modules register
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/


void  BSP_Hardware_Init (void)
{
    //I2c_Init();

    //USB_Bulk_Init();  //prepare config first
    USB_Init();       //then init hw

    //UARTStdioInit(0);
    //UARTprintf("\033[2JBulk device application\n");
}
