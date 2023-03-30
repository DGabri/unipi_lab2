#include "xerrori.h"
#include <pthread.h>
#include <stdio.h>
#include <time.h>

#define line __LINE__
#define file __FILE__

// node struct
typedef struct node {
  int key;
  struct node *next;

} Node;

// queue struct
typedef struct {
  int currently_inserted_elements;
  // termination condition
  int total_inserted_element;
  int total_removed_element;
  int producers_count;
  int finished_producers;
  Node *head;
  Node *tail;

  // sycnronization vars
  pthread_mutex_t lock;
  pthread_cond_t not_empty;

} Queue;

// initialize the queue
void init_queue(Queue *queue, int producers_num) {
  // init values
  queue->producers_count = producers_num;
  queue->currently_inserted_elements = 0;
  queue->total_inserted_element = 0;
  queue->total_removed_element = 0;
  queue->finished_producers = 0;
  queue->head = NULL;
  queue->tail = NULL;

  // init threading vars
  xpthread_mutex_init(&queue->lock, NULL, line, file);
  xpthread_cond_init(&queue->not_empty, NULL, line, file);
}

void destroy_queue_sync_var(Queue *queue) {
  // init threading vars
  xpthread_mutex_destroy(&queue->lock, line, file);
  xpthread_cond_destroy(&queue->not_empty, line, file);
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
  if (new_node == NULL) {
    printf("Node malloc error...\n");
    free_queue(queue);
  }
  
  // init new_node node
  new_node->key = node_value;
  new_node->next = NULL;


  xpthread_mutex_lock(&queue->lock, line, file);

  // no new_node is present inside the queue
  if (queue->currently_inserted_elements == 0) {
    queue->head = new_node;
    queue->tail = new_node;
    queue->currently_inserted_elements++;
  }
  // one node is already present in the queue
  else {
    queue->tail->next = new_node;
    queue->tail = new_node;
    queue->currently_inserted_elements++;
  }
  // update number of inserted elements
  queue->total_inserted_element++;

  free(new_node);
  xpthread_cond_signal(&queue->not_empty, line, file);
  xpthread_mutex_unlock(&queue->lock, line, file);
}

// function to insert a pop the head node from the queue
int pop(Queue *queue) {
  xpthread_mutex_lock(&queue->lock, line, file);

  // queue is empty wait until someone pushes an element
  while (queue->head == NULL) {
    printf("Waiting queue to have some elements\n");
    xpthread_cond_wait(&queue->not_empty, NULL, line, file);
  }

  // update head->next->prev, update head, free old_head
  Node *old_head = queue->head;
  int elem = queue->head->key;
  queue->head = queue->head->next;

  free(old_head);
  queue->total_removed_element++;
  xpthread_mutex_unlock(&queue->lock, line, file);

  return elem;
}

void *producer(void *arg) {
  Queue *queue = (Queue *)arg;

  int iterations = 0;
  srand(time(NULL));

  while (iterations < 20) {
    int number = rand() % 100;
    // printf("Producer %lu inserted: %d\n", pthread_self(), number);
    push(queue, number);
    iterations++;
  }

  xpthread_mutex_lock(&queue->lock, line, file);
  queue->finished_producers++;
  xpthread_mutex_unlock(&queue->lock, line, file);

  printf("Producer %lu finished\n", pthread_self());

  return NULL;
}

void *consumer(void *arg) {
  Queue *queue = (Queue *)arg;

  while (1) {
    printf("Removed: %d\n", pop(queue));

    // termination condition
    xpthread_mutex_lock(&queue->lock, line, file);

    if ((queue->finished_producers == queue->producers_count) &&
        (queue->total_inserted_element == queue->total_removed_element)) {
      break;
    }
    xpthread_mutex_unlock(&queue->lock, line, file);
  }

  xpthread_mutex_unlock(&queue->lock, line, file);
  return NULL;
}

int main(int argc, char *argv[]) {

  if (argc != 3) {
    puts("Insert: 1- consumer thread num 2- producer thread num");
    exit(1);
  }

  Queue *shared_queue = malloc(sizeof(Queue));
  int consumers_num = atoi(argv[1]);
  int producers_num = atoi(argv[2]);

  // intialize queue
  init_queue(shared_queue, producers_num);

  pthread_t producers[producers_num];
  pthread_t consumers[consumers_num];

  // start producer
  for (int i = 0; i < producers_num; i++) {
    printf("started producer: %d\n", i);
    xpthread_create(&producers[i], NULL, producer, (void *)shared_queue, line,
                    file);
  }
  // start consumer
  for (int i = 0; i < consumers_num; i++) {
    printf("started consumer: %d\n", i);
    xpthread_create(&consumers[i], NULL, consumer, (void *)shared_queue, line,
                    file);
  }

  /* JOIN */
  for (int i = 0; i < producers_num; i++) {
    xpthread_join(producers[i], NULL, line, file);
  }

  for (int i = 0; i < consumers_num; i++) {
    xpthread_join(consumers[i], NULL, line, file);
  }

  destroy_queue_sync_var(shared_queue);
  free(shared_queue);

  return 0;
}
