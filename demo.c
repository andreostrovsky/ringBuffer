#include <stdio.h>
#include <stdlib.h>
#include "ringBuffer.h"

typedef struct {
    int j;
} myStruct;

void printArray(myStruct a[], int len) {
    printf("\n");
    for (int i = 0; i < len; i++) {
        printf(" %u", a[i].j);
    }
}

int main() {
    
    ringBuffer* buffer = rb_create(7, sizeof(myStruct));
    myStruct a[buffer->len];
    
    for (int i = 1; i < 11; i++) {
        myStruct ms = {i};
        rb_write(buffer, &ms);
        rb_dump(buffer, a);
        printArray(a, rb_fillLevel(buffer));
        printf("        fillLevel: %zu", rb_fillLevel(buffer));
        printf(" head: %zu", buffer->head);
        printf(" tail: %zu", buffer->tail);
        printf("   ---   rb_write(), rb_dump()");
    }

    printf("\n");

    for (int i = 9; i < 14; i++) {
        myStruct ms = {i};
        rb_overWrite(buffer, &ms);
        rb_dump(buffer, a);
        printArray(a, rb_fillLevel(buffer));
        printf("        fillLevel: %zu", rb_fillLevel(buffer));
        printf(" head: %zu", buffer->head);
        printf(" tail: %zu", buffer->tail);
        printf("   ---   rb_overWrite(), rb_dump()");
    }

    printf("\n");

    for (int i = 0; i < 3; i++) {
        myStruct ms = {0};
        rb_read(buffer, &ms);
        printf("\n %u", ms.j);
        printf("                          fillLevel: %zu", rb_fillLevel(buffer));
        printf(" head: %zu", buffer->head);
        printf(" tail: %zu", buffer->tail);
        printf("   ---   rb_read()");
    }

    printf("\n");

    rb_dump(buffer, a);
    printArray(a, rb_fillLevel(buffer));
    printf("              fillLevel: %zu", rb_fillLevel(buffer));
    printf(" head: %zu", buffer->head);
    printf(" tail: %zu", buffer->tail);
    printf("   ---   rb_dump()\n");

    rb_destroy(buffer);

    return 0;
}
