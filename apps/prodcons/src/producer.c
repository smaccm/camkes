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
#include <stdio.h>
#include <camkes/tls.h>
#include <Producer.h>

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
    for (unsigned int i = 0; ; i++) {
        PRINTF("Putting %u...\n", i);
        b_put(i);
        PAUSE();
    }
    return 0;
}
