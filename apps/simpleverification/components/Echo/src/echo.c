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

void RPCTo__init(void) {
}

int RPCTo_echo_int(int i) {
    return i;
}

int RPCTo_echo_parameter(int pin, int *pout) {
    *pout = pin;
    return pin;
}

void RPCTo_increment_parameter(int *x) {
    *x = *x + 1;
}

int RPCTo_echo_char(char i) {
    return (int)i;
}

void RPCTo_increment_char(char *x) {
    *x = *x + 1;
}

void RPCTo_increment_64(uint64_t *x) {
    *x = *x + 1;
}
