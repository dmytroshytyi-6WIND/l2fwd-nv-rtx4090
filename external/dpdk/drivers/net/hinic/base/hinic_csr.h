/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#ifndef _HINIC_CSR_H_
#define _HINIC_CSR_H_

#define HINIC_CSR_GLOBAL_BASE_ADDR 0x4000

/* HW interface registers */
#define HINIC_CSR_FUNC_ATTR0_ADDR 0x0
#define HINIC_CSR_FUNC_ATTR1_ADDR 0x4
#define HINIC_CSR_FUNC_ATTR2_ADDR 0x8
#define HINIC_CSR_FUNC_ATTR4_ADDR 0x10
#define HINIC_CSR_FUNC_ATTR5_ADDR 0x14

#define HINIC_FUNC_CSR_MAILBOX_DATA_OFF 0x80
#define HINIC_FUNC_CSR_MAILBOX_CONTROL_OFF 0x0100
#define HINIC_FUNC_CSR_MAILBOX_INT_OFFSET_OFF 0x0104
#define HINIC_FUNC_CSR_MAILBOX_RESULT_H_OFF 0x0108
#define HINIC_FUNC_CSR_MAILBOX_RESULT_L_OFF 0x010C

#define HINIC_CSR_DMA_ATTR_TBL_BASE 0xC80

#define HINIC_ELECTION_BASE 0x200

#define HINIC_CSR_DMA_ATTR_TBL_STRIDE 0x4
#define HINIC_CSR_DMA_ATTR_TBL_ADDR(idx)                                       \
  (HINIC_CSR_DMA_ATTR_TBL_BASE + (idx)*HINIC_CSR_DMA_ATTR_TBL_STRIDE)

#define HINIC_PPF_ELECTION_STRIDE 0x4
#define HINIC_CSR_MAX_PORTS 4
#define HINIC_CSR_PPF_ELECTION_ADDR                                            \
  (HINIC_CSR_GLOBAL_BASE_ADDR + HINIC_ELECTION_BASE)

/* MSI-X registers */
#define HINIC_CSR_MSIX_CTRL_BASE 0x2000
#define HINIC_CSR_MSIX_CNT_BASE 0x2004

#define HINIC_CSR_MSIX_STRIDE 0x8

#define HINIC_CSR_MSIX_CTRL_ADDR(idx)                                          \
  (HINIC_CSR_MSIX_CTRL_BASE + (idx)*HINIC_CSR_MSIX_STRIDE)

#define HINIC_CSR_MSIX_CNT_ADDR(idx)                                           \
  (HINIC_CSR_MSIX_CNT_BASE + (idx)*HINIC_CSR_MSIX_STRIDE)

/* EQ registers */
#define HINIC_AEQ_MTT_OFF_BASE_ADDR 0x200

#define HINIC_EQ_MTT_OFF_STRIDE 0x40

#define HINIC_CSR_AEQ_MTT_OFF(id)                                              \
  (HINIC_AEQ_MTT_OFF_BASE_ADDR + (id)*HINIC_EQ_MTT_OFF_STRIDE)

#define HINIC_CSR_EQ_PAGE_OFF_STRIDE 8

#define HINIC_AEQ_HI_PHYS_ADDR_REG(q_id, pg_num)                               \
  (HINIC_CSR_AEQ_MTT_OFF(q_id) + (pg_num)*HINIC_CSR_EQ_PAGE_OFF_STRIDE)

#define HINIC_AEQ_LO_PHYS_ADDR_REG(q_id, pg_num)                               \
  (HINIC_CSR_AEQ_MTT_OFF(q_id) + (pg_num)*HINIC_CSR_EQ_PAGE_OFF_STRIDE + 4)

#define HINIC_EQ_HI_PHYS_ADDR_REG(type, q_id, pg_num)                          \
  ((u32)(HINIC_AEQ_HI_PHYS_ADDR_REG(q_id, pg_num)))

#define HINIC_EQ_LO_PHYS_ADDR_REG(type, q_id, pg_num)                          \
  ((u32)(HINIC_AEQ_LO_PHYS_ADDR_REG(q_id, pg_num)))

