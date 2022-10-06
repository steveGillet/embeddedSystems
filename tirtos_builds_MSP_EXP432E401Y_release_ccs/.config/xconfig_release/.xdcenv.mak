#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /home/steve0gillet/ti/simplelink_msp432e4_sdk_4_20_00_12/source;/home/steve0gillet/ti/simplelink_msp432e4_sdk_4_20_00_12/kernel/tirtos/packages;/home/steve0gillet/workspace_v12/tirtos_builds_MSP_EXP432E401Y_release_ccs/.config
override XDCROOT = /home/steve0gillet/ti/ccs1200/xdctools_3_62_01_16_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /home/steve0gillet/ti/simplelink_msp432e4_sdk_4_20_00_12/source;/home/steve0gillet/ti/simplelink_msp432e4_sdk_4_20_00_12/kernel/tirtos/packages;/home/steve0gillet/workspace_v12/tirtos_builds_MSP_EXP432E401Y_release_ccs/.config;/home/steve0gillet/ti/ccs1200/xdctools_3_62_01_16_core/packages;..
HOSTOS = Linux
endif
