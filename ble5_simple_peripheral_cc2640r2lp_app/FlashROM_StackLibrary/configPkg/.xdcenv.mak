#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/simplelink_cc2640r2_sdk_2_20_00_49/source;C:/ti/simplelink_cc2640r2_sdk_2_20_00_49/kernel/tirtos/packages;C:/ti/simplelink_cc2640r2_sdk_2_20_00_49/source/ti/ble5stack
override XDCROOT = C:/ti/xdctools_3_50_07_20_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/simplelink_cc2640r2_sdk_2_20_00_49/source;C:/ti/simplelink_cc2640r2_sdk_2_20_00_49/kernel/tirtos/packages;C:/ti/simplelink_cc2640r2_sdk_2_20_00_49/source/ti/ble5stack;C:/ti/xdctools_3_50_07_20_core/packages;..
HOSTOS = Windows
endif
