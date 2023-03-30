#include "xerrori.h"
#include <pthread.h>
#include <time.h>

#define line __LINE__
#define file __FILE__

// node struct
typedef struct node {
  int key;
  struct node *next;
  struct node *prev;

} Node;

// queue struct
typedef struct {
  int currently_inserted_elements;
  Node *head;
  Node *tail;

  // sycnronization vars
  pthread_mutex_t lock;
  pthread_cond_t not_empty;

} Queue;

// initialize the queue
void init_queue(Queue *queue) {
  // init values
  queue->head = NULL;
  queue->tail = NULL;
  queue->currently_inserted_elements = 0;

  // init threading vars
  pthread_mutex_init(&queue->lock, NULL);
  pthread_cond_init(&queue->not_empty, NULL);
}

void destroy_queue_sync_var(Queue *queue) {
  // init threading vars
  pthread_mutex_destroy(&queue->lock);
  pthread_cond_destroy(&queue->not_empty);
}

void free_queue(Queue *queue) {

  Node *current = queue->head;
  Node *next;

  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }

  free(queue->tail);
  destroy_queue_sync_var(queue);
  free(queue);
}

// function to insert a new node inside the queue
void push(Queue *queue, int node_value) {

  Node *new_node = malloc(sizeof(Node));
  // init new_node node
  new_node->key = node_value;
  new_node->next = NULL;
  new_node->prev = NULL;

  if (new_node == NULL) {
    printf("Node malloc error...\n");
    free_queue(queue);
  }

  pthread_mutex_lock(&queue->lock);

  // no new_node is present inside the queue
  if (queue->currently_inserted_elements == 0) {
    queue->head = new_node;
    queue->tail = new_node;
    queue->currently_inserted_elements++;
  }
  // one node is already present in the queue
  else {
    queue->tail->next = new_node;
    new_node->prev = queue->tail;
    queue->currently_inserted_elements++;
  }

  pthread_cond_signal(&queue->not_empty);
  pthread_mutex_unlock(&queue->lock);
}

// function to insert a pop the head node from the queue
int pop(Queue *queue) {
  pthread_mutex_lock(&queue->lock);

  // queue is empty wait until someone pushes an element
  while (queue->head == NULL) {
    pthread_cond_wait(&queue->not_empty, &queue->lock);
  }

  //update head->next->prev, update head, free old_head
  Node *old_head = queue->head;

  int elem = queue->head->key;

  if (queue->head == queue->tail) {
    queue->head = NULL;
    queue->tail = NULL;
  } else {
    queue->head = old_head->next;
    queue->head->prev = NULL;
  }

  free(old_head);

  pthread_mutex_unlock(&queue->lock);

  return  elem;
}

int main(int argc, char *argv[]) {

  return 0;
}