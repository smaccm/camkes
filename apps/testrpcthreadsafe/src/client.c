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

static void callback(void *_ UNUSED) {
    printf("Callback started\n");
    for (int i = 100000; i > 0; i--) {
        int res = s_echo_int(i);
        assert(res == i);
    }

    /* Emit the event to signal the main thread we're done. */
    outgoing_emit();
}

int run() {
    /* Use the event that is connected to ourselves as a hack to get an extra
     * control thread (i.e. fork).
     */
    incoming_reg_callback(&callback, NULL);
    outgoing_emit();

    printf("Main thread started echoing\n");
    for (int i = 0; i < 100000; i++) {
        int res = s_echo_int(i);
        assert(res == i);
    }

    printf("Main thread finished, joining callback...\n");
    incoming_wait();
    printf("Done\n");

    return 0;
}
