#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "vec2.h"

/* 1 2 3 4 5 6   */
/* ^         ^   */
/* get       add */

#define MAX_QUEUE_SIZE 1024

typedef struct {
    vec2 values[MAX_QUEUE_SIZE];
    int rear;
    int front;
} Queue;

Queue q_create();
bool q_empty(Queue *q);
bool q_full(Queue *q);
void q_add(Queue *q, vec2 item);
vec2 q_delete(Queue *q);

#endif//QUEUE_H
