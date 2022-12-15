/*
 *  ======== ti_net_config.c ========
 *  Configured module definitions for NS
 *
 *  DO NOT EDIT - This file is generated by the SysConfig tool.
 */


/*
 *  ======== ti.net/SlNet ========
 */
#include <stdint.h>
#include <stdlib.h>
#include "string.h"

#include <ti/net/slnetif.h>
#include <ti/net/slnetutils.h>
#include <ti/net/slnetsock.h>
#include <ti/net/slnet.h>
#include <ti/ndk/slnetif/slnetifndk.h>

/* This generated function must be called after the network stack(s) are
 * initialized.
 */
int32_t ti_net_SlNet_initConfig() {
    int32_t status;

    status = SlNetIf_init(0);

    if (status == 0) {
        status = SlNetSock_init(0);
    }

    if (status == 0) {
        SlNetUtil_init(0);
    }

    /* add CONFIG_SLNET_0 interface */
    if (status == 0) {
        status = SlNetIf_add(SLNETIF_ID_2, "eth0",
                (const SlNetIf_Config_t *)&SlNetIfConfigNDK,
                1);
    }

    return (status);
}

