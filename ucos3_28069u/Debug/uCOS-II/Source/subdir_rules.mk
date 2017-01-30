################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
uCOS-II/Source/os_core.obj: ../uCOS-II/Source/os_core.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/03_workspace/ucos3_28069u/include" --include_path="C:/03_workspace/ucos3_28069u/lib" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Source" --include_path="C:/03_workspace/ucos3_28069u/BSP/OS/uCOS-II" --include_path="C:/03_workspace/ucos3_28069u/uC-LIB" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="C:/03_workspace/ucos3_28069u/APP" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU/C28x/CCS" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_core.d" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uCOS-II/Source/os_flag.obj: ../uCOS-II/Source/os_flag.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/03_workspace/ucos3_28069u/include" --include_path="C:/03_workspace/ucos3_28069u/lib" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Source" --include_path="C:/03_workspace/ucos3_28069u/BSP/OS/uCOS-II" --include_path="C:/03_workspace/ucos3_28069u/uC-LIB" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="C:/03_workspace/ucos3_28069u/APP" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU/C28x/CCS" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_flag.d" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uCOS-II/Source/os_mbox.obj: ../uCOS-II/Source/os_mbox.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/03_workspace/ucos3_28069u/include" --include_path="C:/03_workspace/ucos3_28069u/lib" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Source" --include_path="C:/03_workspace/ucos3_28069u/BSP/OS/uCOS-II" --include_path="C:/03_workspace/ucos3_28069u/uC-LIB" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="C:/03_workspace/ucos3_28069u/APP" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU/C28x/CCS" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_mbox.d" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uCOS-II/Source/os_mem.obj: ../uCOS-II/Source/os_mem.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/03_workspace/ucos3_28069u/include" --include_path="C:/03_workspace/ucos3_28069u/lib" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Source" --include_path="C:/03_workspace/ucos3_28069u/BSP/OS/uCOS-II" --include_path="C:/03_workspace/ucos3_28069u/uC-LIB" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="C:/03_workspace/ucos3_28069u/APP" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU/C28x/CCS" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_mem.d" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uCOS-II/Source/os_mutex.obj: ../uCOS-II/Source/os_mutex.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/03_workspace/ucos3_28069u/include" --include_path="C:/03_workspace/ucos3_28069u/lib" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Source" --include_path="C:/03_workspace/ucos3_28069u/BSP/OS/uCOS-II" --include_path="C:/03_workspace/ucos3_28069u/uC-LIB" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="C:/03_workspace/ucos3_28069u/APP" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU/C28x/CCS" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_mutex.d" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uCOS-II/Source/os_q.obj: ../uCOS-II/Source/os_q.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/03_workspace/ucos3_28069u/include" --include_path="C:/03_workspace/ucos3_28069u/lib" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Source" --include_path="C:/03_workspace/ucos3_28069u/BSP/OS/uCOS-II" --include_path="C:/03_workspace/ucos3_28069u/uC-LIB" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="C:/03_workspace/ucos3_28069u/APP" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU/C28x/CCS" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_q.d" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uCOS-II/Source/os_sem.obj: ../uCOS-II/Source/os_sem.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/03_workspace/ucos3_28069u/include" --include_path="C:/03_workspace/ucos3_28069u/lib" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Source" --include_path="C:/03_workspace/ucos3_28069u/BSP/OS/uCOS-II" --include_path="C:/03_workspace/ucos3_28069u/uC-LIB" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="C:/03_workspace/ucos3_28069u/APP" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU/C28x/CCS" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_sem.d" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uCOS-II/Source/os_task.obj: ../uCOS-II/Source/os_task.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/03_workspace/ucos3_28069u/include" --include_path="C:/03_workspace/ucos3_28069u/lib" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Source" --include_path="C:/03_workspace/ucos3_28069u/BSP/OS/uCOS-II" --include_path="C:/03_workspace/ucos3_28069u/uC-LIB" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="C:/03_workspace/ucos3_28069u/APP" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU/C28x/CCS" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_task.d" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uCOS-II/Source/os_time.obj: ../uCOS-II/Source/os_time.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/03_workspace/ucos3_28069u/include" --include_path="C:/03_workspace/ucos3_28069u/lib" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Source" --include_path="C:/03_workspace/ucos3_28069u/BSP/OS/uCOS-II" --include_path="C:/03_workspace/ucos3_28069u/uC-LIB" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="C:/03_workspace/ucos3_28069u/APP" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU/C28x/CCS" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_time.d" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uCOS-II/Source/os_tmr.obj: ../uCOS-II/Source/os_tmr.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/03_workspace/ucos3_28069u/include" --include_path="C:/03_workspace/ucos3_28069u/lib" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Ports/C28x/Generic/CCS" --include_path="C:/03_workspace/ucos3_28069u/uCOS-II/Source" --include_path="C:/03_workspace/ucos3_28069u/BSP/OS/uCOS-II" --include_path="C:/03_workspace/ucos3_28069u/uC-LIB" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/MWare" --include_path="C:/03_workspace/ucos3_28069u/APP" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU" --include_path="C:/03_workspace/ucos3_28069u/uC-CPU/C28x/CCS" --define=ccs_c2k -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_tmr.d" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


