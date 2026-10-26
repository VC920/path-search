#include "queue.h"
#include <stdio.h>

Queue q_create()
{
    return (Queue){
        .rear  = -1,
        .front = -1
    };
}

bool q_empty(Queue *q)
{
    return q->front == q->rear;
}

bool q_full(Queue *q)
{
    return q->rear == MAX_QUEUE_SIZE - 1;
}

void q_add(Queue *q, vec2 item)
{
    if (q->rear == MAX_QUEUE_SIZE - 1) {
        fprintf(stderr, "error: queue full\n");
        return;
    }
    q->values[++q->rear] = item;
}

vec2 q_delete(Queue *q)
{
    if (q->front == q->rear) {
        fprintf(stderr, "error: queue empty\n");
        return (vec2){-1, -1};
    }
    return q->values[++q->front];
}
