/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

/* Usage of the keyboard in this file is based on information from
 * http://www.win.tue.nl/~aeb/linux/kbd/scancodes-11.html
 */

#include <stdio.h>
#include <Driver.h>

#define KEYBOARD_STATUS_PORT    0x64 /* Control port. */
#define KEYBOARD_DATA_PORT      0x60 /* Input/output port. */

#define KEYBOARD_CCB_WRITE	0x60 /* Write it to the Control port before write a CCB. */
#define KEYBOARD_CCB_READ	0x20 /* Write it to the Control port before read a CCB. */

#define KEYBOARD_ENABLE		0xae /* Keyboard enable command. */
#define KEYBOARD_DISABLE	0xad /* Keyboard disable command. */

static uint8_t read_status(void)
{
	char c;
	c = s_in8(KEYBOARD_STATUS_PORT);

	printf("Current Status: 0x%x\n", c);
	return c;
}

static uint8_t read_scancode(void)
{
	return s_in8(KEYBOARD_DATA_PORT);
}

static int keyboard_enable(void)
{
	s_out8(KEYBOARD_STATUS_PORT, KEYBOARD_ENABLE);
	return 0;
}

static void keyboard_interrupt_handler(void *arg)
{
	printf("Scancode: %u\n", read_scancode());
	keypress_emit();
	interrupt_reg_callback(&keyboard_interrupt_handler, NULL);
}

void kbd__init(void)
{
	int ret = 0;

	read_status();
	keyboard_enable();

	ret = interrupt_reg_callback(&keyboard_interrupt_handler, NULL);
	printf("reg callback: %d\n", ret);
}

int kbd_get_scancode(void)
{
	return read_scancode();
}

