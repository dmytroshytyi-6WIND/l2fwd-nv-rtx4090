/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2019 Intel Corporation
 */

#include <rte_cryptodev.h>
#include <rte_malloc.h>

#include "fips_dev_self_test.h"

#define IV_OFF (sizeof(struct rte_crypto_op) + sizeof(struct rte_crypto_sym_op))

#define FIPS_DEV_TEST_DATA_MAX_SIZE 8096
#define AES_CCM_AAD_PAD_SIZE 18

struct fips_dev_self_test_vector {
  const char *name;
  enum rte_crypto_sym_xform_type operation_type;

  struct {
    uint8_t data[64];
    uint16_t len;
  } digest;

  struct {
    uint8_t data[256];
    uint16_t len;
  } key;

  struct {
    uint8_t data[16];
    uint8_t len;
  } iv;

  union {
    struct {
      enum rte_crypto_cipher_algorithm algo;
    } cipher;

    struct {
      enum rte_crypto_aead_algorithm algo;
      struct {
        uint8_t data[FIPS_DEV_TEST_DATA_MAX_SIZE];
        uint16_t len;
      } aad;
    } aead;

    struct {
      enum rte_crypto_auth_algorithm algo;
    } auth;
  };

  struct {
    const uint8_t data[FIPS_DEV_TEST_DATA_MAX_SIZE];
    uint16_t len;
  } input;

  struct {
    uint8_t data[FIPS_DEV_TEST_DATA_MAX_SIZE];
    uint16_t len;
  } output;
};

#define GET_MBUF_DATA(data, len, m)                                            \
  do {                                                                         \
    len = rte_pktmbuf_pkt_len(m);                                              \
    data = rte_pktmbuf_mtod(m, uint8_t *);                                     \
  } while (0)

/* <-- SHA-x HMAC --> */
static struct fips_dev_self_test_vector SELF_TEST_SHA1_HMAC_test_vector = {
    .name = "SELF_TEST_SHA1_HMAC_test_vector",
    .operation_type = RTE_CRYPTO_SYM_XFORM_AUTH,

    .auth =
        {
            .algo = RTE_CRYPTO_AUTH_SHA1_HMAC,
        },
    .input =
        {
            .data = {0xed, 0xb2, 0xba, 0x09, 0x99, 0x61, 0xd3, 0x8f, 0xd0, 0xa0,
                     0xa6, 0xa2, 0x35, 0xd6, 0x12, 0x71, 0xcb, 0x4d, 0x49, 0x3b,
                     0x64, 0xd9, 0xde, 0x13, 0x5c, 0xbb, 0x1f, 0xe0, 0x86, 0xc4,
                     0xa4, 0xa7, 0x67, 0xbe, 0x28, 0x0d, 0xa2, 0x07, 0x98, 0x17,
                     0xb4, 0x7f, 0x6a, 0x35, 0xe1, 0xa4, 0x30, 0x7f, 0x6e, 0xfc,
                     0x6d, 0x3e, 0x11, 0xb4, 0xa7, 0xae, 0xa6, 0x86, 0xbd, 0x02,
                     0x23, 0xe0, 0x7b, 0xa9, 0xce, 0x42, 0x6c, 0xd0, 0xae, 0xe7,
                     0xef, 0x28, 0x3f, 0xa9, 0x8d, 0xe9, 0x6a, 0x1f, 0x8a, 0x17,
                     0xb3, 0x08, 0xba, 0x04, 0xb5, 0xec, 0x96, 0x16, 0xcb, 0x00,
                     0x8f, 0xca, 0x11, 0x4b, 0xa3, 0xf9, 0x8b, 0x07, 0x2d, 0x5a,
                     0xa3, 0x4a, 0x01, 0x49, 0xd9, 0xe5, 0xb8, 0xc6, 0xb6, 0x8c,
                     0x49, 0xc1, 0x01, 0x38, 0xda, 0x95, 0x36, 0xca, 0xd5, 0xd2,
                     0x34, 0xf1, 0x3d, 0x3f, 0x36, 0x4d, 0x43, 0x1f},
            .len = 128,
        },
    .key =
        {
            .data = {0x8d, 0x8d, 0x15, 0xd8, 0xa9, 0x57, 0x9a, 0xdb, 0x2d,
                     0x62},
            .len = 10,
        },
    .digest =
        {
            .data = {0x0c, 0x66, 0x2e, 0x47, 0x93, 0x93, 0x8c,
                     0xc3, 0x7f, 0x3d, 0x51, 0xd2, 0xb4, 0x05,
                     0x48, 0xec, 0x55, 0x91, 0x4f, 0x0d},
            .len = 20,
        },
};

static struct fips_dev_self_test_vector SELF_TEST_SHA224_HMAC_test_vector = {
    .name = "SELF_TEST_SHA224_HMAC_test_vector",
    .operation_type = RTE_CRYPTO_SYM_XFORM_AUTH,
    .auth =
        {
            .algo = RTE_CRYPTO_AUTH_SHA224_HMAC,
        },
    .input =
        {
            .data = {0x41, 0x18, 0x43, 0xa2, 0x13, 0x87, 0x84, 0x6f, 0x3b, 0x9e,
                     0xd5, 0xfc, 0x54, 0x5a, 0xca, 0xdf, 0xa5, 0xb7, 0x03, 0x86,
                     0xf6, 0x2d, 0xa4, 0xd9, 0xa2, 0x7b, 0x04, 0x1b, 0xee, 0xa3,
                     0xaa, 0x11, 0x99, 0x36, 0x75, 0x67, 0xb4, 0xd1, 0x1a, 0x4f,
                     0xb4, 0xe8, 0xd4, 0x6b, 0xc6, 0xc2, 0x56, 0xed, 0x62, 0xc5,
                     0x05, 0xfd, 0x23, 0xf4, 0x64, 0x5b, 0xd6, 0xb6, 0xcf, 0x45,
                     0xd1, 0xd9, 0x6d, 0x9b, 0x86, 0xd6, 0x60, 0x41, 0x57, 0x57,
                     0x3e, 0xc5, 0xac, 0xf6, 0xc5, 0x41, 0x43, 0x48, 0xca, 0x83,
                     0xc8, 0x1a, 0x73, 0x6c, 0xa6, 0xfa, 0xa6, 0x96, 0x1c, 0xfa,
                     0xc1, 0x39, 0x93, 0xb0, 0x8c, 0x50, 0x2f, 0x81, 0x6c, 0xf7,
                     0xa4, 0x20, 0xd9, 0x18, 0x4b, 0x51, 0x11, 0x46, 0x75, 0xf3,
                     0x0e, 0xe9, 0xff, 0x3d, 0xb6, 0x9c, 0x26, 0x48, 0x53, 0xd3,
                     0x9d, 0xcd, 0x42, 0xc1, 0xdd, 0x31, 0xef, 0x79

            },
            .len = 128,
        },
    .key =
        {
            .data = {0x37, 0x14, 0x70, 0x78, 0x39, 0xda, 0xf7, 0x91, 0x22,
                     0xc7, 0x82, 0x41, 0x63, 0x51, 0x38, 0x5e, 0x88, 0xa8,
                     0x1d, 0x31, 0xc9, 0xf6, 0x41, 0xd8, 0xdc, 0xe5, 0x38,
                     0xe9, 0x0e, 0x63, 0xc9, 0x58, 0x92, 0xa2, 0xea, 0x9b,
                     0x19, 0x62, 0xed, 0x0b, 0xa3, 0x72, 0xf4, 0x8e, 0x94,
                     0x74, 0xaa, 0x73, 0x0a, 0xe2},
            .len = 50,
        },
    .digest =
        {
            .data = {0x33, 0xf1, 0x7a, 0xc8, 0xa5, 0xc6, 0xb5, 0x25, 0xdb, 0x8b,
                     0x86, 0x44, 0xb6, 0xab

            },
            .len = 14,
        },
};