#define HINIC_AEQ_CTRL_0_ADDR_BASE 0xE00
#define HINIC_AEQ_CTRL_1_ADDR_BASE 0xE04
#define HINIC_AEQ_CONS_IDX_0_ADDR_BASE 0xE08
#define HINIC_AEQ_CONS_IDX_1_ADDR_BASE 0xE0C

#define HINIC_EQ_OFF_STRIDE 0x80

#define HINIC_CSR_AEQ_CTRL_0_ADDR(idx)                                         \
  (HINIC_AEQ_CTRL_0_ADDR_BASE + (idx)*HINIC_EQ_OFF_STRIDE)

#define HINIC_CSR_AEQ_CTRL_1_ADDR(idx)                                         \
  (HINIC_AEQ_CTRL_1_ADDR_BASE + (idx)*HINIC_EQ_OFF_STRIDE)

#define HINIC_CSR_AEQ_CONS_IDX_ADDR(idx)                                       \
  (HINIC_AEQ_CONS_IDX_0_ADDR_BASE + (idx)*HINIC_EQ_OFF_STRIDE)

#define HINIC_CSR_AEQ_PROD_IDX_ADDR(idx)                                       \
  (HINIC_AEQ_CONS_IDX_1_ADDR_BASE + (idx)*HINIC_EQ_OFF_STRIDE)

/* API CMD registers */
#define HINIC_CSR_API_CMD_BASE 0xF000

#define HINIC_CSR_API_CMD_STRIDE 0x100

#define HINIC_CSR_API_CMD_CHAIN_HEAD_HI_ADDR(idx)                              \
  (HINIC_CSR_API_CMD_BASE + 0x0 + (idx)*HINIC_CSR_API_CMD_STRIDE)

#define HINIC_CSR_API_CMD_CHAIN_HEAD_LO_ADDR(idx)                              \
  (HINIC_CSR_API_CMD_BASE + 0x4 + (idx)*HINIC_CSR_API_CMD_STRIDE)

#define HINIC_CSR_API_CMD_STATUS_HI_ADDR(idx)                                  \
  (HINIC_CSR_API_CMD_BASE + 0x8 + (idx)*HINIC_CSR_API_CMD_STRIDE)

#define HINIC_CSR_API_CMD_STATUS_LO_ADDR(idx)                                  \
  (HINIC_CSR_API_CMD_BASE + 0xC + (idx)*HINIC_CSR_API_CMD_STRIDE)

#define HINIC_CSR_API_CMD_CHAIN_NUM_CELLS_ADDR(idx)                            \
  (HINIC_CSR_API_CMD_BASE + 0x10 + (idx)*HINIC_CSR_API_CMD_STRIDE)

#define HINIC_CSR_API_CMD_CHAIN_CTRL_ADDR(idx)                                 \
  (HINIC_CSR_API_CMD_BASE + 0x14 + (idx)*HINIC_CSR_API_CMD_STRIDE)

#define HINIC_CSR_API_CMD_CHAIN_PI_ADDR(idx)                                   \
  (HINIC_CSR_API_CMD_BASE + 0x1C + (idx)*HINIC_CSR_API_CMD_STRIDE)

#define HINIC_CSR_API_CMD_CHAIN_REQ_ADDR(idx)                                  \
  (HINIC_CSR_API_CMD_BASE + 0x20 + (idx)*HINIC_CSR_API_CMD_STRIDE)

#define HINIC_CSR_API_CMD_STATUS_0_ADDR(idx)                                   \
  (HINIC_CSR_API_CMD_BASE + 0x30 + (idx)*HINIC_CSR_API_CMD_STRIDE)

/* VF control registers in pf */
#define HINIC_PF_CSR_VF_FLUSH_BASE 0x1F400
#define HINIC_PF_CSR_VF_FLUSH_STRIDE 0x4

#define HINIC_GLB_DMA_SO_RO_REPLACE_ADDR 0x488C

#define HINIC_ICPL_RESERVD_ADDR 0x9204

#define HINIC_PF_CSR_VF_FLUSH_OFF(idx)                                         \
  (HINIC_PF_CSR_VF_FLUSH_BASE + (idx)*HINIC_PF_CSR_VF_FLUSH_STRIDE)

#endif /* _HINIC_CSR_H_ */
