#include <stdio.h>
#include <stdlib.h>

#define arr_size 10

typedef struct list_node {
  int val;
  struct list_node *next;
} List_node;

List_node *create_node(int node_value) {
  List_node *new_node = malloc(sizeof(List_node));

  if (new_node == NULL) {
    perror("CAN'T ALLOCATE STRUCT");
    exit(1);
  }

  new_node->val = node_value;
  new_node->next = NULL;

  return new_node;
}

List_node *add_node_head(int new_node_value, List_node *list) {
  List_node *node_to_add = create_node(new_node_value);

  node_to_add->next = list;
  return node_to_add;
}

List_node *create_list_head_insert(int len, int values[]) {
  List_node *head = create_node(values[0]);

  for (int i = 1; i < len; i++) {
    List_node *new_node = create_node(values[i]);
    new_node->next = head;
    head = new_node;
  }

  return (head);
}

void free_node(List_node *node) {
  free(node->next);
  free(node);
}

void free_list(List_node *list) {
  List_node *tmp = list;

  while (tmp != NULL) {
    List_node *prev = tmp;
    tmp = tmp->next;
    free_node(prev);
  }
}

void print_list(List_node *list) {
  List_node *tmp = list;

  while (tmp != NULL) {
    int value = tmp->val;
    tmp = tmp->next;
    if (tmp != NULL) {
      printf("%d -> ", value);
    } else {
      printf("%d\n", value);
    }
  }
}

int main(int argc, char *argv[]) {
  int val[arr_size] = {10, 25, 63, 54, 12, 58, 897, 102, 456, 56};

  List_node *list = create_list_head_insert(10, val);

  print_list(list);
  free_list(list);
  return -1;
}