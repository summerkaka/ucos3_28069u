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
*
*                                             Delfino 28335
*                                                on the
*                                             TMDSDOCK28335
*                                            Experimenter Kit
*
* Filename      : bsp.h
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

#ifndef  BSP_PRESENT
#define  BSP_PRESENT


/*
*********************************************************************************************************
*                                                EXTERNS
*********************************************************************************************************
*/

#ifdef   BSP_MODULE
#define  BSP_EXT
#else
#define  BSP_EXT  extern
#endif


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <cpu_core.h>

#include  <lib_def.h>


/*
*********************************************************************************************************
*                                            NAME DEFINITIONS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               REGISTERS
*********************************************************************************************************
*/
                                                                /* PLL Registers.                                       */
#define  BSP_PLL_STS                            *((CPU_INT16U *)0x00007011)
#define  BSP_PLL_CR                             *((CPU_INT16U *)0x00007021)
#define  BSP_PLL2_CTL                           *((CPU_INT16U *)0x00007030)
#define  BSP_PLL2_MULT                          *((CPU_INT16U *)0x00007032)
#define  BSP_PLL2_STS                           *((CPU_INT16U *)0x00007034)

                                                                /* PIE Registers.                                       */
#define  BSP_PIE_ADDR_BASE                                     (0x00000CE0u)
#define  BSP_PIE_VECTOR_RAM                                    (0x00000D00u)
#define  BSP_PIE_CTRL                          *((CPU_INT16U *)(BSP_PIE_ADDR_BASE + 0x00))
#define  BSP_PIE_ACK                           *((CPU_INT16U *)(BSP_PIE_ADDR_BASE + 0x01))
#define  BSP_PIE_IER_BASE                       ((CPU_INT16U *)(BSP_PIE_ADDR_BASE + 0x02))
#define  BSP_PIE_IFR_BASE                      *((CPU_INT16U *)(BSP_PIE_ADDR_BASE + 0x03))

                                                                /* External Interrupt Registers.                        */
#define  BSP_XINT_ADDR_BASE                                    (0x00007070u)
#define  BSP_XINT_REG_BASE                      ((CPU_INT16U *)(BSP_XINT_ADDR_BASE))
#define  BSP_XINT_XINT1CR                      *((CPU_INT16U *)(BSP_XINT_ADDR_BASE + 0x0))
#define  BSP_XINT_XINT2CR                      *((CPU_INT16U *)(BSP_XINT_ADDR_BASE + 0x1))
#define  BSP_XINT_XINT3CR                      *((CPU_INT16U *)(BSP_XINT_ADDR_BASE + 0x2))
#define  BSP_XINT_XINT4CR                      *((CPU_INT16U *)(BSP_XINT_ADDR_BASE + 0x3))
#define  BSP_XINT_XINT5CR                      *((CPU_INT16U *)(BSP_XINT_ADDR_BASE + 0x4))
#define  BSP_XINT_XINT6CR                      *((CPU_INT16U *)(BSP_XINT_ADDR_BASE + 0x5))
#define  BSP_XINT_XINT7CR                      *((CPU_INT16U *)(BSP_XINT_ADDR_BASE + 0x6))
#define  BSP_XINT_XNMICR                       *((CPU_INT16U *)(BSP_XINT_ADDR_BASE + 0x7))
#define  BSP_XINT_XINT1CTR                     *((CPU_INT16U *)(BSP_XINT_ADDR_BASE + 0x8))
#define  BSP_XINT_XINT2CTR                     *((CPU_INT16U *)(BSP_XINT_ADDR_BASE + 0x9))
#define  BSP_XINT_XINT3CTR                     *((CPU_INT16U *)(BSP_XINT_ADDR_BASE + 0xA))
#define  BSP_XINT_XNICTR                       *((CPU_INT16U *)(BSP_XINT_ADDR_BASE + 0xF))

                                                                /* GPIO Registers. Only the used ones, not ALL of them. */
