#include"CircularQueue.h"

void QueueInit(queue_ptr pq) {
	pq->front = 0;
	pq->rear = 0;
}

int QisEmpty(queue_ptr pq) {
	if (pq->front == pq->rear)
		return 1;
	else
		return 0;
}

int NextPosIdx(int pos) {
	if (pos == QUE_LEN - 1)
		return 0;
	else
		return pos+1;
}

void Enqueue(queue_ptr pq, int data) {
	pq->rear = NextPosIdx(pq->rear);
	pq->queArr[pq->rear] = data;
}

int Dequeue(queue_ptr pq) {
	pq->front = NextPosIdx(pq->front);
	return pq->queArr[pq->front];
}

