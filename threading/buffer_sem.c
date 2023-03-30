#include "xerrori.h"
#include <stdlib.h>

#define line __LINE__
#define file __FILE__

typedef struct {
  int *buffer;
  int buff_size;
  int tail;
  int head;
  int inserted_element;
  int producers_num;
  int finished_producers;
  int produced_items;
  int consumed_items;

  // syncronization variables
  sem_t empty;
  sem_t full;
  pthread_mutex_t lock;

} Buffer;

void init_buffer(Buffer *buffer, int buffer_size, int producers_count) {
  buffer->tail = 0;
  buffer->head = 0;
  buffer->buff_size = buffer_size;
  buffer->inserted_element = 0;
  buffer->finished_producers = 0;
  buffer->producers_num = producers_count;
  buffer->produced_items = 0;
  buffer->consumed_items = 0;

  xsem_init(&buffer->empty, 0, buffer_size, line, file);
  xsem_init(&buffer->full, 0, 0, line, file);
  xpthread_mutex_init(&buffer->lock, NULL, line, file);

  buffer->buffer = calloc(buffer_size, sizeof(int));

  if (buffer->buffer == NULL) {
    puts("Calloc error creating buffer...");
    return;
  }
}

void destroy_buffer(Buffer *buffer) {

  xsem_destroy(&buffer->empty, line, file);
  xsem_destroy(&buffer->full, line, file);
  xpthread_mutex_destroy(&buffer->lock, line, file);
  free(buffer->buffer);
}

void insert_element(Buffer *buffer, int item) {
  // wait for an empty slot in the buffer
  xsem_wait(&buffer->empty, line, file);
  xpthread_mutex_lock(&buffer->lock, line, file);

  int insert_index = buffer->tail;
  buffer->buffer[insert_index] = item;
  buffer->tail = (insert_index + 1) % (buffer->buff_size);
  printf("Producer [%lu] inserted: %d [%d/%d]\n", (unsigned long)pthread_self(),
         item, buffer->inserted_element, buffer->buff_size);

  buffer->produced_items++;
  xpthread_mutex_unlock(&buffer->lock, line, file);
  // signal that there is a new item in the buffer
  xsem_post(&buffer->full, line, file);
}

int remove_element(Buffer *buffer) {

  // wait for a full slot in the buffer
  xsem_wait(&buffer->full, line, file);
  xpthread_mutex_lock(&buffer->lock, line, file);

  int elem = buffer->buffer[buffer->head];
  buffer->head = (buffer->head + 1) % (buffer->buff_size);
    printf("Consumer [%lu] read: %d\n", (unsigned long)pthread_self(), elem);
  xpthread_mutex_unlock(&buffer->lock, line, file);
  // signal that there is an empty slot in the buffer
  xsem_post(&buffer->empty, line, file);
  return elem;
}

void *producer(void *arg) {
  Buffer *buffer = (Buffer *)arg;

  int inserted = 0;

  while (inserted < 20) {
    int elem = rand() % 100; // produce a random item
    insert_element(buffer, elem);
    inserted++;
  }

  // update the number of producers that have finished
  xpthread_mutex_lock(&buffer->lock, line, file);
  buffer->finished_producers++;
  xpthread_mutex_unlock(&buffer->lock, line, file);

  return NULL;
}

void *consumer(void *arg) {
  Buffer *buffer = (Buffer *)arg;

  while (1) {

    // termination condition
    xpthread_mutex_lock(&buffer->lock, line, file);
    if ((buffer-> produced_items == buffer->consumed_items) &&
        (buffer->finished_producers == buffer->producers_num)) {
        
            break;
    }
    xpthread_mutex_unlock(&buffer->lock, line, file);

    int elem = remove_element(buffer);
    printf("Consumer [%lu] read: %d\n", (unsigned long)pthread_self(), elem);
  }

  return NULL;
}

int main(int argc, char *argv[]) {

  if (argc != 3) {
    puts("Insert: 1- consumer thread num 2- producer thread num");
    exit(1);
  }

  Buffer *bounded_buffer = malloc(sizeof(Buffer));
  int consumers_num = atoi(argv[1]);
  int producers_num = atoi(argv[2]);

  if (bounded_buffer == NULL) {
    puts("Error creating buffer, exiting...");
    free(bounded_buffer);
    exit(1);
  }

  // intialize buffer struct
  init_buffer(bounded_buffer, 15, producers_num);
  pthread_t producers[producers_num];
  pthread_t consumers[consumers_num];

  // start producer
  for (int i = 0; i < producers_num; i++) {
    printf("started producer: %d\n", i);
    xpthread_create(&producers[i], NULL, producer, (void *)bounded_buffer, line,
                    file);
  }
  // start consumer
  for (int i = 0; i < consumers_num; i++) {
    printf("started consumer: %d\n", i);
    xpthread_create(&consumers[i], NULL, consumer, (void *)bounded_buffer, line,
                    file);
  }

  /* JOIN */
  for (int i = 0; i < producers_num; i++) {
    xpthread_join(producers[i], NULL, line, file);
  }

  for (int i = 0; i < consumers_num; i++) {
    xpthread_join(consumers[i], NULL, line, file);
  }

  destroy_buffer(bounded_buffer);
  free(bounded_buffer);

  return 0;
}