static struct fips_dev_self_test_vector SELF_TEST_SHA256_HMAC_test_vector = {
    .name = "SELF_TEST_SHA256_HMAC_test_vector",
    .operation_type = RTE_CRYPTO_SYM_XFORM_AUTH,
    .auth =
        {
            .algo = RTE_CRYPTO_AUTH_SHA256_HMAC,
        },
    .input =
        {
            .data = {0x1c, 0x43, 0x96, 0xf7, 0xb7, 0xf9, 0x22, 0x8e, 0x83, 0x2a,
                     0x13, 0x69, 0x20, 0x02, 0xba, 0x2a, 0xff, 0x43, 0x9d, 0xcb,
                     0x7f, 0xdd, 0xbf, 0xd4, 0x56, 0xc0, 0x22, 0xd1, 0x33, 0xee,
                     0x89, 0x03, 0xa2, 0xd4, 0x82, 0x56, 0x2f, 0xda, 0xa4, 0x93,
                     0xce, 0x39, 0x16, 0xd7, 0x7a, 0x0c, 0x51, 0x44, 0x1d, 0xab,
                     0x26, 0xf6, 0xb0, 0x34, 0x02, 0x38, 0xa3, 0x6a, 0x71, 0xf8,
                     0x7f, 0xc3, 0xe1, 0x79, 0xca, 0xbc, 0xa9, 0x48, 0x2b, 0x70,
                     0x49, 0x71, 0xce, 0x69, 0xf3, 0xf2, 0x0a, 0xb6, 0x4b, 0x70,
                     0x41, 0x3d, 0x6c, 0x29, 0x08, 0x53, 0x2b, 0x2a, 0x88, 0x8a,
                     0x9f, 0xc2, 0x24, 0xca, 0xe1, 0x36, 0x5d, 0xa4, 0x10, 0xb6,
                     0xf2, 0xe2, 0x98, 0x90, 0x4b, 0x63, 0xb4, 0xa4, 0x17, 0x26,
                     0x32, 0x18, 0x35, 0xa4, 0x77, 0x4d, 0xd0, 0x63, 0xc2, 0x11,
                     0xcf, 0xc8, 0xb5, 0x16, 0x6c, 0x2d, 0x11, 0xa2},
            .len = 128,
        },
    .key =
        {
            .data = {0x54, 0x48, 0x99, 0x8f, 0x9d, 0x8f, 0x98, 0x53,
                     0x4a, 0xdd, 0xf0, 0xc8, 0xba, 0x63, 0x1c, 0x49,
                     0x6b, 0xf8, 0xa8, 0x00, 0x6c, 0xbb, 0x46, 0xad,
                     0x15, 0xfa, 0x1f, 0xa2, 0xf5, 0x53, 0x67, 0x12,
                     0x0c, 0x19, 0x34, 0x8c, 0x3a, 0xfa, 0x90, 0xc3},
            .len = 40,
        },
    .digest =
        {
            .data = {0x7e, 0x8c, 0xba, 0x9d, 0xd9, 0xf0, 0x6e, 0xbd,
                     0xd7, 0xf9, 0x2e, 0x0f, 0x1a, 0x67, 0xc7, 0xf4,
                     0xdf, 0x52, 0x69, 0x3c, 0x21, 0x2b, 0xdd, 0x84,
                     0xf6, 0x73, 0x70, 0xb3, 0x51, 0x53, 0x3c, 0x6c},
            .len = 32,
        },
};

/* HMAC count=34 L=48 SHA384 GENERATE*/
static struct fips_dev_self_test_vector SELF_TEST_SHA384_HMAC_test_vector = {
    .name = "SELF_TEST_SHA384_HMAC_test_vector",
    .operation_type = RTE_CRYPTO_SYM_XFORM_AUTH,
    .auth =
        {
            .algo = RTE_CRYPTO_AUTH_SHA384_HMAC,
        },
    .input =
        {
            .data = {0xf5, 0x10, 0x86, 0xfe, 0x78, 0x15, 0x0f, 0xe4, 0x8b, 0xd1,
                     0x41, 0x5a, 0x47, 0x85, 0xac, 0xc0, 0x5a, 0xb8, 0x0e, 0xf0,
                     0x0b, 0x29, 0x75, 0xce, 0x78, 0x07, 0xa4, 0x21, 0x22, 0x64,
                     0xb8, 0xa1, 0xac, 0xe8, 0x0b, 0x50, 0xe0, 0xc2, 0x59, 0x0e,
                     0xf3, 0xe4, 0x21, 0x68, 0x0a, 0x70, 0x4e, 0xb2, 0xfc, 0x6d,
                     0x17, 0x55, 0x5a, 0xbf, 0x24, 0x69, 0xad, 0x56, 0xf2, 0x87,
                     0xfe, 0xa5, 0x78, 0xd8, 0x9c, 0x56, 0x0b, 0x72, 0x19, 0x3c,
                     0x7f, 0xe5, 0x96, 0x89, 0x8f, 0x10, 0x40, 0x41, 0x7e, 0x3a,
                     0x1b, 0xee, 0xff, 0x5e, 0xff, 0x96, 0x53, 0xc5, 0xe0, 0xea,
                     0xb1, 0xda, 0x52, 0xc0, 0xea, 0x3b, 0x4b, 0xc3, 0x4d, 0x0c,
                     0x2b, 0x69, 0xc8, 0x90, 0xfb, 0x26, 0x51, 0xfa, 0xf2, 0xe0,
                     0x84, 0x80, 0x3e, 0xa2, 0x8e, 0xb2, 0x01, 0x94, 0x49, 0x0a,
                     0x99, 0x2b, 0xa8, 0xc4, 0x24, 0x9d, 0x56, 0xef},
            .len = 128,
        },
    .key =
        {
            .data = {0x91, 0x7a, 0x69, 0x8c, 0x82, 0xf4, 0x4f, 0x19, 0x57,
                     0x3b, 0x64, 0x5c, 0x48, 0x79, 0xb8, 0x73, 0x0b, 0x58,
                     0xdf, 0xf4, 0xed, 0xc6, 0xa0, 0xd3, 0x21, 0xf5, 0xf1,
                     0x86, 0x58, 0xa5, 0x24, 0x66, 0x92, 0xa5, 0x5b, 0x59,
                     0x33, 0x97, 0x41, 0xae, 0x59, 0xf5, 0xfc, 0x48, 0x6d,
                     0x51, 0x5d, 0xff, 0xf8, 0xe1},
            .len = 50,
        },
    .digest =
        {
            .data = {0x77, 0xbf, 0x56, 0x15, 0xec, 0x52, 0xf7, 0x06,
                     0xca, 0x74, 0x64, 0x01, 0xe9, 0xfd, 0xe4, 0x3f,
                     0x15, 0x60, 0x52, 0x37, 0xe5, 0x50, 0xb9, 0x3a,
                     0x84, 0x72, 0xfd, 0x14, 0x4f, 0xc3, 0x9e, 0x5e,
                     0xca, 0x0f, 0xe8, 0x90, 0x83, 0x88, 0x28, 0xa0},
            .len = 40,
        },
};

/* HMAC count=28 L=64 SHA512 GENERATE*/
static struct fips_dev_self_test_vector SELF_TEST_SHA512_HMAC_test_vector = {
    .name = "SELF_TEST_SHA512_HMAC_test_vector",
    .operation_type = RTE_CRYPTO_SYM_XFORM_AUTH,
    .auth =
        {
            .algo = RTE_CRYPTO_AUTH_SHA512_HMAC,
        },
    .input =
        {
            .data = {0x0a, 0x33, 0x1c, 0xe2, 0x00, 0x89, 0xb2, 0x9e, 0x94, 0xb2,
                     0xc5, 0xf5, 0x18, 0xc8, 0xdb, 0xea, 0xd4, 0x04, 0x17, 0xa2,
                     0xa8, 0xd5, 0x00, 0x18, 0xf3, 0x2f, 0x85, 0x12, 0xb3, 0x26,
                     0x3d, 0x54, 0xed, 0xbb, 0xf3, 0x13, 0x4f, 0xf6, 0x61, 0xac,
                     0x14, 0x35, 0x3c, 0x96, 0x28, 0xc3, 0x71, 0x95, 0x8c, 0xac,
                     0xaf, 0x31, 0xfd, 0xd0, 0x25, 0x67, 0xd0, 0x37, 0x8d, 0x9e,
                     0x21, 0xa4, 0x69, 0xdd, 0x2c, 0x6d, 0x8c, 0x3a, 0xfb, 0x89,
                     0xdd, 0x96, 0x42, 0xeb, 0x58, 0x87, 0x87, 0x0e, 0x55, 0x96,
                     0x85, 0xd2, 0x0d, 0xab, 0xd3, 0x86, 0x5a, 0xc5, 0xc1, 0x46,
                     0xbe, 0xee, 0x83, 0x87, 0xa7, 0x6f, 0x91, 0xf0, 0xf1, 0x40,
                     0x4d, 0x6c, 0xad, 0xc2, 0xe6, 0x7d, 0x21, 0xb0, 0x7d, 0xd3,
                     0x0f, 0x53, 0x87, 0x1d, 0x3b, 0xf6, 0x73, 0x1f, 0x27, 0x9a,
                     0x8c, 0x04, 0x21, 0xeb, 0x20, 0xf6, 0x7f, 0x72},
            .len = 128,
        },
    .key =
        {
            .data = {0x39, 0xb8, 0x77, 0xb8, 0xe8, 0x2e, 0xcb, 0xd9, 0x74,
                     0x03, 0x25, 0x82, 0x8f, 0xaf, 0x67, 0x21, 0xc1, 0x29,
                     0x04, 0x6e, 0xb0, 0x13, 0x61, 0x44, 0xa0, 0x31, 0x82,
                     0xb1, 0x36, 0x20, 0xe2, 0x49, 0x81, 0x45, 0xa2, 0xbf,
                     0x3b, 0x03, 0xe6, 0xb6, 0x4b, 0x31, 0x7d, 0xd4, 0x8f,
                     0xcb, 0xc0, 0x18, 0xd9, 0xe7, 0xbc, 0x6e, 0x37, 0xeb,
                     0x93, 0x81, 0x78, 0xfe, 0x1f, 0xd1, 0xeb, 0xbc, 0xd9,
                     0x05, 0x6a, 0x2e, 0xf9, 0x82, 0x97, 0xf9, 0xdf, 0x3c,
                     0x66, 0xd5, 0xb2, 0xcc, 0xdc, 0x41, 0x47, 0xc4, 0x16,
                     0x76, 0x44, 0x3f, 0x8c, 0x99, 0x85, 0xbc, 0x97, 0x34,
                     0xbe, 0x2c, 0x31, 0xe7, 0x62, 0x49, 0xfc, 0x5b, 0xc4,
                     0x2a},
            .len = 100,
        },
    .digest =
        {
            .data = {0x97, 0x16, 0x8f, 0x55, 0x13, 0xc2, 0xe9, 0xbc,
                     0x4b, 0xc5, 0x25, 0xce, 0x27, 0x03, 0x74, 0x0b,
                     0xce, 0x1a, 0x06, 0xec, 0xfe, 0x99, 0xa5, 0x70,
                     0xac, 0x66, 0xc8, 0x3e, 0xde, 0x96, 0x67, 0xcc,
                     0x07, 0xed, 0xf6, 0x64, 0x61, 0x7c, 0xe5, 0x3c},
            .len = 40,
        },
};

