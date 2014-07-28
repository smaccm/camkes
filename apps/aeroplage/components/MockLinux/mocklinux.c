/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(NICTA_GPL)
 */

/* CAmkES provides a generated header in the name of the component that
 * prototypes all the relevant generated symbols.
 */
#include <MockLinux.h>

#include <ringbuffer/ringbuffer.h>
#include <stdbool.h>
#include <stdlib.h>

/* This function is invoked by the main CAmkES thread in this component. */
int run(void) {
    ringbuffer_t *input = rb_new(keyboard_input, sizeof(*keyboard_input));
    if (input == NULL) {
        abort();
    }

    ringbuffer_t *output = rb_new(framebuffer, sizeof(*framebuffer));
    if (output == NULL) {
        abort();
    }

    /* Obviously a real Linux would be doing more than just passing through
     * characters here. In particular, network communication.
     */
    while (true) {
        char c = (char)rb_receive_byte(input);
        rb_transmit_byte(output, (unsigned char)c);
    }

    return 0;
}
