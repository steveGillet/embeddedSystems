################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../MSP_EXP432E401Y_NoRTOS.cmd 

SYSCFG_SRCS += \
../uartecho.syscfg 

C_SRCS += \
../main_nortos.c \
../uartecho.c \
./syscfg/ti_drivers_config.c \
../udpEcho.c \
../udpEchoHooks.c 

GEN_FILES += \
./syscfg/ti_drivers_config.c 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./main_nortos.d \
./uartecho.d \
./syscfg/ti_drivers_config.d \
./udpEcho.d \
./udpEchoHooks.d 

OBJS += \
./main_nortos.obj \
./uartecho.obj \
./syscfg/ti_drivers_config.obj \
./udpEcho.obj \
./udpEchoHooks.obj 

GEN_MISC_FILES += \
./syscfg/ti_drivers_config.h \
./syscfg/ti_utils_build_linker.cmd.exp \
./syscfg/syscfg_c.rov.xs 

GEN_MISC_DIRS__QUOTED += \
"syscfg/" 

OBJS__QUOTED += \
"main_nortos.obj" \
"uartecho.obj" \
"syscfg/ti_drivers_config.obj" \
"udpEcho.obj" \
"udpEchoHooks.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg/ti_drivers_config.h" \
"syscfg/ti_utils_build_linker.cmd.exp" \
"syscfg/syscfg_c.rov.xs" 

C_DEPS__QUOTED += \
"main_nortos.d" \
"uartecho.d" \
"syscfg/ti_drivers_config.d" \
"udpEcho.d" \
"udpEchoHooks.d" 

GEN_FILES__QUOTED += \
"syscfg/ti_drivers_config.c" 

C_SRCS__QUOTED += \
"../main_nortos.c" \
"../uartecho.c" \
"./syscfg/ti_drivers_config.c" \
"../udpEcho.c" \
"../udpEchoHooks.c" 

SYSCFG_SRCS__QUOTED += \
"../uartecho.syscfg" 