/* <-- AES CMAC --> */
static struct fips_dev_self_test_vector SELF_TEST_AES_CMAC_test_vector = {
    .name = "SELF_TEST_AES_CMAC_test_vector",
    .operation_type = RTE_CRYPTO_SYM_XFORM_AUTH,
    .auth =
        {
            .algo = RTE_CRYPTO_AUTH_AES_CMAC,
        },
    .input =
        {
            .data = {0x57, 0x88, 0xf6, 0x1e, 0x02, 0x30, 0x47, 0x91, 0xb5, 0x2f,
                     0x40, 0x05, 0x7a, 0xbb, 0x4e, 0x04, 0x46, 0x40, 0x3e, 0xf3,
                     0x74, 0x02, 0x53, 0xdf, 0x72, 0x05, 0x96, 0x79, 0xbb, 0x2a,
                     0x6e, 0x5e, 0x05, 0x9a, 0x70, 0x9c, 0xbb},
            .len = 37,
        },
    .key =
        {
            .data = {0x18, 0x42, 0x15, 0x14, 0x5d, 0xa4, 0x9d, 0xb4, 0x17, 0xe8,
                     0xbd, 0xd5, 0x73, 0xd6, 0x28, 0x2d},
            .len = 16,
        },
    .digest =
        {
            .data = {0x8d, 0xa8, 0xcc, 0xa9, 0xb3, 0x6f, 0x68, 0x57, 0x1c, 0x6c,
                     0x0e, 0x40, 0xa3, 0xf4, 0x10},
            .len = 15,
        },
};

/* <-- AES CCM --> */
static struct fips_dev_self_test_vector SELF_TEST_AES128_CCM_test_vector = {
    .name = "SELF_TEST_AES128_CCM_test_vector",
    .operation_type = RTE_CRYPTO_SYM_XFORM_AEAD,
    .iv =
        {
            .data = {0x00, 0x50, 0x30, 0xF1, 0x84, 0x44, 0x08, 0xB5, 0x03, 0x97,
                     0x76, 0xE7, 0x0C},
            .len = 13,
        },
    .aead =
        {
            .algo = RTE_CRYPTO_AEAD_AES_CCM,
            .aad =
                {
                    .data =
                        {/* 18 bytes padding for AAD */
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x08, 0x40, 0x0F, 0xD2, 0xE1, 0x28,
                         0xA5, 0x7C, 0x50, 0x30, 0xF1, 0x84, 0x44, 0x08,
                         0xAB, 0xAE, 0xA5, 0xB8, 0xFC, 0xBA, 0x00, 0x00},
                    .len = 22,
                },
        },
    .input =
        {
            .data = {0xF8, 0xBA, 0x1A, 0x55, 0xD0, 0x2F, 0x85,
                     0xAE, 0x96, 0x7B, 0xB6, 0x2F, 0xB6, 0xCD,
                     0xA8, 0xEB, 0x7E, 0x78, 0xA0, 0x50},
            .len = 20,
        },
    .key =
        {
            .data = {0xC9, 0x7C, 0x1F, 0x67, 0xCE, 0x37, 0x11, 0x85, 0x51, 0x4A,
                     0x8A, 0x19, 0xF2, 0xBD, 0xD5, 0x2F},
            .len = 16,
        },
    .output =
        {
            .data = {0xF3, 0xD0, 0xA2, 0xFE, 0x9A, 0x3D, 0xBF,
                     0x23, 0x42, 0xA6, 0x43, 0xE4, 0x32, 0x46,
                     0xE8, 0x0C, 0x3C, 0x04, 0xD0, 0x19},
            .len = 20,
        },
    .digest =
        {
            .data = {0x78, 0x45, 0xCE, 0x0B, 0x16, 0xF9, 0x76, 0x23},
            .len = 8,
        },
};

/* <-- AES CBC --> */
static struct fips_dev_self_test_vector SELF_TEST_AES128_CBC_test_vector = {
    .name = "SELF_TEST_AES128_CBC_test_vector",
    .operation_type = RTE_CRYPTO_SYM_XFORM_CIPHER,

    .iv =
        {
            .data = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
                     0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F},
            .len = 16,
        },
    .cipher =
        {
            .algo = RTE_CRYPTO_CIPHER_AES_CBC,
        },
    .input =
        {
            .data =
                {
                    0x57, 0x68, 0x61, 0x74, 0x20, 0x61, 0x20, 0x6C,
                    0x6F, 0x75, 0x73, 0x79, 0x20, 0x65, 0x61, 0x72,
                    0x74, 0x68, 0x21, 0x20, 0x48, 0x65, 0x20, 0x77,
                    0x6F, 0x6E, 0x64, 0x65, 0x72, 0x65, 0x64, 0x20,
                },
            .len = 32,
        },
    .key =
        {
            .data = {0xE4, 0x23, 0x33, 0x8A, 0x35, 0x64, 0x61, 0xE2, 0x49, 0x03,
                     0xDD, 0xC6, 0xB8, 0xCA, 0x55, 0x7A},
            .len = 16,
        },
    .output =
        {
            .data =
                {
                    0x8B, 0x4D, 0xDA, 0x1B, 0xCF, 0x04, 0xA0, 0x31,
                    0xB4, 0xBF, 0xBD, 0x68, 0x43, 0x20, 0x7E, 0x76,
                    0xB1, 0x96, 0x8B, 0xA2, 0x7C, 0xA2, 0x83, 0x9E,
                    0x39, 0x5A, 0x2F, 0x7E, 0x92, 0xB4, 0x48, 0x1A,
                },
            .len = 32,
        },
};

static struct fips_dev_self_test_vector SELF_TEST_AES192_CBC_test_vector = {
    .name = "SELF_TEST_AES192_CBC_test_vector",
    .operation_type = RTE_CRYPTO_SYM_XFORM_CIPHER,

    .iv =
        {
            .data = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
                     0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F},
            .len = 16,
        },
    .cipher =
        {
            .algo = RTE_CRYPTO_CIPHER_AES_CBC,
        },
    .input =
        {
            .data =
                {
                    0x57, 0x68, 0x61, 0x74, 0x20, 0x61, 0x20, 0x6C,
                    0x6F, 0x75, 0x73, 0x79, 0x20, 0x65, 0x61, 0x72,
                    0x74, 0x68, 0x21, 0x20, 0x48, 0x65, 0x20, 0x77,
                    0x6F, 0x6E, 0x64, 0x65, 0x72, 0x65, 0x64, 0x20,
                },
            .len = 32,
        },
    .key =
        {
            .data = {0xE4, 0x23, 0x33, 0x8A, 0x35, 0x64, 0x61, 0xE2,
                     0x49, 0x03, 0xDD, 0xC6, 0xB8, 0xCA, 0x55, 0x7A,
                     0xD4, 0xC3, 0xA3, 0xAA, 0x33, 0x62, 0x61, 0xE0},
            .len = 24,
        },
    .output =
        {
            .data =
                {
                    0x45, 0xEE, 0x9A, 0xEA, 0x3C, 0x03, 0xFC, 0x4C,
                    0x84, 0x36, 0xB0, 0xDA, 0xB0, 0xDC, 0xF3, 0x5B,
                    0x75, 0xA7, 0xBE, 0x0E, 0xC0, 0x8D, 0x6C, 0xF8,
                    0xC1, 0x0F, 0xD0, 0x35, 0x1D, 0x82, 0xAE, 0x7C,
                },
            .len = 32,
        },
};

/* AES-256 CBC ENCRYPT*/
static struct fips_dev_self_test_vector SELF_TEST_AES256_CBC_test_vector = {
    .name = "SELF_TEST_AES256_CBC_test_vector",
    .operation_type = RTE_CRYPTO_SYM_XFORM_CIPHER,

