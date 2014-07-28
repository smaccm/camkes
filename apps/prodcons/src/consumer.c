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
#include <camkes/tls.h>
#include <Consumer.h>

#ifdef CONFIG_PRODCONS_DEBUG
    #define PRINTF(format, args...) \
        printf("%s, thread %d: " format, get_instance_name(), \
            camkes_get_tls()->thread_index, ## args)

    #define PAUSE() \
        do { \
            for (unsigned int i = 0; i < 10000; i++) { \
                asm volatile (""); \
            } \
        } while (0)
#else
    #define PRINTF(args...) /* Nothing */
    #define PAUSE() /* Nothing */
#endif

int run(void) {
    /* Let the producer fill the buffer a little. */
    for (int i = 0; i < 10; i++) {
        PAUSE();
    }

    while (1) {
        unsigned int value = b_get();
        PRINTF("Got %u...\n", value);
        PAUSE();
    }
    return 0;
}
