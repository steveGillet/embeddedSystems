/*
 * Do not modify this file; it is automatically generated from the template
 * linkcmd.xdt in the ti.platforms.msp432 package and will be overwritten.
 */

/*
 * put '"'s around paths because, without this, the linker
 * considers '-' as minus operator, not a file name character.
 */


-l"/home/steve0gillet/workspace_v12/tirtos_builds_MSP_EXP432E401Y_release_ccs/Debug/configPkg/package/cfg/release_pem4f.oem4f"
-l"/home/steve0gillet/workspace_v12/tirtos_builds_MSP_EXP432E401Y_release_ccs/src/sysbios/sysbios.aem4f"
-l"/home/steve0gillet/ti/simplelink_msp432e4_sdk_4_20_00_12/kernel/tirtos/packages/ti/targets/arm/rtsarm/lib/boot.aem4f"
-l"/home/steve0gillet/ti/simplelink_msp432e4_sdk_4_20_00_12/kernel/tirtos/packages/ti/targets/arm/rtsarm/lib/auto_init.aem4f"
-l"/home/steve0gillet/ti/ccs1200/xdctools_3_62_01_16_core/packages/xdc/rov/runtime/lib/xdc.rov.runtime.aem4f"

--retain="*(xdc.meta)"

/* C6x Elf symbols */
--symbol_map __TI_STACK_SIZE=__STACK_SIZE
--symbol_map __TI_STACK_BASE=__stack
--symbol_map _stack=__stack


--args 0x0
-heap  0x0

/*
 * Linker command file contributions from all loaded packages:
 */

/* Content from xdc.services.global (null): */

/* Content from xdc (null): */

/* Content from xdc.corevers (null): */

/* Content from xdc.rov (null): */

/* Content from xdc.runtime (null): */

/* Content from xdc.rov.runtime (null): */

/* Content from xdc.shelf (null): */

/* Content from xdc.services.spec (null): */

/* Content from xdc.services.intern.xsr (null): */

/* Content from xdc.services.intern.gen (null): */

/* Content from xdc.services.intern.cmd (null): */

/* Content from xdc.bld (null): */

/* Content from ti.targets (null): */

/* Content from ti.targets.arm.elf (null): */

/* Content from ti.targets.arm.rtsarm (null): */

/* Content from ti.sysbios.interfaces (null): */

/* Content from ti.sysbios.family (null): */

/* Content from ti.sysbios.family.arm (ti/sysbios/family/arm/linkcmd.xdt): */

/* Content from xdc.services.getset (null): */

/* Content from ti.sysbios.rts (null): */

/* Content from xdc.runtime.knl (null): */

/* Content from xdc.platform (null): */

/* Content from ti.catalog.arm.cortexm4 (null): */

/* Content from ti.catalog (null): */

/* Content from ti.catalog.peripherals.hdvicp2 (null): */

/* Content from ti.catalog.arm.peripherals.timers (null): */

/* Content from xdc.cfg (null): */

/* Content from ti.platforms.msp432 (null): */

/* Content from ti.sysbios.family.arm.msp432e4.init (null): */

/* Content from ti.sysbios (null): */

/* Content from ti.sysbios.hal (null): */

/* Content from ti.sysbios.family.arm.lm4 (null): */

/* Content from ti.sysbios.family.arm.m3 (ti/sysbios/family/arm/m3/linkcmd.xdt): */
-u _c_int00
--retain "*(.resetVecs)"
--retain "*(.vecs)"
ti_sysbios_family_arm_m3_Hwi_nvic = 0xe000e000;

/* Content from ti.sysbios.knl (null): */

/* Content from ti.sysbios.gates (null): */

/* Content from ti.sysbios.heaps (null): */

/* Content from ti.sysbios.xdcruntime (null): */

/* Content from ti.sysbios.rts.ti (ti/sysbios/rts/ti/linkcmd.xdt): */

/* Content from ti.posix.tirtos (null): */

/* Content from ti.sysbios.utils (null): */

/* Content from configPkg (null): */

/* Content from xdc.services.io (null): */



/*
 * symbolic aliases for static instance objects
 */
xdc_runtime_Startup__EXECFXN__C = 1;
xdc_runtime_Startup__RESETFXN__C = 1;
xdc_rov_runtime_Mon__checksum = 1;
xdc_rov_runtime_Mon__write = 1;


SECTIONS
{
    .bootVecs:  type = DSECT
    .resetVecs: load > 0x0
    .vecs: load > 0x20000000, type = NOLOAD



    xdc.meta: type = COPY
    xdc.noload: type = COPY
}
