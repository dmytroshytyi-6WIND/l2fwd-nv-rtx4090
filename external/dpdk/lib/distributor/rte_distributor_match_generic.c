/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2017 Intel Corporation
 */

#include "distributor_private.h"
#include "rte_distributor.h"
#include <rte_mbuf.h>

void find_match_vec(struct rte_distributor *d, uint16_t *data_ptr,
                    uint16_t *output_ptr) {
  find_match_scalar(d, data_ptr, output_ptr);
}
