/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2010-2014 Intel Corporation
 */

#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include <termios.h>

#include <rte_common.h>

#include <cmdline.h>
#include <cmdline_parse.h>
#include <cmdline_rdline.h>
#include <cmdline_socket.h>

#include "cmdline_test.h"

int main(int __rte_unused argc, char __rte_unused **argv) {
  struct cmdline *cl;

  cl = cmdline_stdin_new(main_ctx, "CMDLINE_TEST>>");
  if (cl == NULL) {
    return -1;
  }
  cmdline_interact(cl);
  cmdline_stdin_exit(cl);

  return 0;
}
