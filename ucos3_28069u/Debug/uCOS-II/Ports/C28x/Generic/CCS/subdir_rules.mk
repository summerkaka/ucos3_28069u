################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
uCOS-II/Ports/C28x/Generic/CCS/os_cpu_a.obj: ../uCOS-II/Ports/C28x/Generic/CCS/os_cpu_a.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/03_workspace/ucos3_28069u/include" --include_path="C:/03_workspace/ucos3_28069u/lib" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Source" --include_path="C:/03_workspace/ucos3_28069u/BSP/OS/uCOS-II" --include_path="C:/03_workspace/ucos3_28069u/uC-LIB" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="C:/03_workspace/ucos3_28069u/APP" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU/C28x/CCS" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Ports/C28x/Generic/CCS/os_cpu_a.d" --obj_directory="uCOS-II/Ports/C28x/Generic/CCS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uCOS-II/Ports/C28x/Generic/CCS/os_cpu_c.obj: ../uCOS-II/Ports/C28x/Generic/CCS/os_cpu_c.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/03_workspace/ucos3_28069u/include" --include_path="C:/03_workspace/ucos3_28069u/lib" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Source" --include_path="C:/03_workspace/ucos3_28069u/BSP/OS/uCOS-II" --include_path="C:/03_workspace/ucos3_28069u/uC-LIB" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="C:/03_workspace/ucos3_28069u/APP" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU/C28x/CCS" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Ports/C28x/Generic/CCS/os_cpu_c.d" --obj_directory="uCOS-II/Ports/C28x/Generic/CCS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uCOS-II/Ports/C28x/Generic/CCS/os_cpu_i.obj: ../uCOS-II/Ports/C28x/Generic/CCS/os_cpu_i.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/03_workspace/ucos3_28069u/include" --include_path="C:/03_workspace/ucos3_28069u/lib" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Source" --include_path="C:/03_workspace/ucos3_28069u/BSP/OS/uCOS-II" --include_path="C:/03_workspace/ucos3_28069u/uC-LIB" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="C:/03_workspace/ucos3_28069u/APP" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU/C28x/CCS" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Ports/C28x/Generic/CCS/os_cpu_i.d" --obj_directory="uCOS-II/Ports/C28x/Generic/CCS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uCOS-II/Ports/C28x/Generic/CCS/os_dbg.obj: ../uCOS-II/Ports/C28x/Generic/CCS/os_dbg.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/03_workspace/ucos3_28069u/include" --include_path="C:/03_workspace/ucos3_28069u/lib" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Source" --include_path="C:/03_workspace/ucos3_28069u/BSP/OS/uCOS-II" --include_path="C:/03_workspace/ucos3_28069u/uC-LIB" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="C:/03_workspace/ucos3_28069u/APP" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU/C28x/CCS" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Ports/C28x/Generic/CCS/os_dbg.d" --obj_directory="uCOS-II/Ports/C28x/Generic/CCS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


