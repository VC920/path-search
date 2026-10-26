#pragma once
#include "vec2.h"

#define MAX_ELEMENTS 1024

typedef struct {
    vec2 pos;
    vec2 parent;
    double f;
    double g;
    double h;
} Node;

typedef struct {
    Node values[MAX_ELEMENTS];
    int n;
} Heap;

Heap h_create();
bool h_empty(Heap *h);
bool h_full(Heap *h);
void h_add(Heap *h, Node item);
Node h_delete(Heap *h);
