/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2017 Cavium, Inc
 */

#ifndef _RTE_PAUSE_ARM32_H_
#define _RTE_PAUSE_ARM32_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "generic/rte_pause.h"
#include <rte_common.h>

static inline void rte_pause(void) {}

#ifdef __cplusplus
}
#endif

#endif /* _RTE_PAUSE_ARM32_H_ */
