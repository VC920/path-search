#include "stack.h"
#include <stdio.h>

Stack s_create()
{
    return (Stack) {
        .top = -1
    };
}

bool s_empty(Stack *s)
{
    return s->top < 0;
}

bool s_full(Stack *s)
{
    return s->top >= MAX_STACK_SIZE - 1;
}

void s_add(Stack *s, vec2 item)
{
    if (s->top >= MAX_STACK_SIZE - 1) {
        fprintf(stderr, "error: stack full\n");
        return;
    }
    s->values[++(s->top)] = item;
}

vec2 s_delete(Stack *s)
{
    if (s->top == -1) {
        fprintf(stderr, "error: stack empty\n");
        return (vec2){ -1, -1 };
    };
    return s->values[s->top--];
}
