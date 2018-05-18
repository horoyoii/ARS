#pragma once

#define QUE_LEN 100

typedef struct _QUEUE *queue_ptr;

typedef struct _QUEUE {
	int front;
	int rear;
	int queArr[QUE_LEN];
}Queue;

void QueueInit(queue_ptr pq);
int QisEmpty(queue_ptr pq);

void Enqueue(queue_ptr pq, int data);
int Dequeue(queue_ptr pq);