#define  BSP_GPIO_CTRL_BASE_ADDR                   (CPU_INT32U)(0x00006F00u)
#define  BSP_GPIO_GPAMUX2                      *((CPU_INT32U *)(BSP_GPIO_CTRL_BASE_ADDR + 0x88u))
#define  BSP_GPIO_GPADIR                       *((CPU_INT32U *)(BSP_GPIO_CTRL_BASE_ADDR + 0x8Au))
#define  BSP_GPIO_GPAPUD                       *((CPU_INT32U *)(BSP_GPIO_CTRL_BASE_ADDR + 0x8Cu))
#define  BSP_GPIO_GPBMUX1                      *((CPU_INT32U *)(BSP_GPIO_CTRL_BASE_ADDR + 0x96u))
#define  BSP_GPIO_GPBDIR                       *((CPU_INT32U *)(BSP_GPIO_CTRL_BASE_ADDR + 0x9Au))
#define  BSP_GPIO_GPBPUD                       *((CPU_INT32U *)(BSP_GPIO_CTRL_BASE_ADDR + 0x9Cu))

#define  BSP_GPIO_DATA_BASE_ADDR                   (CPU_INT32U)(0x00006F00u)
#define  BSP_GPIO_GPASET                       *((CPU_INT32U *)(BSP_GPIO_DATA_BASE_ADDR + 0xC2u))
#define  BSP_GPIO_GPACLEAR                     *((CPU_INT32U *)(BSP_GPIO_DATA_BASE_ADDR + 0xC4u))
#define  BSP_GPIO_GPATOGGLE                    *((CPU_INT32U *)(BSP_GPIO_DATA_BASE_ADDR + 0xC6u))
#define  BSP_GPIO_GPBSET                       *((CPU_INT32U *)(BSP_GPIO_DATA_BASE_ADDR + 0xCAu))
#define  BSP_GPIO_GPBCLEAR                     *((CPU_INT32U *)(BSP_GPIO_DATA_BASE_ADDR + 0xCCu))
#define  BSP_GPIO_GPBTOGGLE                    *((CPU_INT32U *)(BSP_GPIO_DATA_BASE_ADDR + 0xCEu))




/*
*********************************************************************************************************
*                                             REGISTER BITS
*********************************************************************************************************
*/
                                                                /* PLL Register bits.                                   */
#define  BSP_PLL_STS_DIVSEL_MASK                                DEF_BIT_FIELD(2u, 7u)
#define  BSP_PLL_STS_DIVSEL_DIV4                                DEF_BIT_MASK(0u, 7u)
#define  BSP_PLL_STS_DIVSEL_DIV2                                DEF_BIT_MASK(2u, 7u)
#define  BSP_PLL_STS_DIVSEL_DIV1                                DEF_BIT_MASK(3u, 7u)
#define  BSP_PLL_STS_MCLKOFF                                    DEF_BIT_06
#define  BSP_PLL_STS_OSCOFF                                     DEF_BIT_05
#define  BSP_PLL_STS_MCLKCLR                                    DEF_BIT_04
#define  BSP_PLL_STS_MCLKSTS                                    DEF_BIT_03
#define  BSP_PLL_STS_PLLOFF                                     DEF_BIT_02
#define  BSP_PLL_STS_PLLLOCKS                                   DEF_BIT_00

#define  BSP_PLL_CR_DIV_MASK                                    DEF_BIT_FIELD(4u, 0u)
#define  BSP_PLL_CR_DIV_NINE                                    DEF_BIT_MASK(9u, 0u)
#define  BSP_PLL_CR_DIV_TEN                                     DEF_BIT_MASK(10u, 0u)

#define  BSP_PLL2_CLKSRCSEL_X1                                  DEF_BIT_MASK(2u, 0u)
#define  BSP_PLL2_EN                                            DEF_BIT_02

#define  BSP_PLL2MULT_SIX                                       DEF_BIT_MASK(6u, 0u)

#define  BSP_PLL2STS_LOCKS                                      DEF_BIT_00


                                                                /* PIE Register bits.                                   */
#define  BSP_PIE_CTRL_ENPIE                                     DEF_BIT_00

                                                                /* External Interrupt Register bits.                    */
#define  BSP_XINT_ENABLE                                        DEF_BIT_00
#define  BSP_XINT_POL_MASK                                      DEF_BIT_FIELD(2u, 2u)
#define  BSP_XINT_POL_FALLING_EDGE                              DEF_BIT_MASK(0u, 2u)
#define  BSP_XINT_POL_RISING_EDGE                               DEF_BIT_MASK(1u, 2u)
#define  BSP_XINT_POL_EDGE                                      DEF_BIT_MASK(3u, 2u)

                                                                /* GPIO Register bits. [Only the used ones]             */
