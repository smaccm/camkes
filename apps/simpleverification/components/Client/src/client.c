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
#include <Client.h>

int run() {
    char s;
    int i = 42, j;
    int p, p1, p2;

    printf("Starting the client\n");
    printf("-------------------\n");

    j = RPCFrom_echo_int(i);
    printf("echo_int: %d -> %d\n",i, j);

    p = 123;
    p2 = RPCFrom_echo_parameter(p, &p1);
    printf("echo_parameter: %d -> %d (returned = %d)\n", p, p1, p2);

    p = 100;
    RPCFrom_increment_parameter(&p);
    printf("increment_parameter: 100 -> %d\n", p);

    s = 'a';
    printf("incrementing '%c' -> ", s);
    RPCFrom_increment_char(&s);
    printf("'%c'\n", s);

    uint64_t x = 0xcafebeefcafebeefUL;
    printf("incrementing %llu -> ", x);
    RPCFrom_increment_64(&x);
    printf("%llu\n", x);

    printf("After the client\n");
    return 0;
}