    .iv =
        {
            .data = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
                     0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F},
            .len = 16,
        },
    .cipher =
        {
            .algo = RTE_CRYPTO_CIPHER_AES_CBC,
        },
    .input =
        {
            .data =
                {
                    0x57, 0x68, 0x61, 0x74, 0x20, 0x61, 0x20, 0x6C,
                    0x6F, 0x75, 0x73, 0x79, 0x20, 0x65, 0x61, 0x72,
                    0x74, 0x68, 0x21, 0x20, 0x48, 0x65, 0x20, 0x77,
                    0x6F, 0x6E, 0x64, 0x65, 0x72, 0x65, 0x64, 0x20,
                },
            .len = 32,
        },
    .key =
        {
            .data = {0xE4, 0x23, 0x33, 0x8A, 0x35, 0x64, 0x61, 0xE2,
                     0x49, 0x03, 0xDD, 0xC6, 0xB8, 0xCA, 0x55, 0x7A,
                     0xD4, 0xC3, 0xA3, 0xAA, 0x33, 0x62, 0x61, 0xE0,
                     0x37, 0x07, 0xB8, 0x23, 0xA2, 0xA3, 0xB5, 0x8D},
            .len = 32,
        },
    .output =
        {
            .data =
                {
                    0xF3, 0xDD, 0xF0, 0x0B, 0xFF, 0xA2, 0x6A, 0x04,
                    0xBE, 0xDA, 0x52, 0xA6, 0xFE, 0x6B, 0xA6, 0xA7,
                    0x48, 0x1D, 0x7D, 0x98, 0x65, 0xDB, 0xEF, 0x06,
                    0x26, 0xB5, 0x8E, 0xEB, 0x05, 0x0E, 0x77, 0x98,
                },
            .len = 32,
        },
};

/* DES-128 CBC ENCRYPT*/
static struct fips_dev_self_test_vector SELF_TEST_3DES_2KEY_CBC_test_vector = {
    .name = "SELF_TEST_3DES_2KEY_CBC_test_vector",
    .operation_type = RTE_CRYPTO_SYM_XFORM_CIPHER,
    .iv =
        {
            .data = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07},
            .len = 8,
        },
    .cipher =
        {
            .algo = RTE_CRYPTO_CIPHER_3DES_CBC,
        },
    .input =
        {
            .data =
                {
                    0x57, 0x68, 0x61, 0x74, 0x20, 0x61, 0x20, 0x6C,
                    0x6F, 0x75, 0x73, 0x79, 0x20, 0x65, 0x61, 0x72,
                    0x74, 0x68, 0x21, 0x20, 0x48, 0x65, 0x20, 0x77,
                    0x6F, 0x6E, 0x64, 0x65, 0x72, 0x65, 0x64, 0x20,
                },
            .len = 32,
        },
    .key =
        {
            .data = {0xE4, 0x23, 0x33, 0x8A, 0x35, 0x64, 0x61, 0xE2,
                     0x49, 0x03, 0xDD, 0xC6, 0xB8, 0xCA, 0x55, 0x7A,
                     0xE4, 0x23, 0x33, 0x8A, 0x35, 0x64, 0x61, 0xE2},
            .len = 24,
        },
    .output =
        {
            .data =
                {
                    0x28, 0x2a, 0xff, 0x15, 0x5c, 0xdf, 0xd9, 0x6b,
                    0x54, 0xbc, 0x7b, 0xfb, 0xc5, 0x64, 0x4d, 0xdd,
                    0x3e, 0xf2, 0x9e, 0xb7, 0x53, 0x65, 0x37, 0x05,
                    0xe0, 0xdf, 0xae, 0xf7, 0xc9, 0x27, 0xe4, 0xec,
                },
            .len = 32,
        },
};

static struct fips_dev_self_test_vector SELF_TEST_3DES_3KEY_CBC_test_vector = {
    .name = "SELF_TEST_3DES_3KEY_CBC_test_vector",
    .operation_type = RTE_CRYPTO_SYM_XFORM_CIPHER,

    .iv =
        {
            .data = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07},
            .len = 8,
        },
    .cipher =
        {
            .algo = RTE_CRYPTO_CIPHER_3DES_CBC,
        },
    .input =
        {
            .data =
                {
                    0x57, 0x68, 0x61, 0x74, 0x20, 0x61, 0x20, 0x6C,
                    0x6F, 0x75, 0x73, 0x79, 0x20, 0x65, 0x61, 0x72,
                    0x74, 0x68, 0x21, 0x20, 0x48, 0x65, 0x20, 0x77,
                    0x6F, 0x6E, 0x64, 0x65, 0x72, 0x65, 0x64, 0x20,
                },
            .len = 32,
        },
    .key =
        {
            .data = {0xE4, 0x23, 0x33, 0x8A, 0x35, 0x64, 0x61, 0xE2,
                     0x49, 0x03, 0xDD, 0xC6, 0xB8, 0xCA, 0x55, 0x7A,
                     0xD4, 0xC3, 0xA3, 0xAA, 0x33, 0x62, 0x61, 0xE0},
            .len = 24,
        },
    .output =
        {
            .data =
                {
                    0xd0, 0xc9, 0xdc, 0x51, 0x29, 0x97, 0x03, 0x64,
                    0xcd, 0x22, 0xba, 0x3d, 0x2b, 0xbc, 0x21, 0x37,
                    0x7b, 0x1e, 0x29, 0x23, 0xeb, 0x51, 0x6e, 0xac,
                    0xbe, 0x5b, 0xd3, 0x67, 0xe0, 0x3f, 0xc3, 0xb5,
                },
            .len = 32,
        },
};

/* <-- AES GCM --> */
static struct fips_dev_self_test_vector
    SELF_TEST_AES128_GCM_encrypt_test_vector = {
        .name = "SELF_TEST_AES128_GCM_encrypt_test_vector",
        .operation_type = RTE_CRYPTO_SYM_XFORM_AEAD,

        .iv =
            {
                .data = {0x5a, 0xdb, 0x96, 0x09, 0xdb, 0xae, 0xb5, 0x8c, 0xbd,
                         0x6e, 0x72, 0x75},
                .len = 12,
            },
        .aead =
            {
                .algo = RTE_CRYPTO_AEAD_AES_GCM,
                .aad =
                    {
                        .data = {0x88, 0x31, 0x9d, 0x6e, 0x1d, 0x3f, 0xfa,
                                 0x5f, 0x98, 0x71, 0x99, 0x16, 0x6c, 0x8a,
                                 0x9b, 0x56, 0xc2, 0xae, 0xba, 0x5a},
                        .len = 20,
                    },
            },
        .input =
            {
                .data = {0x7c, 0x0e, 0x88, 0xc8, 0x88, 0x99, 0xa7, 0x79, 0x22,
                         0x84, 0x65, 0x07, 0x47, 0x97, 0xcd, 0x4c, 0x2e, 0x14,
                         0x98, 0xd2, 0x59, 0xb5, 0x43, 0x90, 0xb8, 0x5e, 0x3e,
                         0xef, 0x1c, 0x02, 0xdf, 0x60, 0xe7, 0x43, 0xf1, 0xb8,
                         0x40, 0x38, 0x2c, 0x4b, 0xcc, 0xaf, 0x3b, 0xaf, 0xb4,
                         0xca, 0x84, 0x29, 0xbe, 0xa0, 0x63},
                .len = 51,
            },
        .key =
            {
                .data = {0xfe, 0x47, 0xfc, 0xce, 0x5f, 0xc3, 0x26, 0x65, 0xd2,
                         0xae, 0x39, 0x9e, 0x4e, 0xec, 0x72, 0xba},
                .len = 16,
            },
        .output =
            {
                .data = {0x98, 0xf4, 0x82, 0x6f, 0x05, 0xa2, 0x65, 0xe6, 0xdd,
                         0x2b, 0xe8, 0x2d, 0xb2, 0x41, 0xc0, 0xfb, 0xbb, 0xf9,
                         0xff, 0xb1, 0xc1, 0x73, 0xaa, 0x83, 0x96, 0x4b, 0x7c,
                         0xf5, 0x39, 0x30, 0x43, 0x73, 0x63, 0x65, 0x25, 0x3d,
                         0xdb, 0xc5, 0xdb, 0x87, 0x78, 0x37, 0x14, 0x95, 0xda,
                         0x76, 0xd2, 0x69, 0xe5, 0xdb, 0x3e},
                .len = 51,
            },
        .digest =
            {
                .data = {0x29, 0x1e, 0xf1, 0x98, 0x2e, 0x4d, 0xef, 0xed, 0xaa,
                         0x22, 0x49, 0xf8, 0x98, 0x55, 0x6b, 0x47},
                .len = 16,
            },
};

