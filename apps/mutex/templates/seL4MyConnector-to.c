/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <assert.h>
#include <sel4/sel4.h>
#include <sync/mutex.h>

/*- set ep = alloc('ep', seL4_EndpointObject, read=True, write=True) -*/
/*- set aep = alloc('aep', seL4_AsyncEndpointObject, read=True, write=True) -*/

static sync_mutex_t mutex;

/* We implement the 'to' side of this interface, removing the need for the user
 * to implement it.
 */
int /*? me.to_interface.name ?*/_lock(void) {
    return sync_mutex_lock(&mutex);
}

int /*? me.to_interface.name ?*/_unlock(void) {
    return sync_mutex_unlock(&mutex);
}

void /*? me.to_interface.name ?*/__init(void) {
    int result = sync_mutex_init(&mutex, /*? aep ?*/);
    assert(result == 0);
}

int /*? me.to_interface.name ?*/__run(void) {
    while (1) {
        seL4_MessageInfo_t info = seL4_Wait(/*? ep ?*/, NULL);
        assert(seL4_MessageInfo_get_length(info) == 1);
        if (seL4_GetMR(0) == 0) {
            (void)sync_mutex_lock(&mutex);
        } else {
            (void)sync_mutex_unlock(&mutex);
        }
        seL4_Notify(/*? ep ?*/, 0 /* ignored */);
    }

    assert(!"unreachable");
    return -1;
}
