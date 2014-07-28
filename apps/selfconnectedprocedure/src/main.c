/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(NICTA_GPL)
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Foo.h>

static char *msg1 = "hello", *msg2 = "world";

int run() {
    char *res;

    printf("Started\n");

    while (1) {
        printf("Sending \"%s\"\n", msg1);
        res = outgoing_echo_string(msg1);
        printf("Received \"%s\"\n", res);
        free(res);

        printf("Sending \"%s\"\n", msg2);
        res = outgoing_echo_string(msg2);
        printf("Received \"%s\"\n", res);
        free(res);
    }

    return 0;
}

char *incoming_echo_string(char *s) {
    static char *res = NULL;
    if (res != NULL) {
        /* We've already run once and need to reclaim memory. */
        free(res);
    }

    res = (char*)malloc(sizeof(char) * (strlen(msg1) + 1));
    assert(res != NULL);

    if (!strcmp(s, msg1)) {
        strcpy(res, msg2);
    } else {
        strcpy(res, msg1);
    }

    return res;
}
