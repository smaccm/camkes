/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(NICTA_GPL)
 */

#include <autoconf.h>
#include <assert.h>
#include <stdio.h>
#include <sync/spinlock.h>
#include <camkes/tls.h>
#include <Buffer.h>

static unsigned int buffer[128];
static unsigned int buffer_sz = sizeof(buffer) / sizeof(buffer[0]);
static unsigned int next_write = 0;
static unsigned int next_read = 0;

static sync_spinlock_t lock;

#ifdef CONFIG_PRODCONS_DEBUG
    #define PRINTF(format, args...) \
        printf("%s, thread %d: " format, get_instance_name(), \
            camkes_get_tls()->thread_index, ## args)
#else
    #define PRINTF(args...) /* Nothing */
#endif

void pre_init(void) {
    PRINTF("Initialising lock...\n");
    int result = sync_spinlock_init(&lock);
    assert(result == 0);
}

void incoming_put(unsigned int value) {
    PRINTF("Received %u, waiting for lock...\n", value);
    sync_spinlock_lock(&lock);

    PRINTF("Writing %u...\n", value);
    buffer[next_write] = value;
    next_write = (next_write + 1) % buffer_sz;

    PRINTF("Releasing lock...\n");
    sync_spinlock_unlock(&lock);
}

unsigned int outgoing_get(void) {
    PRINTF("Received get request, waiting for lock...\n");
    sync_spinlock_lock(&lock);

    unsigned int value = buffer[next_read];
    next_read = (next_read + 1) % buffer_sz;
    PRINTF("Read %u...\n", value);

    PRINTF("Releasing lock...\n");
    sync_spinlock_unlock(&lock);

    return value;
}