static struct fips_dev_self_test_vector
    SELF_TEST_AES192_GCM_encrypt_test_vector = {
        .operation_type = RTE_CRYPTO_SYM_XFORM_AEAD,
        .name = "SELF_TEST_AES192_GCM_encrypt_test_vector",
        .iv =
            {
                .data = {0x0b, 0xd4, 0x4f, 0xf4, 0xd2, 0x0c, 0x15, 0xd0, 0x4f,
                         0xc6, 0x1e, 0xe7},
                .len = 12,
            },
        .aead =
            {
                .algo = RTE_CRYPTO_AEAD_AES_GCM,
                .aad =
                    {
                        .data = {0x9e, 0xa4, 0x2c, 0x50, 0xa7, 0xfd, 0xb8, 0x5e,
                                 0x14, 0x1a, 0xa0, 0x84, 0xb4, 0x6b, 0xde,
                                 0x12},
                        .len = 16,
                    },
            },
        .input =
            {
                .data = {0x56, 0x7c, 0xcb, 0x3f, 0xa0, 0xdb, 0x89, 0x70,
                         0x8a, 0xf3, 0xff, 0x2b, 0xb0, 0x29, 0xdd, 0xec,
                         0x52, 0xc6, 0x69, 0x47, 0x58, 0x5d, 0x29, 0x1a,
                         0x28, 0x56, 0x4b, 0xf5, 0x6d, 0xb7, 0x06, 0xf7},
                .len = 32,
            },
        .key =
            {
                .data = {0x0d, 0x4a, 0x90, 0x0d, 0x1b, 0x0b, 0xb5, 0xb7,
                         0xbe, 0x24, 0x38, 0xc2, 0xba, 0x48, 0xfc, 0x45,
                         0x13, 0x4c, 0xc1, 0x98, 0x10, 0x8c, 0xf8, 0x85},
                .len = 24,
            },
        .output =
            {
                .data = {0x2f, 0x8a, 0x42, 0xcd, 0x18, 0x3b, 0x03, 0x14,
                         0xfd, 0x20, 0xa3, 0xd9, 0x7d, 0x9e, 0x0c, 0x52,
                         0x17, 0xb0, 0xf0, 0x88, 0xd2, 0xca, 0x87, 0xa8,
                         0x29, 0x0d, 0x4b, 0xae, 0x69, 0xad, 0x83, 0xf5},
                .len = 32,
            },
        .digest =
            {
                .data = {0xde, 0x41, 0x45, 0x92, 0xd7, 0x7f, 0x2f, 0x0b, 0x50,
                         0xdf, 0x4a, 0xec, 0x71, 0x4f, 0xad, 0x43},
                .len = 16,
            },
};

static struct fips_dev_self_test_vector
    SELF_TEST_AES256_GCM_encrypt_test_vector = {
        .operation_type = RTE_CRYPTO_SYM_XFORM_AEAD,
        .name = "SELF_TEST_AES256_GCM_encrypt_test_vector",
        .iv =
            {
                .data = {0x5c, 0x1b, 0x21, 0xc8, 0x99, 0x8e, 0xd6, 0x29, 0x90,
                         0x06, 0xd3, 0xf9},
                .len = 12,
            },
        .aead =
            {
                .algo = RTE_CRYPTO_AEAD_AES_GCM,
                .aad =
                    {
                        .data = {0x22, 0xed, 0x23, 0x59, 0x46, 0x23, 0x5a, 0x85,
                                 0xa4, 0x5b, 0xc5, 0xfa, 0xd7, 0x14, 0x0b,
                                 0xfa},
                        .len = 16,
                    },
            },
        .input =
            {
                .data = {0xad, 0x42, 0x60, 0xe3, 0xcd, 0xc7, 0x6b, 0xcc,
                         0x10, 0xc7, 0xb2, 0xc0, 0x6b, 0x80, 0xb3, 0xbe,
                         0x94, 0x82, 0x58, 0xe5, 0xef, 0x20, 0xc5, 0x08,
                         0xa8, 0x1f, 0x51, 0xe9, 0x6a, 0x51, 0x83, 0x88},
                .len = 32,
            },
        .key =
            {
                .data = {0x37, 0xcc, 0xdb, 0xa1, 0xd9, 0x29, 0xd6, 0x43,
                         0x6c, 0x16, 0xbb, 0xa5, 0xb5, 0xff, 0x34, 0xde,
                         0xec, 0x88, 0xed, 0x7d, 0xf3, 0xd1, 0x5d, 0x0f,
                         0x4d, 0xdf, 0x80, 0xc0, 0xc7, 0x31, 0xee, 0x1f},
                .len = 32,
            },
        .output =
            {
                .data = {0x3b, 0x33, 0x5f, 0x8b, 0x08, 0xd3, 0x3c, 0xcd,
                         0xca, 0xd2, 0x28, 0xa7, 0x47, 0x00, 0xf1, 0x00,
                         0x75, 0x42, 0xa4, 0xd1, 0xe7, 0xfc, 0x1e, 0xbe,
                         0x3f, 0x44, 0x7f, 0xe7, 0x1a, 0xf2, 0x98, 0x16},
                .len = 32,
            },
        .digest =
            {
                .data = {0x1f, 0xbf, 0x49, 0xcc, 0x46, 0xf4, 0x58, 0xbf, 0x6e,
                         0x88, 0xf6, 0x37, 0x09, 0x75, 0xe6, 0xd4},
                .len = 16,
            },
};

/* <-- AES CTR --> */
static struct fips_dev_self_test_vector SELF_TEST_AES128_CTR_test_vector = {
    .name = "SELF_TEST_AES128_CTR_test_vector",
    .operation_type = RTE_CRYPTO_SYM_XFORM_CIPHER,

    .iv =
        {
            .data = {0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9,
                     0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF},
            .len = 16,
        },
    .cipher =
        {
            .algo = RTE_CRYPTO_CIPHER_AES_CTR,
        },
    .input =
        {
            .data =
                {
                    0x6B, 0xC1, 0xBE, 0xE2, 0x2E, 0x40, 0x9F, 0x96,
                    0xE9, 0x3D, 0x7E, 0x11, 0x73, 0x93, 0x17, 0x2A,
                    0xAE, 0x2D, 0x8A, 0x57, 0x1E, 0x03, 0xAC, 0x9C,
                    0x9E, 0xB7, 0x6F, 0xAC, 0x45, 0xAF, 0x8E, 0x51,
                },
            .len = 32,
        },
    .key =
        {
            .data = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7,
                     0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C},
            .len = 16,
        },
    .output =
        {
            .data =
                {
                    0x87, 0x4D, 0x61, 0x91, 0xB6, 0x20, 0xE3, 0x26,
                    0x1B, 0xEF, 0x68, 0x64, 0x99, 0x0D, 0xB6, 0xCE,
                    0x98, 0x06, 0xF6, 0x6B, 0x79, 0x70, 0xFD, 0xFF,
                    0x86, 0x17, 0x18, 0x7B, 0xB9, 0xFF, 0xFD, 0xFF,
                },
            .len = 32,
        },
};

static struct fips_dev_self_test_vector SELF_TEST_AES192_CTR_test_vector = {
    .name = "SELF_TEST_AES192_CTR_test_vector",
    .operation_type = RTE_CRYPTO_SYM_XFORM_CIPHER,

    .iv =
        {
            .data = {0x3F, 0x69, 0xA8, 0xCD, 0xE8, 0xF0, 0xEF, 0x40, 0xB8, 0x7A,
                     0x4B, 0xED, 0x2B, 0xAF, 0xBF, 0x57},
            .len = 16,
        },
    .cipher =
        {
            .algo = RTE_CRYPTO_CIPHER_AES_CTR,
        },
    .input =
        {
            .data =
                {
                    0x01, 0x0F, 0x10, 0x1F, 0x20, 0x1C, 0x0E, 0xB8,
                    0xFB, 0x5C, 0xCD, 0xCC, 0x1F, 0xF9, 0xAF, 0x0B,
                    0x95, 0x03, 0x74, 0x99, 0x49, 0xE7, 0x62, 0x55,
                    0xDA, 0xEA, 0x13, 0x20, 0x1D, 0xC6, 0xCC, 0xCC,
                },
            .len = 32,
        },
    .key =
        {
            .data = {0xCB, 0xC5, 0xED, 0x5B, 0xE7, 0x7C, 0xBD, 0x8C,
                     0x50, 0xD9, 0x30, 0xF2, 0xB5, 0x6A, 0x0E, 0x5F,
                     0xAA, 0xAE, 0xAD, 0xA2, 0x1F, 0x49, 0x52, 0xD4},
            .len = 24,
        },
    .output =
        {
            .data =
                {
                    0x4A, 0x6C, 0xC8, 0xCC, 0x96, 0x2A, 0x13, 0x84,
                    0x1C, 0x36, 0x88, 0xE9, 0xE5, 0x94, 0x70, 0xB2,
                    0x14, 0x5B, 0x13, 0x80, 0xEA, 0xD8, 0x8D, 0x37,
                    0xFD, 0x70, 0xA8, 0x83, 0xE8, 0x2B, 0x88, 0x1E,
                },
            .len = 32,
        },
};

static struct fips_dev_self_test_vector SELF_TEST_AES256_CTR_test_vector = {
    .name = "SELF_TEST_AES256_CTR_test_vector",
    .operation_type = RTE_CRYPTO_SYM_XFORM_CIPHER,