#define  BSP_GPIO_31_SHIFT                                      31u
#define  BSP_GPIO_34_SHIFT                                      2u
#define  BSP_GPIO_31                                            DEF_BIT_31
#define  BSP_GPIO_34                                            DEF_BIT_02
#define  BSP_GPIO_GPAMUX2_MASK                                  DEF_BIT_FIELD(2u, 0u)
#define  BSP_GPIO_GPADIR_OUT                                    1uL
#define  BSP_GPIO_GPAPUD_DIS                                    1uL
#define  BSP_GPIO_GPAGMUX2_MASK                                 DEF_BIT_FIELD(2u, 0u)
#define  BSP_GPIO_GPBMUX1_MASK                                  DEF_BIT_FIELD(2u, 0u)
#define  BSP_GPIO_GPBDIR_OUT                                    1uL
#define  BSP_GPIO_GPBPUD_DIS                                    1uL
#define  BSP_GPIO_GPBGMUX1_MASK                                 DEF_BIT_FIELD(2u, 0u)

/*
*********************************************************************************************************
*                                           INTERRUPT DEFINES
*********************************************************************************************************
*/
                                                                /* F28335 Interrupt sources.                            */
#define  BSP_INT_SRC_NBR                                128u
                                                                /* Interrupt Groups.                                    */
#define  BSP_INT_GROUP_1                                  0u
#define  BSP_INT_GROUP_2                                  1u
#define  BSP_INT_GROUP_3                                  2u
#define  BSP_INT_GROUP_4                                  3u
#define  BSP_INT_GROUP_5                                  4u
#define  BSP_INT_GROUP_6                                  5u
#define  BSP_INT_GROUP_7                                  6u
#define  BSP_INT_GROUP_8                                  7u
#define  BSP_INT_GROUP_9                                  8u
#define  BSP_INT_GROUP_10                                 9u
#define  BSP_INT_GROUP_11                                10u
#define  BSP_INT_GROUP_12                                11u
                                                                /* External Interrupt sources.                          */
#define  BSP_XINT_ID_XINT1                                0u
#define  BSP_XINT_ID_XINT2                                1u
#define  BSP_XINT_ID_XINT3                                2u
#define  BSP_XINT_ID_XINT4                                3u
#define  BSP_XINT_ID_XINT5                                40
#define  BSP_XINT_ID_XINT6                                5u
#define  BSP_XINT_ID_XINT7                                6u
#define  BSP_XINT_ID_XNMI                                 7u
                                                                /* Generic Interrupt sources.                           */
