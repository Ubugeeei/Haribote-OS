#include "boot.h"

#define FLAGS_OVERRUN 0x0001

void queue32_init(struct Queue32 *queue, int size, int *buf, struct TASK *task) {
    queue->size = size;
    queue->buf = buf;
    queue->free = size;
    queue->flags = 0;
    queue->p = 0;
    queue->q = 0;
    queue->task = task;
    return;
}

int queue32_put(struct Queue32 *queue, int data) {
    if (queue->free == 0) {
        queue->flags |= FLAGS_OVERRUN;
        return -1;
    }
    queue->buf[queue->p] = data;
    queue->p++;
    if (queue->p == queue->size) {
        queue->p = 0;
    }
    queue->free--;
    if (queue->task != 0) {
        if (queue->task->flags != 2) {
            task_run(queue->task, -1, 0);
        }
    }
    return 0;
}

int queue32_get(struct Queue32 *queue) {
    int data;
    if (queue->free == queue->size) {
        return -1;
    }
    data = queue->buf[queue->q];
    queue->q++;
    if (queue->q == queue->size) {
        queue->q = 0;
    }
    queue->free++;
    return data;
}

int queue32_status(struct Queue32 *queue) { return queue->size - queue->free; }