    .iv =
        {
            .data = {0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9,
                     0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF},
            .len = 16,
        },
    .cipher =
        {
            .algo = RTE_CRYPTO_CIPHER_AES_CTR,
        },
    .input =
        {
            .data =
                {
                    0x6B, 0xC1, 0xBE, 0xE2, 0x2E, 0x40, 0x9F, 0x96,
                    0xE9, 0x3D, 0x7E, 0x11, 0x73, 0x93, 0x17, 0x2A,
                    0xAE, 0x2D, 0x8A, 0x57, 0x1E, 0x03, 0xAC, 0x9C,
                    0x9E, 0xB7, 0x6F, 0xAC, 0x45, 0xAF, 0x8E, 0x51,
                },
            .len = 32,
        },
    .key =
        {
            .data = {0x60, 0x3D, 0xEB, 0x10, 0x15, 0xCA, 0x71, 0xBE,
                     0x2B, 0x73, 0xAE, 0xF0, 0x85, 0x7D, 0x77, 0x81,
                     0x1F, 0x35, 0x2C, 0x07, 0x3B, 0x61, 0x08, 0xD7,
                     0x2D, 0x98, 0x10, 0xA3, 0x09, 0x14, 0xDF, 0xF4},
            .len = 32,
        },
    .output =
        {
            .data =
                {
                    0x60, 0x1E, 0xC3, 0x13, 0x77, 0x57, 0x89, 0xA5,
                    0xB7, 0xA7, 0xF5, 0x04, 0xBB, 0xF3, 0xD2, 0x28,
                    0xF4, 0x43, 0xE3, 0xCA, 0x4D, 0x62, 0xB5, 0x9A,
                    0xCA, 0x84, 0xE9, 0x90, 0xCA, 0xCA, 0xF5, 0xC5,
                },
            .len = 32,
        },
};

struct fips_dev_self_test_vector *self_test_vectors[] = {
    &SELF_TEST_AES128_CBC_test_vector,
    &SELF_TEST_AES192_CBC_test_vector,
    &SELF_TEST_AES256_CBC_test_vector,
    &SELF_TEST_3DES_2KEY_CBC_test_vector,
    &SELF_TEST_3DES_3KEY_CBC_test_vector,
    &SELF_TEST_AES128_CCM_test_vector,
    &SELF_TEST_SHA1_HMAC_test_vector,
    &SELF_TEST_SHA224_HMAC_test_vector,
    &SELF_TEST_SHA256_HMAC_test_vector,
    &SELF_TEST_SHA384_HMAC_test_vector,
    &SELF_TEST_SHA512_HMAC_test_vector,
    &SELF_TEST_AES_CMAC_test_vector,
    &SELF_TEST_AES128_GCM_encrypt_test_vector,
    &SELF_TEST_AES192_GCM_encrypt_test_vector,
    &SELF_TEST_AES256_GCM_encrypt_test_vector,
    &SELF_TEST_AES128_CTR_test_vector,
    &SELF_TEST_AES192_CTR_test_vector,
    &SELF_TEST_AES256_CTR_test_vector,
};

struct fips_dev_auto_test_env {
  struct rte_mempool *mpool;
  struct rte_mempool *op_pool;
  struct rte_mempool *sess_pool;
  struct rte_mempool *sess_priv_pool;
  struct rte_mbuf *mbuf;
  struct rte_crypto_op *op;
};

typedef int (*fips_dev_self_test_prepare_xform_t)(
    uint8_t, struct rte_crypto_sym_xform *, struct fips_dev_self_test_vector *,
    uint32_t, uint8_t *, uint32_t);

typedef int (*fips_dev_self_test_prepare_op_t)(
    struct rte_crypto_op *, struct rte_mbuf *,
    struct rte_cryptodev_sym_session *, uint32_t,
    struct fips_dev_self_test_vector *);

typedef int (*fips_dev_self_test_check_result_t)(
    struct rte_crypto_op *, struct fips_dev_self_test_vector *, uint32_t);

struct fips_dev_self_test_ops {
  enum rte_crypto_sym_xform_type last_operation_type;
  fips_dev_self_test_prepare_xform_t prepare_xform;
  fips_dev_self_test_prepare_op_t prepare_op;
  fips_dev_self_test_check_result_t check_result;
};

static int prepare_cipher_xform(uint8_t dev_id,
                                struct rte_crypto_sym_xform *xform,
                                struct fips_dev_self_test_vector *vec,
                                uint32_t dir, uint8_t *key, uint32_t neg_test) {
  const struct rte_cryptodev_symmetric_capability *cap;
  struct rte_cryptodev_sym_capability_idx cap_idx;
  struct rte_crypto_cipher_xform *cipher_xform = &xform->cipher;

  memset(xform, 0, sizeof(*xform));

  /** negative test, key is xored */
  if (neg_test) {
    uint32_t i;

    for (i = 0; i < vec->key.len; i++)
      key[i] ^= vec->key.data[i];
  } else
    memcpy(key, vec->key.data, vec->key.len);

  xform->type = RTE_CRYPTO_SYM_XFORM_CIPHER;

  cipher_xform->algo = vec->cipher.algo;
  cipher_xform->op = (dir == self_test_dir_enc_auth_gen)
                         ? RTE_CRYPTO_CIPHER_OP_ENCRYPT
                         : RTE_CRYPTO_CIPHER_OP_DECRYPT;
  cipher_xform->key.data = key;
  cipher_xform->key.length = vec->key.len;
  cipher_xform->iv.length = vec->iv.len;
  cipher_xform->iv.offset = IV_OFF;

  cap_idx.algo.cipher = cipher_xform->algo;
  cap_idx.type = RTE_CRYPTO_SYM_XFORM_CIPHER;

  cap = rte_cryptodev_sym_capability_get(dev_id, &cap_idx);
  if (!cap) {
    RTE_LOG(ERR, PMD, "Failed to get capability for cdev %u\n", dev_id);
    return -EACCES;
  }

  if (rte_cryptodev_sym_capability_check_cipher(cap, cipher_xform->key.length,
                                                cipher_xform->iv.length) != 0) {
    RTE_LOG(ERR, PMD, "PMD %s key length %u IV length %u\n",
            rte_cryptodev_name_get(dev_id), cipher_xform->key.length,
            cipher_xform->iv.length);
    return -EACCES;
  }

  return 0;
}

static int prepare_auth_xform(uint8_t dev_id,
                              struct rte_crypto_sym_xform *xform,
                              struct fips_dev_self_test_vector *vec,
                              uint32_t dir, uint8_t *key, uint32_t neg_test) {
  const struct rte_cryptodev_symmetric_capability *cap;
  struct rte_cryptodev_sym_capability_idx cap_idx;
  struct rte_crypto_auth_xform *auth_xform = &xform->auth;

  memset(xform, 0, sizeof(*xform));

  /** negative test, key is xored */
  if (neg_test) {
    uint32_t i;

    for (i = 0; i < vec->key.len; i++)
      key[i] ^= vec->key.data[i];
  } else
    memcpy(key, vec->key.data, vec->key.len);

  xform->type = RTE_CRYPTO_SYM_XFORM_AUTH;

  auth_xform->algo = vec->auth.algo;
  auth_xform->op = (dir == self_test_dir_enc_auth_gen)
                       ? RTE_CRYPTO_AUTH_OP_GENERATE
                       : RTE_CRYPTO_AUTH_OP_VERIFY;
  auth_xform->digest_length = vec->digest.len;
  auth_xform->key.data = key;
  auth_xform->key.length = vec->key.len;

  cap_idx.algo.auth = auth_xform->algo;
  cap_idx.type = RTE_CRYPTO_SYM_XFORM_AUTH;

  cap = rte_cryptodev_sym_capability_get(dev_id, &cap_idx);
  if (!cap) {
    RTE_LOG(ERR, PMD, "Failed to get capability for cdev %u\n", dev_id);
    return -EACCES;
  }

  if (rte_cryptodev_sym_capability_check_auth(
          cap, auth_xform->key.length, auth_xform->digest_length, 0) != 0) {
    RTE_LOG(ERR, PMD, "PMD %s key length %u Digest length %u\n",
            rte_cryptodev_name_get(dev_id), auth_xform->key.length,
            auth_xform->digest_length);
    return -EACCES;
  }

  return 0;
}

