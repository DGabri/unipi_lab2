#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int length;
  int tail;
  int head;
  int *data;
} Queue;

void print_queue(Queue *queue) {
  int len = queue->length;
  printf("[ ");
  for (int i = 0; i < len; i++) {
    printf("%d, ", queue->data[i]);
  }
  printf("]\n");
}

Queue *create_queue(int length) {
  Queue *new_queue = malloc(sizeof(Queue));

  if (new_queue == NULL) {
    puts("Error creating queue struct, exiting...");
    exit(1);
  }

  new_queue->data = malloc(sizeof(int) * length);

  if (new_queue == NULL) {
    puts("Error creating queue, exiting...");
    exit(1);
  }

  new_queue->length = length;
  new_queue->tail = 0;
  new_queue->head = 0;

  return new_queue;
}

// return -1 => queue is full
// return 1 => op successful

int insert_element(Queue *queue, int elem) {
  int length = queue->length;
  int tail = queue->tail;

  if (tail < length) {
    queue->data[tail] = elem;
    queue->tail++;

  } else {
    return -1;
  }

  return 1;
}

// return -1 => queue is empty

int fifo_dequeue(Queue *queue) {
  int tail = queue->tail;
  int head = queue->head;

  // queue empty
  if (head == -1 || head > tail) {
    return -1;
  }

  int popped_elem = queue->data[head];
  queue->data[head] = 0;
  queue->head++;

  return popped_elem;
}

int lifo_dequeue(Queue *queue) {
  int tail = queue->tail;
  int head = queue->tail;

  // queue empty
  if (head == -1 || head > tail) {
    return -1;
  }

  int popped_elem = queue->data[tail];
  queue->tail--;

  return popped_elem;
}

int main(int arg, char *argv[]) {

  Queue *new = create_queue(6);

  for (int i = 1; i < 4; i++) {
    insert_element(new, i * 2);
    printf("Inserted: %d\n", i * 2);
    print_queue(new);
    printf("=============\n");
  }

  for (int i = 0; i < 6; i++) {
    int elem = fifo_dequeue(new);
    printf("Dequeued: %d\n", elem);
    print_queue(new);
    printf("=============\n");
  }
  for (int i = 0; i < 5; i++) {
    insert_element(new, i);
    printf("Inserted: %d\n", i);
    print_queue(new);
    printf("=============\n");
  }

  free(new->data);
  free(new);
}