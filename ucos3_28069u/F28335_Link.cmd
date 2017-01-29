/*
*********************************************************************************************************
*
*                                          F28335 Linker Script
*
*                                                TI C28x
*                                            TI C28x Linker
*
*
* Filename      : F28335_Link.cmd
* Version       : V1.00
* Programmer(s) : JFT
*
* Note(s)       : (1) Heavily based on '28335_RAM_link.cmd' by Texas Instruments.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            MEMORY REGIONS
*
* Note(s) : (1) PAGE 0 will be used for program sections.
*
*           (2) PAGE 1 will be used for data    sections.
*
*           (3) Blocks in PAGE 0 are mirrored in PAGE 1, there is no need to define them twice.
*
*           (4) This linker script doesn't define memory regions for the IQMath library.
*********************************************************************************************************
*/

MEMORY
{
                                                                /* Program Memory.                                      */
    PAGE 0:
        BEGIN      : origin = 0x000000, length = 0x000002
        RAMM0      : origin = 0x000050, length = 0x0003B0

        RAMLP      : origin = 0x008000, length = 0x005000
        CSM_RSVD   : origin = 0x33FF80, length = 0x000076       /* Part of FLASHA.  Program with all 0x0000 when ...    */
                                                                /*  ... CSM is in use.                                  */
        CSM_PWL    : origin = 0x33FFF8, length = 0x000008       /* Part of FLASHA.  CSM password locations in FLASHA    */
        ADC_CAL    : origin = 0x380080, length = 0x000009

        BOOTROM    : origin = 0x3FF27C, length = 0x000D44
        VECTORS    : origin = 0x3FFFC0, length = 0x000040
                                                                /* Data Memory.                                         */
    PAGE 1 :
        BOOT_RSVD  : origin = 0x000002, length = 0x00004E       /* Part of M0, BOOT rom will use this for stack.        */
        RAMM1      : origin = 0x000400, length = 0x000400
        PIE_VRAM   : origin = 0x000D00, length = 0x000100
        RAMLD      : origin = 0x00D000, length = 0x003000
}


/*
*********************************************************************************************************
*                                            LINKER SECTIONS
*
* Note(s) : (1) This block maps the linker defined sections to the previously defined memory regions.
*********************************************************************************************************
*/

SECTIONS
{
                                                                 /* Program sections.                                   */
    ram_start  : > BEGIN,           PAGE = 0                     /* codestart branches to c_int00().                    */
    ramfuncs   : > RAMLP,           PAGE = 0
    .text      : > RAMLP,           PAGE = 0
    .cinit     : > RAMLP,           PAGE = 0
    .pinit     : > RAMLP,           PAGE = 0
    .switch    : > RAMLP,           PAGE = 0
                                                                /* Default reset handler. Not used.                     */
    .reset     : > VECTORS,         PAGE = 0, TYPE = DSECT
                                                                /* Data sections.                                       */
    .stack     : > RAMM1,           PAGE = 1
    pie_vram   : > PIE_VRAM,        PAGE = 1
    .ebss      : > RAMLD,           PAGE = 1
    .econst    : > RAMLD,           PAGE = 1
    .esysmem   : > RAMLD,           PAGE = 1
                                                                /* 128-bit CSM Password. Not used.                      */
    csm_rsvd   : > CSM_RSVD,        PAGE = 0, TYPE = DSECT
    csmpasswds : > CSM_PWL,         PAGE = 0, TYPE = DSECT
                                                                /* ADC Calibration.                                     */
    .adc_cal   : load = ADC_CAL,    PAGE = 0, TYPE = NOLOAD
}