#define  BSP_INT_ID_RESET                                 0u    /* [  0] RESET   - Always fetched from 0x3FFFD0.        */
#define  BSP_INT_ID_INT1                                  1u    /* [  1] INT1    - Core specific implementation.        */
#define  BSP_INT_ID_INT2                                  2u    /* [  2] INT2    - Core specific implementation.        */
#define  BSP_INT_ID_INT3                                  3u    /* [  3] INT3    - Core specific implementation.        */
#define  BSP_INT_ID_INT4                                  4u    /* [  4] INT4    - Core specific implementation.        */
#define  BSP_INT_ID_INT5                                  5u    /* [  5] INT5    - Core specific implementation.        */
#define  BSP_INT_ID_INT6                                  6u    /* [  6] INT6    - Core specific implementation.        */
#define  BSP_INT_ID_INT7                                  7u    /* [  7] INT7    - Core specific implementation.        */
#define  BSP_INT_ID_INT8                                  8u    /* [  8] INT8    - Core specific implementation.        */
#define  BSP_INT_ID_INT9                                  9u    /* [  9] INT9    - Core specific implementation.        */
#define  BSP_INT_ID_INT10                                10u    /* [ 10] INT10   - Core specific implementation.        */
#define  BSP_INT_ID_INT11                                11u    /* [ 11] INT11   - Core specific implementation.        */
#define  BSP_INT_ID_INT12                                12u    /* [ 12] INT12   - Core specific implementation.        */
#define  BSP_INT_ID_INT13                                13u    /* [ 13] INT13   - Core specific implementation.        */
#define  BSP_INT_ID_INT14                                14u    /* [ 14] INT14   - Core specific implementation.        */
#define  BSP_INT_ID_DATALOG                              15u    /* [ 15] DATALOG - Data log interrupt.                  */
#define  BSP_INT_ID_RTOSINT                              16u    /* [ 16] RTOSINT - OS service interrupt. [CtxSw]        */
#define  BSP_INT_ID_EMUINT                               17u    /* [ 17] EMUINT  - Emulator interrupt.                  */
#define  BSP_INT_ID_NMI                                  18u    /* [ 18] NMI     - Non-Maskable interrupt               */
#define  BSP_INT_ID_ILLEGAL                              19u    /* [ 19] ILLEGAL - Illegal operation.                   */
#define  BSP_INT_ID_USER1                                20u    /* [ 20] USER1   - User event 1 , only called by TRAP.  */
#define  BSP_INT_ID_USER2                                21u    /* [ 21] USER2   - User event 2 , only called by TRAP.  */
#define  BSP_INT_ID_USER3                                22u    /* [ 22] USER3   - User event 3 , only called by TRAP.  */
#define  BSP_INT_ID_USER4                                23u    /* [ 23] USER4   - User event 4 , only called by TRAP.  */
#define  BSP_INT_ID_USER5                                24u    /* [ 24] USER5   - User event 5 , only called by TRAP.  */
#define  BSP_INT_ID_USER6                                25u    /* [ 25] USER6   - User event 6 , only called by TRAP.  */
#define  BSP_INT_ID_USER7                                26u    /* [ 26] USER7   - User event 7 , only called by TRAP.  */
#define  BSP_INT_ID_USER8                                27u    /* [ 27] USER8   - User event 8 , only called by TRAP.  */
#define  BSP_INT_ID_USER9                                28u    /* [ 28] USER9   - User event 9 , only called by TRAP.  */
#define  BSP_INT_ID_USER10                               29u    /* [ 29] USER10  - User event 10, only called by TRAP.  */
#define  BSP_INT_ID_USER11                               30u    /* [ 30] USER11  - User event 11, only called by TRAP.  */
#define  BSP_INT_ID_USER12                               31u    /* [ 31] USER12  - User event 12, only called by TRAP.  */
#define  BSP_INT_ID_INT1_1                               32u    /* [ 32] PIE Group 1 channels 1..8                      */
#define  BSP_INT_ID_INT1_2                               33u    /* [ 33]                                                */
#define  BSP_INT_ID_INT1_3                               34u    /* [ 34]                                                */
#define  BSP_INT_ID_INT1_4                               35u    /* [ 35]                                                */
#define  BSP_INT_ID_INT1_5                               36u    /* [ 36]                                                */
#define  BSP_INT_ID_INT1_6                               37u    /* [ 37]                                                */
#define  BSP_INT_ID_INT1_7                               38u    /* [ 38]                                                */
#define  BSP_INT_ID_INT1_8                               39u    /* [ 39]                                                */
#define  BSP_INT_ID_INT2_1                               40u    /* [ 40] PIE Group 2 channels 1..8                      */
#define  BSP_INT_ID_INT2_2                               41u    /* [ 41]                                                */
#define  BSP_INT_ID_INT2_3                               42u    /* [ 42]                                                */
#define  BSP_INT_ID_INT2_4                               43u    /* [ 43]                                                */
#define  BSP_INT_ID_INT2_5                               44u    /* [ 44]                                                */
#define  BSP_INT_ID_INT2_6                               45u    /* [ 45]                                                */
#define  BSP_INT_ID_INT2_7                               46u    /* [ 46]                                                */
#define  BSP_INT_ID_INT2_8                               47u    /* [ 47]                                                */
#define  BSP_INT_ID_INT3_1                               48u    /* [ 48] PIE Group 3 channels 1..8                      */
#define  BSP_INT_ID_INT3_2                               49u    /* [ 49]                                                */
#define  BSP_INT_ID_INT3_3                               50u    /* [ 50]                                                */
#define  BSP_INT_ID_INT3_4                               51u    /* [ 51]                                                */
#define  BSP_INT_ID_INT3_5                               52u    /* [ 52]                                                */
#define  BSP_INT_ID_INT3_6                               53u    /* [ 53]                                                */
#define  BSP_INT_ID_INT3_7                               54u    /* [ 54]                                                */
#define  BSP_INT_ID_INT3_8                               55u    /* [ 55]                                                */
#define  BSP_INT_ID_INT4_1                               56u    /* [ 56] PIE Group 4 channels 1..8                      */
#define  BSP_INT_ID_INT4_2                               57u    /* [ 57]                                                */
#define  BSP_INT_ID_INT4_3                               58u    /* [ 58]                                                */
#define  BSP_INT_ID_INT4_4                               59u    /* [ 59]                                                */
#define  BSP_INT_ID_INT4_5                               60u    /* [ 60]                                                */
#define  BSP_INT_ID_INT4_6                               61u    /* [ 61]                                                */
#define  BSP_INT_ID_INT4_7                               62u    /* [ 62]                                                */
#define  BSP_INT_ID_INT4_8                               63u    /* [ 63]                                                */
#define  BSP_INT_ID_INT5_1                               64u    /* [ 64] PIE Group 5 channels 1..8                      */
#define  BSP_INT_ID_INT5_2                               65u    /* [ 65]                                                */
#define  BSP_INT_ID_INT5_3                               66u    /* [ 66]                                                */
#define  BSP_INT_ID_INT5_4                               67u    /* [ 67]                                                */
#define  BSP_INT_ID_INT5_5                               68u    /* [ 68]                                                */
#define  BSP_INT_ID_INT5_6                               69u    /* [ 69]                                                */
#define  BSP_INT_ID_INT5_7                               70u    /* [ 70]                                                */
#define  BSP_INT_ID_INT5_8                               71u    /* [ 71]                                                */
#define  BSP_INT_ID_INT6_1                               72u    /* [ 72] PIE Group 6 channels 1..8                      */
#define  BSP_INT_ID_INT6_2                               73u    /* [ 73]                                                */
#define  BSP_INT_ID_INT6_3                               74u    /* [ 74]                                                */
#define  BSP_INT_ID_INT6_4                               75u    /* [ 75]                                                */
#define  BSP_INT_ID_INT6_5                               76u    /* [ 76]                                                */
#define  BSP_INT_ID_INT6_6                               77u    /* [ 77]                                                */
#define  BSP_INT_ID_INT6_7                               78u    /* [ 78]                                                */
#define  BSP_INT_ID_INT6_8                               79u    /* [ 79]                                                */
#define  BSP_INT_ID_INT7_1                               80u    /* [ 80] PIE Group 7 channels 1..8                      */
#define  BSP_INT_ID_INT7_2                               81u    /* [ 81]                                                */
#define  BSP_INT_ID_INT7_3                               82u    /* [ 82]                                                */
#define  BSP_INT_ID_INT7_4                               83u    /* [ 83]                                                */
#define  BSP_INT_ID_INT7_5                               84u    /* [ 84]                                                */
#define  BSP_INT_ID_INT7_6                               85u    /* [ 85]                                                */
#define  BSP_INT_ID_INT7_7                               86u    /* [ 86]                                                */
#define  BSP_INT_ID_INT7_8                               87u    /* [ 87]                                                */
#define  BSP_INT_ID_INT8_1                               88u    /* [ 88] PIE Group 8 channels 1..8                      */
#define  BSP_INT_ID_INT8_2                               89u    /* [ 89]                                                */
#define  BSP_INT_ID_INT8_3                               90u    /* [ 90]                                                */
#define  BSP_INT_ID_INT8_4                               91u    /* [ 91]                                                */
#define  BSP_INT_ID_INT8_5                               92u    /* [ 92]                                                */
#define  BSP_INT_ID_INT8_6                               93u    /* [ 93]                                                */
#define  BSP_INT_ID_INT8_7                               94u    /* [ 94]                                                */
#define  BSP_INT_ID_INT8_8                               95u    /* [ 95]                                                */
#define  BSP_INT_ID_INT9_1                               96u    /* [ 96] PIE Group 9 channels 1..8                      */
#define  BSP_INT_ID_INT9_2                               97u    /* [ 97]                                                */
#define  BSP_INT_ID_INT9_3                               98u    /* [ 98]                                                */
#define  BSP_INT_ID_INT9_4                               99u    /* [ 99]                                                */
#define  BSP_INT_ID_INT9_5                              100u    /* [100]                                                */
#define  BSP_INT_ID_INT9_6                              101u    /* [101]                                                */
#define  BSP_INT_ID_INT9_7                              102u    /* [102]                                                */
#define  BSP_INT_ID_INT9_8                              103u    /* [103]                                                */
#define  BSP_INT_ID_INT10_1                             104u    /* [104] PIE Group 10 channels 1..8                     */
#define  BSP_INT_ID_INT10_2                             105u    /* [105]                                                */
#define  BSP_INT_ID_INT10_3                             106u    /* [106]                                                */
#define  BSP_INT_ID_INT10_4                             107u    /* [107]                                                */
#define  BSP_INT_ID_INT10_5                             108u    /* [108]                                                */
#define  BSP_INT_ID_INT10_6                             109u    /* [109]                                                */
#define  BSP_INT_ID_INT10_7                             110u    /* [110]                                                */
#define  BSP_INT_ID_INT10_8                             111u    /* [111]                                                */
#define  BSP_INT_ID_INT11_1                             112u    /* [112] PIE Group 11 channels 1..8                     */
#define  BSP_INT_ID_INT11_2                             113u    /* [113]                                                */
#define  BSP_INT_ID_INT11_3                             114u    /* [114]                                                */
#define  BSP_INT_ID_INT11_4                             115u    /* [115]                                                */
#define  BSP_INT_ID_INT11_5                             116u    /* [116]                                                */
#define  BSP_INT_ID_INT11_6                             117u    /* [117]                                                */
#define  BSP_INT_ID_INT11_7                             118u    /* [118]                                                */
#define  BSP_INT_ID_INT11_8                             119u    /* [119]                                                */
#define  BSP_INT_ID_INT12_1                             120u    /* [120] PIE Group 12 channels 1..8                     */
#define  BSP_INT_ID_INT12_2                             121u    /* [121]                                                */
#define  BSP_INT_ID_INT12_3                             122u    /* [122]                                                */
#define  BSP_INT_ID_INT12_4                             123u    /* [123]                                                */
#define  BSP_INT_ID_INT12_5                             124u    /* [124]                                                */
#define  BSP_INT_ID_INT12_6                             125u    /* [125]                                                */
#define  BSP_INT_ID_INT12_7                             126u    /* [126]                                                */
#define  BSP_INT_ID_INT12_8                             127u    /* [127]                                                */
#define  BSP_INT_ID_INT1_9                              128u    /* [128] PIE Group 1 channels 9..16                     */
#define  BSP_INT_ID_INT1_10                             129u    /* [129]                                                */
#define  BSP_INT_ID_INT1_11                             130u    /* [130]                                                */
#define  BSP_INT_ID_INT1_12                             131u    /* [131]                                                */
#define  BSP_INT_ID_INT1_13                             132u    /* [132]                                                */
#define  BSP_INT_ID_INT1_14                             133u    /* [133]                                                */
#define  BSP_INT_ID_INT1_15                             134u    /* [134]                                                */
#define  BSP_INT_ID_INT1_16                             135u    /* [135]                                                */
#define  BSP_INT_ID_INT2_9                              136u    /* [136] PIE Group 2 channels 9..16                     */
#define  BSP_INT_ID_INT2_10                             137u    /* [137]                                                */
#define  BSP_INT_ID_INT2_11                             138u    /* [138]                                                */
#define  BSP_INT_ID_INT2_12                             139u    /* [139]                                                */
#define  BSP_INT_ID_INT2_13                             140u    /* [140]                                                */
#define  BSP_INT_ID_INT2_14                             141u    /* [141]                                                */
#define  BSP_INT_ID_INT2_15                             142u    /* [142]                                                */
#define  BSP_INT_ID_INT2_16                             143u    /* [143]                                                */
#define  BSP_INT_ID_INT3_9                              144u    /* [144] PIE Group 3 channels 9..16                     */
#define  BSP_INT_ID_INT3_10                             145u    /* [145]                                                */
#define  BSP_INT_ID_INT3_11                             146u    /* [146]                                                */
#define  BSP_INT_ID_INT3_12                             147u    /* [147]                                                */
#define  BSP_INT_ID_INT3_13                             148u    /* [148]                                                */
#define  BSP_INT_ID_INT3_14                             149u    /* [149]                                                */
#define  BSP_INT_ID_INT3_15                             150u    /* [150]                                                */
#define  BSP_INT_ID_INT3_16                             151u    /* [151]                                                */
#define  BSP_INT_ID_INT4_9                              152u    /* [152] PIE Group 4 channels 9..16                     */
#define  BSP_INT_ID_INT4_10                             153u    /* [153]                                                */
#define  BSP_INT_ID_INT4_11                             154u    /* [154]                                                */
#define  BSP_INT_ID_INT4_12                             155u    /* [155]                                                */
#define  BSP_INT_ID_INT4_13                             156u    /* [156]                                                */
#define  BSP_INT_ID_INT4_14                             157u    /* [157]                                                */
#define  BSP_INT_ID_INT4_15                             158u    /* [158]                                                */
#define  BSP_INT_ID_INT4_16                             159u    /* [159]                                                */
#define  BSP_INT_ID_INT5_9                              160u    /* [160] PIE Group 5 channels 9..16                     */
#define  BSP_INT_ID_INT5_10                             161u    /* [161]                                                */
#define  BSP_INT_ID_INT5_11                             162u    /* [162]                                                */
#define  BSP_INT_ID_INT5_12                             163u    /* [163]                                                */
#define  BSP_INT_ID_INT5_13                             164u    /* [164]                                                */
#define  BSP_INT_ID_INT5_14                             165u    /* [165]                                                */
#define  BSP_INT_ID_INT5_15                             166u    /* [166]                                                */
#define  BSP_INT_ID_INT5_16                             167u    /* [167]                                                */
#define  BSP_INT_ID_INT6_9                              168u    /* [168] PIE Group 6 channels 9..16                     */
#define  BSP_INT_ID_INT6_10                             169u    /* [169]                                                */
#define  BSP_INT_ID_INT6_11                             170u    /* [170]                                                */
#define  BSP_INT_ID_INT6_12                             171u    /* [171]                                                */
#define  BSP_INT_ID_INT6_13                             172u    /* [172]                                                */
#define  BSP_INT_ID_INT6_14                             173u    /* [173]                                                */
#define  BSP_INT_ID_INT6_15                             174u    /* [174]                                                */
#define  BSP_INT_ID_INT6_16                             175u    /* [175]                                                */
#define  BSP_INT_ID_INT7_9                              176u    /* [176] PIE Group 7 channels 9..16                     */
#define  BSP_INT_ID_INT7_10                             177u    /* [177]                                                */
#define  BSP_INT_ID_INT7_11                             178u    /* [178]                                                */
#define  BSP_INT_ID_INT7_12                             179u    /* [179]                                                */
#define  BSP_INT_ID_INT7_13                             180u    /* [180]                                                */
#define  BSP_INT_ID_INT7_14                             181u    /* [181]                                                */
#define  BSP_INT_ID_INT7_15                             182u    /* [182]                                                */
#define  BSP_INT_ID_INT7_16                             183u    /* [183]                                                */
#define  BSP_INT_ID_INT8_9                              184u    /* [184] PIE Group 8 channels 9..16                     */
#define  BSP_INT_ID_INT8_10                             185u    /* [185]                                                */
#define  BSP_INT_ID_INT8_11                             186u    /* [186]                                                */
#define  BSP_INT_ID_INT8_12                             187u    /* [187]                                                */
#define  BSP_INT_ID_INT8_13                             188u    /* [188]                                                */
#define  BSP_INT_ID_INT8_14                             189u    /* [189]                                                */
#define  BSP_INT_ID_INT8_15                             190u    /* [190]                                                */
#define  BSP_INT_ID_INT8_16                             191u    /* [191]                                                */
#define  BSP_INT_ID_INT9_9                              192u    /* [192] PIE Group 9 channels 9..16                     */
#define  BSP_INT_ID_INT9_10                             193u    /* [193]                                                */
#define  BSP_INT_ID_INT9_11                             194u    /* [194]                                                */
#define  BSP_INT_ID_INT9_12                             195u    /* [195]                                                */
#define  BSP_INT_ID_INT9_13                             196u    /* [196]                                                */
#define  BSP_INT_ID_INT9_14                             197u    /* [197]                                                */
#define  BSP_INT_ID_INT9_15                             198u    /* [198]                                                */
#define  BSP_INT_ID_INT9_16                             199u    /* [199]                                                */
#define  BSP_INT_ID_INT10_9                             200u    /* [200] PIE Group 10 channels 9..16                    */
#define  BSP_INT_ID_INT10_10                            201u    /* [201]                                                */
#define  BSP_INT_ID_INT10_11                            202u    /* [202]                                                */
#define  BSP_INT_ID_INT10_12                            203u    /* [203]                                                */
#define  BSP_INT_ID_INT10_13                            204u    /* [204]                                                */
#define  BSP_INT_ID_INT10_14                            205u    /* [205]                                                */
#define  BSP_INT_ID_INT10_15                            206u    /* [206]                                                */
#define  BSP_INT_ID_INT10_16                            207u    /* [207]                                                */
#define  BSP_INT_ID_INT11_9                             208u    /* [208] PIE Group 11 channels 9..16                    */
#define  BSP_INT_ID_INT11_10                            209u    /* [209]                                                */
#define  BSP_INT_ID_INT11_11                            210u    /* [210]                                                */
#define  BSP_INT_ID_INT11_12                            211u    /* [211]                                                */
#define  BSP_INT_ID_INT11_13                            212u    /* [212]                                                */
#define  BSP_INT_ID_INT11_14                            213u    /* [213]                                                */
#define  BSP_INT_ID_INT11_15                            214u    /* [214]                                                */
#define  BSP_INT_ID_INT11_16                            215u    /* [215]                                                */
#define  BSP_INT_ID_INT12_9                             216u    /* [216] PIE Group 12 channels 9..16                    */
#define  BSP_INT_ID_INT12_10                            217u    /* [217]                                                */
#define  BSP_INT_ID_INT12_11                            218u    /* [218]                                                */
#define  BSP_INT_ID_INT12_12                            219u    /* [219]                                                */
#define  BSP_INT_ID_INT12_13                            220u    /* [220]                                                */
#define  BSP_INT_ID_INT12_14                            221u    /* [221]                                                */
#define  BSP_INT_ID_INT12_15                            222u    /* [222]                                                */
#define  BSP_INT_ID_INT12_16                            223u    /* [223]                                                */


