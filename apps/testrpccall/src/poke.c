/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(NICTA_GPL)
 */

#include <Poke.h>
#include <stdio.h>
#include <limits.h>

int run() {
    /* Wait for echo to have been invoked. */
    o_wait();

    /* Spin for a long time to make sure echo reaches its Wait and is blocked
     * on the endpoint when we signal it below.
     */
    for (int i = 0; i < INT_MAX; i++) {
        asm volatile ("");
    }

    printf("Poke: signalling echo\n");
    e_emit();

    return 0;
}
