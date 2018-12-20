#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct queue {
    int front, end, size;
    unsigned capacity;
    int *array;
} Queue;
 
Queue *createQueue(unsigned capacity);
bool isFull(Queue *queue);
bool isEmpty(Queue *queue);
void enqueue(Queue *queue, int item);
int dequeue(Queue *queue);
int front(Queue *queue);
int top(Queue *queue);
void display(Queue *queue);

int main() {
    Queue *queue;
    queue = createQueue(20);
    for(int i = 0; i < 20; i++){
        enqueue(queue, i);
    }
    display(queue);
    dequeue(queue);
    dequeue(queue);
    display(queue);
}

Queue *createQueue(unsigned capacity) {
    Queue *queue = (Queue*) malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->end = -1; 
    queue->size = 0; 
    queue->array = (int*) malloc(queue->capacity * sizeof(int));
    return queue;
}

bool isFull(Queue *queue) {  
    return (queue->size == queue->capacity);  
}

bool isEmpty(Queue *queue) {  
    return (queue->size == 0); 
}
 

void enqueue(Queue *queue, int item) {
    if (!isFull(queue)){
        queue->array[queue->end++] = item;
        queue->size++;
    }
}

int dequeue(Queue *queue) {
    if (!isEmpty(queue)) {
        int item = queue->array[queue->front];
        queue->front = (queue->front + 1)%queue->capacity;
        queue->size = queue->size - 1;
        return item;
    }
}

int front(Queue *queue) {
    if (!isEmpty(queue))
        return queue->array[queue->front];
}

int top(Queue *queue) {
    if (!isEmpty(queue))
        return queue->array[queue->end];
}

void display(Queue *queue) {
    for(int i = queue->front; i < queue->end; i++) {
        printf("%d ", queue->array[i]);
    }
    printf("\n");
}