/*
*********************************************************************************************************
*                                              LED DEFINES
*********************************************************************************************************
*/
                                                                /* LED Identification.                                  */
#define  BSP_LED_ALL                                      0u
#define  BSP_LED_LD1                                      1u
#define  BSP_LED_LD2                                      2u
#define  BSP_LED_LD3                                      3u
#define  BSP_LED_LD4                                      4u


/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/
                                                                /* Interrupt vector table.                              */
#if 0
extern  CPU_FNCT_VOID  __BSP_VectorTable[];
#endif


/*
*********************************************************************************************************
*                                                 MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void        BSP_Init         (void);

void        BSP_Tick_Init    (void);

CPU_INT32U  BSP_CPU_ClkFreq  (void);

void        BSP_RAM_StartHere(void);


/*
*********************************************************************************************************
*                                           INTERRUPT SERVICES
*********************************************************************************************************
*/

void  BSP_IntAck         (CPU_DATA       int_id);

void  BSP_IntEn          (CPU_DATA       int_id);

void  BSP_IntDis         (CPU_DATA       int_id);

void  BSP_ExtIntEn       (CPU_DATA       xint_id);

void  BSP_ExtIntDis      (CPU_DATA       xint_id);

#if 0
                                                                /* TODO: BSP_ExtIntSetPol() BSP_ExtIntSetSrc()          */
void  BSP_ExtIntSetPol   (CPU_DATA       pol);
void  BSP_ExtIntSetSrc   (CPU_DATA       src);
#endif

void  BSP_IntVectSet     (CPU_DATA       int_id,
                          CPU_FNCT_VOID  isr);

void  BSP_IntHandlerDummy(void);


/*
*********************************************************************************************************
*                                             LED SERVICES
*********************************************************************************************************
*/

void  BSP_LED_On    (CPU_DATA  led);

void  BSP_LED_Off   (CPU_DATA  led);

void  BSP_LED_Toggle(CPU_DATA  led);


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of module include.                               */

