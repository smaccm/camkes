/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <stdlib.h>
#include <sel4/sel4.h>

/*- set ep = alloc('ep', seL4_EndpointObject, read=True, write=True) -*/

int /*? me.from_interface.name ?*/__run(void) {
    /* No setup required */
    return 0;
}

int /*? me.from_interface.name ?*/_lock(void) {
    seL4_Notify(/*? ep ?*/, 0);
    (void)seL4_Wait(/*? ep ?*/, NULL);
    return 0;
}

int /*? me.from_interface.name ?*/_unlock(void) {
    seL4_Notify(/*? ep ?*/, 1);
    (void)seL4_Wait(/*? ep ?*/, NULL);
    return 0;
}
