################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
uC-LIB/lib_ascii.obj: ../uC-LIB/lib_ascii.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/include" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/lib" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uCOS-II/Source" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/BSP/OS/uCOS-II" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uC-LIB" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/APP" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uC-CPU" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uC-CPU/C28x/CCS" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uC-LIB/lib_ascii.d" --obj_directory="uC-LIB" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uC-LIB/lib_math.obj: ../uC-LIB/lib_math.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/include" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/lib" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uCOS-II/Source" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/BSP/OS/uCOS-II" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uC-LIB" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/APP" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uC-CPU" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uC-CPU/C28x/CCS" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uC-LIB/lib_math.d" --obj_directory="uC-LIB" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uC-LIB/lib_mem.obj: ../uC-LIB/lib_mem.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/include" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/lib" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uCOS-II/Source" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/BSP/OS/uCOS-II" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uC-LIB" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/APP" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uC-CPU" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uC-CPU/C28x/CCS" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uC-LIB/lib_mem.d" --obj_directory="uC-LIB" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uC-LIB/lib_str.obj: ../uC-LIB/lib_str.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/include" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/lib" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uCOS-II/Source" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/BSP/OS/uCOS-II" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uC-LIB" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/APP" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uC-CPU" --include_path="C:/03_workspace/ccsv7/ucos3_28069u/ucos3_28069u/uC-CPU/C28x/CCS" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uC-LIB/lib_str.d" --obj_directory="uC-LIB" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


