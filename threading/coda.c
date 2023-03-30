#include <stdlib.h>
#include "queue.h"

static struct Node {
	void *key;
	struct Node *next;
};

struct Queue {
	int size;
	int max_size;
	struct Node *head;
	struct Node *tail;
};

struct Queue* newQueue(int capacity)
{
	struct Queue *queue;
	queue = malloc(sizeof(struct Queue));

	if (queue == NULL) {
		return queue;
	}

	queue->size = 0;
	queue->max_size = capacity;
	queue->head = NULL;
	queue->tail = NULL;

	return queue;
}

int enqueue(struct Queue *queue, void *key)
{
	if ((queue->size + 1) > queue->max_size) {
		return queue->size;
	}

	struct Node *node = malloc(sizeof(struct Node));

	if (node == NULL) {
		return queue->size;
	}

	node->key = key;
	node->next = NULL;

	if (queue->head == NULL) {
		queue->head = node;
		queue->tail = node;
		queue->size = 1;

		return queue->size;
	}


	queue->tail->next = node;
	queue->tail = node;
	queue->size += 1;

	return queue->size;
}

void* dequeue(struct Queue *queue)
{
	if (queue->size == 0) {
		return NULL;
	}

	void *key = NULL;
	struct Node *old_head = NULL;

	key = queue->head->key;
	old_head = queue->head;
	queue->head = queue->head->next;
	queue->size -= 1;

	free(old_head);

	return key;
}

void freeQueue(struct Queue *queue)
{
	if (queue == NULL) {
		return;
	}

	while (queue->head != NULL) {
		struct Node *tmp = queue->head;
		queue->head = queue->head->next;
		if (tmp->key != NULL) {
			free(tmp->key);
		}

		free(tmp);
	}

	if (queue->tail != NULL) {
		free(queue->tail);
	}

	free (queue);
}