static int prepare_aead_xform(uint8_t dev_id,
                              struct rte_crypto_sym_xform *xform,
                              struct fips_dev_self_test_vector *vec,
                              uint32_t dir, uint8_t *key, uint32_t neg_test) {
  const struct rte_cryptodev_symmetric_capability *cap;
  struct rte_cryptodev_sym_capability_idx cap_idx;
  struct rte_crypto_aead_xform *aead_xform = &xform->aead;

  memset(xform, 0, sizeof(*xform));

  /** negative test, key is xored */
  if (neg_test) {
    uint32_t i;

    for (i = 0; i < vec->key.len; i++)
      key[i] ^= vec->key.data[i];
  } else
    memcpy(key, vec->key.data, vec->key.len);

  xform->type = RTE_CRYPTO_SYM_XFORM_AEAD;

  aead_xform->algo = vec->aead.algo;
  aead_xform->op = (dir == self_test_dir_enc_auth_gen)
                       ? RTE_CRYPTO_AEAD_OP_ENCRYPT
                       : RTE_CRYPTO_AEAD_OP_DECRYPT;
  aead_xform->aad_length = vec->aead.aad.len;
  aead_xform->digest_length = vec->digest.len;
  aead_xform->iv.offset = IV_OFF;
  aead_xform->iv.length = vec->iv.len;
  aead_xform->key.data = key;
  aead_xform->key.length = vec->key.len;

  cap_idx.algo.aead = aead_xform->algo;
  cap_idx.type = RTE_CRYPTO_SYM_XFORM_AEAD;

  cap = rte_cryptodev_sym_capability_get(dev_id, &cap_idx);
  if (!cap) {
    RTE_LOG(ERR, PMD, "Failed to get capability for cdev %u\n", dev_id);
    return -EACCES;
  }

  if (rte_cryptodev_sym_capability_check_aead(
          cap, aead_xform->key.length, aead_xform->digest_length,
          aead_xform->aad_length, aead_xform->iv.length) != 0) {
    RTE_LOG(ERR, PMD, "PMD %s key_len %u tag_len %u aad_len %u iv_len %u\n",
            rte_cryptodev_name_get(dev_id), aead_xform->key.length,
            aead_xform->digest_length, aead_xform->aad_length,
            aead_xform->iv.length);
    return -EACCES;
  }

  return 0;
}

static int prepare_cipher_op(struct rte_crypto_op *op, struct rte_mbuf *mbuf,
                             struct rte_cryptodev_sym_session *session,
                             uint32_t dir,
                             struct fips_dev_self_test_vector *vec) {
  struct rte_crypto_sym_op *sym = op->sym;
  uint8_t *iv = rte_crypto_op_ctod_offset(op, uint8_t *, IV_OFF);
  uint8_t *dst;
  const uint8_t *src;
  uint32_t len;

  if (dir == self_test_dir_enc_auth_gen) {
    src = vec->input.data;
    len = vec->input.len;
  } else {
    src = vec->output.data;
    len = vec->output.len;
  }

  sym->cipher.data.offset = 0;
  memcpy(iv, vec->iv.data, vec->iv.len);

  dst = (uint8_t *)rte_pktmbuf_append(mbuf, len);
  if (!dst) {
    RTE_LOG(ERR, PMD, "Error %i: MBUF too small\n", -ENOMEM);
    return -ENOMEM;
  }

  memcpy(dst, src, len);

  sym->cipher.data.length = len;

  rte_crypto_op_attach_sym_session(op, session);

  return 0;
}

static int prepare_auth_op(struct rte_crypto_op *op, struct rte_mbuf *mbuf,
                           struct rte_cryptodev_sym_session *session,
                           uint32_t dir,
                           struct fips_dev_self_test_vector *vec) {
  struct rte_crypto_sym_op *sym = op->sym;
  uint8_t *dst;

  if (vec->input.len + vec->digest.len > RTE_MBUF_MAX_NB_SEGS) {
    RTE_LOG(ERR, PMD, "Error %i: Test data too long (%u).\n", -ENOMEM,
            vec->input.len + vec->digest.len);
    return -ENOMEM;
  }

  sym->auth.data.offset = 0;

  dst = (uint8_t *)rte_pktmbuf_append(mbuf, vec->input.len + vec->digest.len);
  if (!dst) {
    RTE_LOG(ERR, PMD, "Error %i: MBUF too small\n", -ENOMEM);
    return -ENOMEM;
  }

  memcpy(dst, vec->input.data, vec->input.len);
  sym->auth.data.length = vec->input.len;
  sym->auth.digest.data = dst + vec->input.len;
  sym->auth.digest.phys_addr = rte_pktmbuf_iova_offset(mbuf, vec->input.len);

  if (dir == self_test_dir_dec_auth_verify)
    memcpy(dst + vec->input.len, vec->digest.data, vec->digest.len);

  rte_crypto_op_attach_sym_session(op, session);

  return 0;
}

static int prepare_aead_op(struct rte_crypto_op *op, struct rte_mbuf *mbuf,
                           struct rte_cryptodev_sym_session *session,
                           uint32_t dir,
                           struct fips_dev_self_test_vector *vec) {
  struct rte_crypto_sym_op *sym = op->sym;
  uint8_t *iv = rte_crypto_op_ctod_offset(op, uint8_t *, IV_OFF);
  uint8_t *dst;
  const uint8_t *src;
  uint32_t len;

  if (dir == self_test_dir_enc_auth_gen) {
    len = vec->input.len;
    src = vec->input.data;
  } else {
    len = vec->output.len;
    src = vec->output.data;
  }

  if (vec->aead.algo == RTE_CRYPTO_AEAD_AES_CCM)
    memcpy(iv + 1, vec->iv.data, vec->iv.len);
  else
    memcpy(iv, vec->iv.data, vec->iv.len);

  if (len + vec->digest.len > RTE_MBUF_MAX_NB_SEGS) {
    RTE_LOG(ERR, PMD, "Error %i: Test data too long (%u).\n", -ENOMEM,
            len + vec->digest.len);
    return -ENOMEM;
  }

  dst = (uint8_t *)rte_pktmbuf_append(
      mbuf, RTE_ALIGN_CEIL(len + vec->digest.len, 16));
  if (!dst) {
    RTE_LOG(ERR, PMD, "Error %i: MBUF too small\n", -ENOMEM);
    return -ENOMEM;
  }

  sym->m_src = mbuf;
  sym->aead.data.length = len;
  sym->aead.data.offset = 0;
  memcpy(dst, src, len);

  sym->aead.digest.data = dst + vec->input.len;
  sym->aead.digest.phys_addr = rte_pktmbuf_iova_offset(mbuf, vec->input.len);
  if (dir == self_test_dir_dec_auth_verify)
    memcpy(sym->aead.digest.data, vec->digest.data, vec->digest.len);

  len = (vec->aead.algo == RTE_CRYPTO_AEAD_AES_CCM)
            ? (vec->aead.aad.len + AES_CCM_AAD_PAD_SIZE)
            : vec->aead.aad.len;

  dst = rte_malloc(NULL, len, 16);
  if (!dst) {
    RTE_LOG(ERR, PMD, "Error %i: Not enough memory\n", -ENOMEM);
    return -ENOMEM;
  }

  sym->aead.aad.data = dst;
  sym->aead.aad.phys_addr = rte_malloc_virt2iova(dst);
  if (vec->aead.algo == RTE_CRYPTO_AEAD_AES_CCM)
    memcpy(dst, vec->aead.aad.data, vec->aead.aad.len + AES_CCM_AAD_PAD_SIZE);
  else
    memcpy(dst, vec->aead.aad.data, vec->aead.aad.len);

  rte_crypto_op_attach_sym_session(op, session);

  return 0;
}

static int check_cipher_result(struct rte_crypto_op *op,
                               struct fips_dev_self_test_vector *vec,
                               uint32_t dir) {
  struct rte_mbuf *mbuf = op->sym->m_src;
  uint8_t *data;
  const uint8_t *src;
  uint32_t len, src_len;
  int ret;

  if (!mbuf)
    return -1;

  if (dir == self_test_dir_enc_auth_gen) {
    src = vec->output.data;
    src_len = vec->output.len;
  } else {
    src = vec->input.data;
    src_len = vec->input.len;
  }

  GET_MBUF_DATA(data, len, mbuf);
  if (!len)
    return -1;

  ret = memcmp(data, src, src_len);
  if (ret != 0)
    return -1;

  return 0;
}

static int check_auth_result(struct rte_crypto_op *op,
                             struct fips_dev_self_test_vector *vec,
                             uint32_t dir) {
  struct rte_mbuf *mbuf = op->sym->m_src;
  uint8_t *data;
  uint32_t len;
  int ret;

  if (mbuf == NULL)
    return -1;

  GET_MBUF_DATA(data, len, mbuf);
  if (!len)
    return -1;

  if (dir == self_test_dir_enc_auth_gen) {
    data += vec->input.len;
    ret = memcmp(data, vec->digest.data, vec->digest.len);
    if (ret != 0)
      return -1;
  }

  return 0;
}

static int check_aead_result(struct rte_crypto_op *op,
                             struct fips_dev_self_test_vector *vec,
                             uint32_t dir) {
  struct rte_mbuf *mbuf = op->sym->m_src;
  uint8_t *data;
  const uint8_t *src;
  uint32_t len, src_len;
  int ret;

  if (!mbuf)
    return -1;

  rte_free(op->sym->aead.aad.data);

  if (dir == self_test_dir_enc_auth_gen) {
    src = vec->output.data;
    src_len = vec->output.len;
  } else {
    src = vec->input.data;
    src_len = vec->input.len;
  }

  GET_MBUF_DATA(data, len, mbuf);
  if (!len)
    return -1;

  ret = memcmp(data, src, src_len);
  if (ret != 0)
    return -1;

  if (dir == self_test_dir_enc_auth_gen) {
    data += src_len;
    ret = memcmp(data, vec->digest.data, vec->digest.len);
    if (ret != 0)
      return -1;
  }

  return 0;
}

