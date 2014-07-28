/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(NICTA_GPL)
 */

#include <assert.h>
#include <stdio.h>
#include <Client.h>

int run() {
    printf("Client started\n");

    int i = 42;
    i = s_echo_int(i);
    assert(i == 42);

    printf("Client done\n");

    return 0;
}
