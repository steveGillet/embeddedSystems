################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/home/steve0gillet/ti/ccs1200/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/steve0gillet/workspace_v12/uartecho_MSP_EXP432E401Y_nortos_ccs" --include_path="/home/steve0gillet/workspace_v12/uartecho_MSP_EXP432E401Y_nortos_ccs/Debug" --include_path="/home/steve0gillet/ti/simplelink_msp432e4_sdk_4_20_00_12/source" --include_path="/home/steve0gillet/ti/simplelink_msp432e4_sdk_4_20_00_12/source/third_party/CMSIS/Include" --include_path="/home/steve0gillet/ti/simplelink_msp432e4_sdk_4_20_00_12/kernel/nortos" --include_path="/home/steve0gillet/ti/simplelink_msp432e4_sdk_4_20_00_12/kernel/nortos/posix" --include_path="/home/steve0gillet/ti/ccs1200/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=none -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="/home/steve0gillet/workspace_v12/uartecho_MSP_EXP432E401Y_nortos_ccs/Debug/syscfg" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1928100815: ../uartecho.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"/home/steve0gillet/ti/sysconfig_1.5.0/sysconfig_cli.sh" -s "/home/steve0gillet/ti/simplelink_msp432e4_sdk_4_20_00_12/.metadata/product.json" -o "syscfg" "/home/steve0gillet/workspace_v12/uartecho_MSP_EXP432E401Y_nortos_ccs/uartecho.syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-1928100815 ../uartecho.syscfg
syscfg/ti_drivers_config.h: build-1928100815
syscfg/ti_utils_build_linker.cmd.exp: build-1928100815
syscfg/syscfg_c.rov.xs: build-1928100815
syscfg/: build-1928100815

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/home/steve0gillet/ti/ccs1200/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/steve0gillet/workspace_v12/uartecho_MSP_EXP432E401Y_nortos_ccs" --include_path="/home/steve0gillet/workspace_v12/uartecho_MSP_EXP432E401Y_nortos_ccs/Debug" --include_path="/home/steve0gillet/ti/simplelink_msp432e4_sdk_4_20_00_12/source" --include_path="/home/steve0gillet/ti/simplelink_msp432e4_sdk_4_20_00_12/source/third_party/CMSIS/Include" --include_path="/home/steve0gillet/ti/simplelink_msp432e4_sdk_4_20_00_12/kernel/nortos" --include_path="/home/steve0gillet/ti/simplelink_msp432e4_sdk_4_20_00_12/kernel/nortos/posix" --include_path="/home/steve0gillet/ti/ccs1200/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=none -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="/home/steve0gillet/workspace_v12/uartecho_MSP_EXP432E401Y_nortos_ccs/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


