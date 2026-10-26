#include "heap.h"
#include <stdio.h>

Heap h_create()
{
    return (Heap) {
        .n = 0
    };
}

bool h_empty(Heap *h)
{
    return h->n == 0;
}

bool h_full(Heap *h)
{
    return h->n == MAX_ELEMENTS - 1;
}

void h_add(Heap *h, Node item)
{
    int i;
    if (h->n == MAX_ELEMENTS - 1) {
        fprintf(stderr, "error: heap full\n");
        return;
    }
    i = ++h->n;
    while ((i != 1) && (item.f < h->values[i / 2].f)) {
        h->values[i] = h->values[i / 2];
        i /= 2;
    }
    h->values[i] = item;
}

Node h_delete(Heap *h)
{
    int parent, child;
    Node item, temp;
    if (h->n == 0) {
        fprintf(stderr, "error: heap empty\n");
        return (Node) {0};
    }

    item = h->values[1];

    temp = h->values[h->n--];
    parent = 1;
    child = 2;
    while (child <= h->n) {
        if (child < h->n && h->values[child].f > h->values[child + 1].f)
            child++;
        if (temp.f <= h->values[child].f)
            break;

        h->values[parent] = h->values[child];
        parent = child;
        child *= 2;
    }
    h->values[parent] = temp;
    return item;
}
