/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(NICTA_GPL)
 */

#include <stdio.h>
#include <Foo.h>

int run(void) {
    printf("Started up\n");

    while(1) {
        printf("Emitting...\n");
        outgoing_emit();

        printf("Waiting...\n");
        incoming_wait();

        printf("Got event!\n");
    }
    return 0;
}
