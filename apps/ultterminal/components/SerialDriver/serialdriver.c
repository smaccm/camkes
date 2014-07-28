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
#include <SerialDriver.h>

#include <utils/util.h>
#include <ringbuffer/ringbuffer.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/* The following is a pretty quick and dirty serial driver clagged mostly from
 * libplatsupport. Ordinarily we would just link against a library that
 * provides this, but for now I think it's simpler and clearer to have the
 * driver inline. A full serial driver would provide putchar and getchar, but
 * we only need one way commuication with the device in this component. Note
 * that we could also be using interrupts instead of polling to make this more
 * efficient.
 */

#define REG_PTR(base, offset)  ((volatile uint32_t *)((char*)(base) + (offset)))
#define IMXUART_LSR             0x094
#define IMXUART_LSR_RXFIFIOE    BIT(9)
#define IMXUART_RHR             0x000
#define UART_RHR_READY_MASK    BIT(15)
#define UART_BYTE_MASK           0xFF

/* Read a character from the serial device. */
static char get(void) {
    while (true) {

        /* Busy wait for a character. */
        while ((*REG_PTR(device_registers, IMXUART_LSR) & IMXUART_LSR_RXFIFIOE) == 0);

        /* Determine whether we received a valid character and, if so, return
         * it.
         */
        uint32_t data = *REG_PTR(device_registers, IMXUART_RHR);
        if (data & UART_RHR_READY_MASK) {
            char c = (char)(data & UART_BYTE_MASK);
            return c;
        }

        /* The data we received was not a valid character. Try again. */
    }
}

int run(void) {
    ringbuffer_t *output = rb_new(char_out, sizeof(*char_out));
    if (output == NULL) {
        abort();
    }

    /* Take each received character and pass it on to the switch. */
    while (true) {
        char c = get();
        rb_transmit_byte(output, (unsigned char)c);
    }

    return 0;
}
