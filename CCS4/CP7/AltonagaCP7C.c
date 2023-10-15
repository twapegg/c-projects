#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5

typedef struct
{
    int front;
    int rear;
    int count;
    int data[MAX_QUEUE_SIZE];
} CircularQueue;

void CreateQueue(CircularQueue *queue)
{
    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
}

int FullQueue(CircularQueue *queue)
{
    return queue->count == MAX_QUEUE_SIZE;
}

int EmptyQueue(CircularQueue *queue)
{
    return queue->count == 0;
}

void Enqueue(CircularQueue *queue, int item)
{
    if (!FullQueue(queue))
    {
        queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
        queue->data[queue->rear] = item;
        queue->count++;
    }
    else
    {
        printf("Queue is full\n");
    }
}

int Dequeue(CircularQueue *queue)
{
    int item = -1;
    if (!EmptyQueue(queue))
    {
        item = queue->data[queue->front];
        queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
        queue->count--;
    }
    else
    {
        printf("Queue is empty\n");
    }
    return item;
}

void Display(CircularQueue *queue)
{
    int i;
    if (!EmptyQueue(queue))
    {
        printf("Queue: ");
        for (i = queue->front; i != queue->rear; i = (i + 1) % MAX_QUEUE_SIZE)
        {
            printf("%d ", queue->data[i]);
        }
        printf("%d ", queue->data[i]);
        printf("\n");
    }
    else
    {
        printf("Queue is empty\n");
    }
}

int main()
{
    CircularQueue queue;
    CreateQueue(&queue);

    Enqueue(&queue, 10);
    Enqueue(&queue, 20);
    Enqueue(&queue, 30);
    Enqueue(&queue, 40);
    Enqueue(&queue, 50);
    Enqueue(&queue, 60);

    printf("Dequeued item: %d\n", Dequeue(&queue));
    printf("Dequeued item: %d\n", Dequeue(&queue));
    printf("Dequeued item: %d\n", Dequeue(&queue));
    printf("Dequeued item: %d\n", Dequeue(&queue));
    printf("Dequeued item: %d\n", Dequeue(&queue));
    printf("Dequeued item: %d\n", Dequeue(&queue));

    return 0;
}
