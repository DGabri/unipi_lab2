#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int len;
  int head;
  int tail;
  int inserted;
  int *data;
} Buffer;

Buffer *crete_buffer(int size) {
  Buffer *circular_buffer = malloc(sizeof(Buffer));

  if (circular_buffer == NULL) {
    printf("Error creating buffer\n");
    exit(1);
  }

  circular_buffer->len = size;
  circular_buffer->inserted = 0;
  circular_buffer->head = 0;
  circular_buffer->tail = 0;

  circular_buffer->data = calloc(size, sizeof(int));

  if (circular_buffer->data == NULL) {
    printf("Error allocating buffer\n");
    exit(1);
  }

  return circular_buffer;
}

int insert(Buffer *buff, int elem) {
  // buffer full
  if (buff->inserted == buff->len) {
    return 0;
  }
  // insert elem and update tail
  int tail = buff->tail;
  buff->data[tail] = elem;
  buff->tail = (tail + 1) % (buff->len);

  return 1;
}

int remove_elem(Buffer *buff) {
  // buffer empty
  if (buff->inserted == 0) {
    return 0;
  }

  int head = buff->head;
  int elem = buff->data[head];
  buff->head = (head + 1) % (buff->len);
  buff->inserted--;

  return elem;
}