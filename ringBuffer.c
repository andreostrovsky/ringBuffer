#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <omp.h>
#include "ringBuffer.h"

static uint32_t uppow2(uint32_t v) {
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

ringBuffer* rb_create(size_t len, size_t size) {
    size_t upsize = uppow2(len);
    ringBuffer* buffer = malloc(sizeof(ringBuffer) + (upsize * size));
    if (buffer == NULL) { return NULL; }
    memset(buffer, 0, sizeof(ringBuffer) + (upsize * size));
    buffer->len = upsize;
    buffer->size = size;
    return buffer;
}

void rb_destroy(ringBuffer* r) {
    free(r);
}

size_t rb_fillLevel(ringBuffer* r) {
    int const mask = (r->head - r->tail) >> sizeof(int) * 7;
    return ((r->head - r->tail) ^ mask) - mask;
}

void rb_reset(ringBuffer* r) {
    r->head = r->tail = 0;
}

void rb_write(ringBuffer* r, void* src) {
    if (rb_fillLevel(r) != r->len) {
        memcpy(&r->A[(r->tail & r->len-1) * r->size], src, r->size);
        r->tail++;
    }
}

void rb_overWrite(ringBuffer* r, void* src) {
    memcpy(&r->A[(r->tail & r->len-1) * r->size], src, r->size);
    if (rb_fillLevel(r) == r->len) {
        r->head++;
    }
    r->tail++;
}

void rb_read(ringBuffer* r, void* dest) {
    if (rb_fillLevel(r) != 0) {
        memcpy(dest, &r->A[(r->head & r->len-1) * r->size], r->size);
        r->head++;
    }
}

void rb_dump(ringBuffer* r, void* dest) {
    omp_set_num_threads(omp_get_num_procs());
    #pragma omp parallel for schedule(static)
    for (size_t i = 0; i < rb_fillLevel(r); i++) {
        memcpy(dest + (i * r->size), &r->A[((r->head + i) & r->len-1) * r->size], r->size);
    }
}