static void init_test_op(struct fips_dev_self_test_ops *test_ops,
                         struct fips_dev_self_test_vector *vec) {
  if (test_ops->last_operation_type == vec->operation_type)
    return;

  switch (vec->operation_type) {
  case RTE_CRYPTO_SYM_XFORM_CIPHER:
    test_ops->prepare_xform = prepare_cipher_xform;
    test_ops->prepare_op = prepare_cipher_op;
    test_ops->check_result = check_cipher_result;
    break;
  case RTE_CRYPTO_SYM_XFORM_AUTH:
    test_ops->prepare_xform = prepare_auth_xform;
    test_ops->prepare_op = prepare_auth_op;
    test_ops->check_result = check_auth_result;
    break;
  case RTE_CRYPTO_SYM_XFORM_AEAD:
    test_ops->prepare_xform = prepare_aead_xform;
    test_ops->prepare_op = prepare_aead_op;
    test_ops->check_result = check_aead_result;
    break;
  default:
    break;
  }

  test_ops->last_operation_type = vec->operation_type;
}

static int run_single_test(uint8_t dev_id,
                           struct fips_dev_self_test_vector *vec,
                           const struct fips_dev_self_test_ops *test_ops,
                           struct fips_dev_auto_test_env *env, uint32_t dir,
                           uint32_t negative_test) {
  struct rte_crypto_sym_xform xform;
  struct rte_cryptodev_sym_session *sess;
  uint16_t n_deqd;
  uint8_t key[256];
  int ret;

  __rte_crypto_op_reset(env->op, RTE_CRYPTO_OP_TYPE_SYMMETRIC);
  rte_pktmbuf_reset(env->mbuf);
  env->op->sym->m_src = env->mbuf;

  ret = test_ops->prepare_xform(dev_id, &xform, vec, dir, key, negative_test);
  if (ret < 0) {
    RTE_LOG(ERR, PMD, "Error %i: Prepare Xform\n", ret);
    return ret;
  }

  sess = rte_cryptodev_sym_session_create(env->sess_pool);
  if (!sess)
    return -ENOMEM;

  ret =
      rte_cryptodev_sym_session_init(dev_id, sess, &xform, env->sess_priv_pool);
  if (ret < 0) {
    RTE_LOG(ERR, PMD, "Error %i: Init session\n", ret);
    return ret;
  }

  ret = test_ops->prepare_op(env->op, env->mbuf, sess, dir, vec);
  if (ret < 0) {
    RTE_LOG(ERR, PMD, "Error %i: Prepare op\n", ret);
    return ret;
  }

  if (rte_cryptodev_enqueue_burst(dev_id, 0, &env->op, 1) < 1) {
    RTE_LOG(ERR, PMD, "Error: Failed enqueue\n");
    return ret;
  }

  do {
    struct rte_crypto_op *deqd_op;

    n_deqd = rte_cryptodev_dequeue_burst(dev_id, 0, &deqd_op, 1);
  } while (n_deqd == 0);

  rte_cryptodev_sym_session_clear(dev_id, sess);
  rte_cryptodev_sym_session_free(sess);

  if (env->op->status != RTE_CRYPTO_OP_STATUS_SUCCESS)
    return -1;

  return test_ops->check_result(env->op, vec, dir);
}

static void fips_dev_auto_test_uninit(uint8_t dev_id,
                                      struct fips_dev_auto_test_env *env) {
  rte_pktmbuf_free(env->mbuf);
  if (env->op)
    rte_crypto_op_free(env->op);
  rte_mempool_free(env->mpool);
  rte_mempool_free(env->op_pool);
  rte_mempool_free(env->sess_pool);
  rte_mempool_free(env->sess_priv_pool);

  rte_cryptodev_stop(dev_id);
}

static int fips_dev_auto_test_init(uint8_t dev_id,
                                   struct fips_dev_auto_test_env *env) {
  struct rte_cryptodev_qp_conf qp_conf = {128, NULL, NULL};
  uint32_t sess_sz = rte_cryptodev_sym_get_private_session_size(dev_id);
  struct rte_cryptodev_config conf;
  char name[128];
  int ret;

  conf.socket_id = rte_cryptodev_socket_id(dev_id);
  conf.nb_queue_pairs = 1;
  conf.ff_disable = 0;

  ret = rte_cryptodev_configure(dev_id, &conf);
  if (ret < 0)
    return ret;

  memset(name, 0, 128);
  snprintf(name, 128, "%s%u", "SELF_TEST_MEMPOOL", dev_id);

  memset(env, 0, sizeof(*env));

  env->mpool = rte_pktmbuf_pool_create(name, 128, 0, 0, UINT16_MAX,
                                       rte_cryptodev_socket_id(dev_id));
  if (!env->mpool) {
    ret = -ENOMEM;
    goto error_exit;
  }

  memset(name, 0, 128);
  snprintf(name, 128, "%s%u", "SELF_TEST_OP_POOL", dev_id);

  env->op_pool = rte_crypto_op_pool_create(name, RTE_CRYPTO_OP_TYPE_SYMMETRIC,
                                           16, 0, 16, rte_socket_id());
  if (!env->op_pool) {
    ret = -ENOMEM;
    goto error_exit;
  }

  memset(name, 0, 128);
  snprintf(name, 128, "%s%u", "SELF_TEST_SESS_POOL", dev_id);

  env->sess_pool = rte_cryptodev_sym_session_pool_create(
      name, 128, 0, 0, 0, rte_cryptodev_socket_id(dev_id));
  if (!env->sess_pool) {
    ret = -ENOMEM;
    goto error_exit;
  }

  memset(name, 0, 128);
  snprintf(name, 128, "%s%u", "SELF_TEST_SESS_PRIV_POOL", dev_id);

  env->sess_priv_pool =
      rte_mempool_create(name, 128, sess_sz, 0, 0, NULL, NULL, NULL, NULL,
                         rte_cryptodev_socket_id(dev_id), 0);
  if (!env->sess_priv_pool) {
    ret = -ENOMEM;
    goto error_exit;
  }

  qp_conf.mp_session = env->sess_pool;
  qp_conf.mp_session_private = env->sess_priv_pool;

  ret = rte_cryptodev_queue_pair_setup(dev_id, 0, &qp_conf,
                                       rte_cryptodev_socket_id(dev_id));
  if (ret < 0)
    goto error_exit;

  env->mbuf = rte_pktmbuf_alloc(env->mpool);
  if (!env->mbuf) {
    ret = -ENOMEM;
    goto error_exit;
  }

  env->op = rte_crypto_op_alloc(env->op_pool, RTE_CRYPTO_OP_TYPE_SYMMETRIC);
  if (!env->op) {
    ret = -ENOMEM;
    goto error_exit;
  }

  ret = rte_cryptodev_start(dev_id);
  if (ret < 0)
    goto error_exit;

  return 0;

error_exit:

  fips_dev_auto_test_uninit(dev_id, env);

  return ret;
}

int fips_dev_self_test(uint8_t dev_id,
                       struct fips_dev_broken_test_config *config) {
  struct fips_dev_self_test_ops test_ops = {0};
  struct fips_dev_auto_test_env env;
  uint32_t i, j, negative_test;
  int ret;

  ret = fips_dev_auto_test_init(dev_id, &env);
  if (ret < 0) {
    RTE_LOG(ERR, PMD, "Failed to init self-test for PMD %u\n", dev_id);
    return ret;
  }

  for (i = 0; i < RTE_DIM(self_test_vectors); i++) {
    struct fips_dev_self_test_vector *vec = self_test_vectors[i];

    init_test_op(&test_ops, vec);

    for (j = 0; j < self_test_dir_max; j++) {
      if (!config)
        negative_test = 0;
      else {
        if ((config->expect_fail_test_idx == i) &&
            (config->expect_fail_dir == j))
          negative_test = 1;
        else
          negative_test = 0;
      }

      RTE_LOG(INFO, PMD, "Testing (ID %u) %s %s%s...\n", i, vec->name,
              j == self_test_dir_enc_auth_gen ? "Encrypt" : "Decrypt",
              negative_test ? " (Expect Fail)" : "");

      ret = run_single_test(dev_id, vec, &test_ops, &env, j, negative_test);
      switch (ret) {
      case 0:
        if (!negative_test)
          break;
        ret = -1;
        RTE_LOG(ERR, PMD, "PMD %u Failed test %s %s\n", dev_id, vec->name,
                j == self_test_dir_enc_auth_gen ? "Encrypt" : "Decrypt");
        goto error_exit;
      case -EACCES:
        RTE_LOG(ERR, PMD, "Not supported by %s. Skip\n",
                rte_cryptodev_name_get(dev_id));
        ret = 0;
        break;
      default:
        RTE_LOG(ERR, PMD, "PMD %u Failed test %s %s\n", dev_id, vec->name,
                j == self_test_dir_enc_auth_gen ? "Encrypt" : "Decrypt");
        goto error_exit;
      }
    }
  }

error_exit:
  fips_dev_auto_test_uninit(dev_id, &env);

  if (ret == 0) {
    RTE_LOG(INFO, PMD, "PMD %u finished self-test successfully\n", dev_id);
  }

  return ret;
}
