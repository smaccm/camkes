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
#include <stdlib.h>
#include <Client.h>
#include <camkes/dma.h>

int run(void) {
    printf("Starting client...\n");

    printf("Allocating some DMA pages...\n");
    void *buffers[100];
    int i;
    for (i = 0; i < sizeof(buffers) / sizeof(void*); i++) {
        buffers[i] = camkes_dma_alloc_page();
        if (buffers[i] == NULL) {
            printf("Ran out of memory after %d of them\n", i);
            break;
        }
    }

    printf("Reversing some offsets into them...\n");
    for (int j = 0; j < i; j++) {
        printf(" vaddr %p reversed to %p\n", buffers[j] + j * 13, (void*)camkes_dma_get_paddr(buffers[j] + j * 13));
    }

    printf("Freeing them...\n");
    for (int j = 0; j < i; j++) {
        camkes_dma_free_page(buffers[i]);
    }

    printf("Done.\n");
    return 0;
}
