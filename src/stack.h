#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "vec2.h"

#define MAX_STACK_SIZE 1024
typedef struct {
    vec2 values[MAX_STACK_SIZE];
    int top;
} Stack;

Stack s_create();
bool s_empty(Stack *s);
bool s_full(Stack *s);
void s_add(Stack *s, vec2 item);
vec2 s_delete(Stack *s);

#endif//STACK_H
