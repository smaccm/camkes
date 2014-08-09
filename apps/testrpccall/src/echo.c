/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(NICTA_GPL)
 */

#include <Echo.h>

int s_echo_int(int i) {
    /* Signal poke that we've been invoked. */
    o_emit();

    /* Wait on our incoming event which will trash our reply cap if it hasn't
     * been saved.
     */
    e_wait();

    return i;
}
