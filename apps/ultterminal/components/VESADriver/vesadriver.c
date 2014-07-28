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
#include <VESADriver.h>

#include <ringbuffer/ringbuffer.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* This component, in the full system, would be an actual VESA (or VGA or
 * whatever) driver. For simplicity it's currently just implemented as a
 * console driver. We only provide the ability to write to the console, not
 * read from it, as reading from an actual display would make no sense.
 */

#define REG_PTR(base, offset)  ((volatile uint32_t *)((char*)(base) + (offset)))
#define IMXUART_LSR             0x094
#define IMXUART_LSR_TXFIFOE     BIT(13)
#define IMXUART_THR             0x040

#define print(args...) \
    do { \
        char _buffer[100]; \
        sprintf(_buffer, args); \
        for (char *_p = _buffer; *_p != '\0'; _p++) { \
            put(*_p); \
        } \
    } while (0)

#define SIDE_LENGTH 30

static void put(char c) {
    if (*REG_PTR(mock_hdmi, IMXUART_LSR) & IMXUART_LSR_TXFIFOE) {
        *REG_PTR(mock_hdmi, IMXUART_THR) = c;
    }
}

static void write_to(int x, int y, char c) {
    print("\033[%d;%dH%c", y, x + 1, c);
}

/* Draw coloured borders around each input's virtual framebuffer. */
static void borders(void) {
    /* Clear the screen. */
    print("\033[2J");

    /* Switch to magenta. */
    print("\033[35m");

    /* Draw the 'low' client's box. */
    for (int i = 5; i < 5 + SIDE_LENGTH; i++) {
        write_to(i, 5, '+');
        write_to(i, 5 + SIDE_LENGTH, '+');
        write_to(5, i, '+');
        write_to(4 + SIDE_LENGTH, i, '+');
    }

    /* Switch to cyan. */
    print("\033[36m");

    /* Draw the 'high' client's box. */
    for (int i = 10 + SIDE_LENGTH; i < 10 + 2 * SIDE_LENGTH; i++) {
        write_to(i, 5, '+');
        write_to(i, 5 + SIDE_LENGTH, '+');
        write_to(10 + SIDE_LENGTH, i - 5 - SIDE_LENGTH, '+');
        write_to(9 + 2 * SIDE_LENGTH, i - 5 - SIDE_LENGTH, '+');
    }

    /* Reset colours. */
    print("\033[0m");
}

/* Write a character to the 'low' framebuffer. */
static void write_low(char c) {
    const int offsetx = 6;
    const int offsety = 6;
    static int posx = 0;
    static int posy = 0;
    write_to(offsetx + posx, offsety + posy, c);
    posx++;
    if (posx > SIDE_LENGTH - 3) {
        posx = 0;
        posy++;
        if (posy > SIDE_LENGTH - 3) {
            posy = 0;
        }
    }
}

/* Write a character to the 'high' framebuffer. */
static void write_high(char c) {
    const int offsetx = SIDE_LENGTH + 11;
    const int offsety = 6;
    static int posx = 0;
    static int posy = 0;
    write_to(offsetx + posx, offsety + posy, c);
    posx++;
    if (posx > SIDE_LENGTH - 3) {
        posx = 0;
        posy++;
        if (posy > SIDE_LENGTH - 3) {
            posy = 0;
        }
    }
}

/* This function is invoked by the main CAmkES thread in this component. */
int run(void) {
    ringbuffer_t *low = rb_new(low_input, sizeof(*low_input));
    if (low == NULL) {
        abort();
    }

    ringbuffer_t *high = rb_new(high_input, sizeof(*high_input));
    if (high == NULL) {
        abort();
    }

    borders();

    /* Check both inputs for data and pass it to the relevant framebuffer. */
    while (true) {
        char c;

        if ((c = (char)rb_poll_byte(low)) != 0) {
            write_low(c);
        }

        if ((c = (char)rb_poll_byte(high)) != 0) {
            write_high(c);
        }
    }

    return 0;
}
