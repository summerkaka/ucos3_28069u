;
;********************************************************************************************************
;                                     MICIRUM BOARD SUPPORT PACKAGE
;
;                             (c) Copyright 2015; Micrium, Inc.; Weston, FL
;
;                   All rights reserved.  Protected by international copyright laws.
;                  Knowledge of the source code may not be used to write a similar
;                   product.  This file may only be used in accordance with a license
;                   and should not be redistributed in any way.
;********************************************************************************************************
;

;
;********************************************************************************************************
;
;                                         BOARD SUPPORT PACKAGE
;
*                                             Delfino 28335
*                                                on the
*                                             TMDSDOCK28335
*                                            Experimenter Kit
;
; Filename      : bsp_start.asm
; Version       : V1.00
; Programmer(s) : JFT
;********************************************************************************************************
;

;********************************************************************************************************
;                                           PUBLIC FUNCTIONS
;********************************************************************************************************

    .def   _BSP_RAM_StartHere


;********************************************************************************************************
;                                       EXTERNAL GLOBAL VARIABLES
;********************************************************************************************************

    .ref   _c_int00                                             ; RTS entry point. Ultimately calls main().


;********************************************************************************************************
;                                                EQUATES
;********************************************************************************************************

WDCR             .set                       0x007029
WDKEY            .set                       0x007025
WDCR_WDDIS       .set                       0x0068              ; See Watchdog Control Register Field Descriptions.


;********************************************************************************************************
;                                      CODE GENERATION DIRECTIVES
;********************************************************************************************************

    .sect "ram_start"
    LB      _BSP_RAM_StartHere


;********************************************************************************************************
;                                           BSP_RAM_StartHere()
;
; Description : C28x jumps into RAM Start upon RAM loading.
;
; Prototypes  : void  BSP_RAM_StartHere(void);
;********************************************************************************************************

    .text
    .asmfunc
_BSP_RAM_StartHere:
                                                                ; Allow access to protected registers and regions.
    EALLOW
                                                                ; Disable interrupts.
    DINT
                                                                ; Debugger can access registers and memory in real time.
    CLRC    DBGM
                                                                ; Disable Watchdog.
    MOVL    XAR0, #WDCR
    MOV     *AR0, #WDCR_WDDIS
    MOVL    XAR0, #WDKEY
    MOV     *AR0, #0x55
    MOV     *AR0, #0xAA
                                                                ; Call c_int00().
    LCR     _c_int00
    .endasmfunc


;********************************************************************************************************
;                                      CODE GENERATION DIRECTIVES
;********************************************************************************************************

    .end

