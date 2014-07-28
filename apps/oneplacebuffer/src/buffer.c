/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(NICTA_GPL)
 */

#include <Buffer.h>

static unsigned int buffer;

void incoming_put(unsigned int value) {
    buffer = value;
}

unsigned int outgoing_get(void) {
    return buffer;
}