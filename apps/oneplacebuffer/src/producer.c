/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(NICTA_GPL)
 */

#include <Producer.h>

int run(void) {
    for (unsigned int i = 0; ; i++) {
        b_put(i);
    }
    return 0;
}
