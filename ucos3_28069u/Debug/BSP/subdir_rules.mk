################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
BSP/I2C.obj: ../BSP/I2C.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/include" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/lib" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uCOS-II/Source" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/BSP/OS/uCOS-II" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uC-LIB" --include_path="/Applications/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/APP" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uC-CPU" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uC-CPU/C28x/CCS" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="BSP/I2C.d" --obj_directory="BSP" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

BSP/bsp.obj: ../BSP/bsp.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/include" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/lib" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uCOS-II/Source" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/BSP/OS/uCOS-II" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uC-LIB" --include_path="/Applications/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/APP" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uC-CPU" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uC-CPU/C28x/CCS" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="BSP/bsp.d" --obj_directory="BSP" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

BSP/bsp_int.obj: ../BSP/bsp_int.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/include" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/lib" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uCOS-II/Source" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/BSP/OS/uCOS-II" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uC-LIB" --include_path="/Applications/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/APP" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uC-CPU" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uC-CPU/C28x/CCS" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="BSP/bsp_int.d" --obj_directory="BSP" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

BSP/bsp_led.obj: ../BSP/bsp_led.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/include" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/lib" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uCOS-II/Source" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/BSP/OS/uCOS-II" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uC-LIB" --include_path="/Applications/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/APP" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uC-CPU" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uC-CPU/C28x/CCS" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="BSP/bsp_led.d" --obj_directory="BSP" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

BSP/cpu_bsp.obj: ../BSP/cpu_bsp.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/include" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/lib" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uCOS-II/Source" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/BSP/OS/uCOS-II" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uC-LIB" --include_path="/Applications/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/APP" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uC-CPU" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u/uC-CPU/C28x/CCS" --include_path="/Volumes/UDISK/ucos3_28069u/ucos3_28069u" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="BSP/cpu_bsp.d" --obj_directory="BSP" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


