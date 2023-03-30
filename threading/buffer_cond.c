#include "xerrori.h"
#include <pthread.h>
#include <time.h>

#define line __LINE__
#define file __FILE__

typedef struct {
  int buff_size;
  int inserted;
  int head;
  int tail;
  int *data;
  int finished_producers;
  int producers_num;

  pthread_mutex_t lock;
  pthread_cond_t not_full;
  pthread_cond_t not_empty;

} Buffer;

// initialize the buffer
int init_buffer(Buffer *buffer, int buffer_len, int producers_count) {
  buffer->buff_size = buffer_len;
  buffer->head = 0;
  buffer->tail = 0;
  buffer->inserted = 0;
  buffer->finished_producers = 0;
  buffer->producers_num = producers_count;

  // init threading vars
  xpthread_mutex_init(&buffer->lock, NULL, line, file);
  xpthread_cond_init(&buffer->not_full, NULL, line, file);
  xpthread_cond_init(&buffer->not_empty, NULL, line, file);

  buffer->data = calloc(buffer_len, sizeof(int));

  if (buffer->data == NULL) {
    puts("Malloc error creating buffer...");
    return -1;
  }

  return 1;
}

void destroy_buffer(Buffer *buffer) {
  // init threading vars
  xpthread_mutex_destroy(&buffer->lock, line, file);
  pthread_cond_destroy(&buffer->not_full);
  pthread_cond_destroy(&buffer->not_empty);
  free(buffer->data);
}

// insert element into buffer
void insert_element(Buffer *buffer, int elem) {

  // acquire lock
  xpthread_mutex_lock(&buffer->lock, line, file);

  // wait until there is space to insert a new element
  while ((buffer->inserted) == (buffer->buff_size)) {
    xpthread_cond_wait(&buffer->not_full, &buffer->lock, line, file);
  }

  // i can place a new item inside the buffer
  int insert_index = buffer->tail;
  buffer->data[insert_index] = elem;
  buffer->tail = (insert_index + 1) % (buffer->buff_size);
  buffer->inserted++;

  // logging
  printf("Producer [%lu] inserted: %d [%d/%d]\n", (unsigned long)pthread_self(),
         elem, buffer->inserted, buffer->buff_size);

  xpthread_cond_signal(&buffer->not_empty, line, file);
  xpthread_mutex_unlock(&buffer->lock, line, file);
}

// remove element from buffer
int remove_element(Buffer *buffer) {

  // acquire lock
  xpthread_mutex_lock(&buffer->lock, line, file);

  // no element to remove, wait
  while ((buffer->inserted == 0) &&
         (buffer->finished_producers < buffer->producers_num)) {
    xpthread_cond_wait(&buffer->not_empty, &buffer->lock, line, file);
  }

  int elem = -1;
  // read element
  if (buffer->inserted > 0) {
    int head = buffer->head;
    elem = buffer->data[head];
    buffer->head = (head + 1) % (buffer->buff_size);
    buffer->inserted--;
    printf("Consumer [%lu] read: %d\n", (unsigned long)pthread_self(), elem);

    xpthread_cond_signal(&buffer->not_full, line, file);
  }

  if ((buffer->inserted == 0) &&
      (buffer->finished_producers == buffer->producers_num)) {
    
    xpthread_cond_broadcast(&buffer->not_empty, line, file);
  }

  xpthread_mutex_unlock(&buffer->lock, line, file);

  return elem;
}

/*=========================================================*/
// insert random numbers inside the buffer
void *producer(void *arg) {

  Buffer *shared_buff = (Buffer *)arg;
  srand(time(NULL));

  int inserted = 0;

  while (inserted < 20) {
    int number = rand() % 100;
    insert_element(shared_buff, number);
    inserted++;
  }

  // update the number of producers that have finished
  xpthread_mutex_lock(&shared_buff->lock, line, file);
  shared_buff->finished_producers++;
  xpthread_mutex_unlock(&shared_buff->lock, line, file);

  return NULL;
}

// remove element and print it
void *consumer(void *arg) {
  Buffer *shared_buff = (Buffer *)arg;

  while (true) {
    int read_number = remove_element(shared_buff);

    if (read_number == -1) {
      break;
    }

    printf("Consumer %lu consumed %d\n", pthread_self(), read_number);
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
