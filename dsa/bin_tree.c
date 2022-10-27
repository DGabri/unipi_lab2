#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node {
  int val;
  struct tree_node *sx;
  struct tree_node *dx;
} Node;

Node *new_node(int node_value) {
  Node *new_node = malloc(sizeof(Node));

  if (new_node == NULL) {
    perror("CAN'T ALLOCATE NODE");
    exit(1);
  }

  new_node->val = node_value;
  new_node->sx = NULL;
  new_node->dx = NULL;

  return new_node;
}

Node *insert_new_node(Node *root, int val) {
  if (root == NULL) {
    return new_node(val);
  }

  if (val < (root->val)) {
    root->sx = insert_new_node(root->sx, val);
  } else if (val > (root->val)) {
    root->dx = insert_new_node(root->dx, val);
  }
  return root;
}

void inorder_print(Node *root) {
  if (root != NULL) {
    inorder_print(root->sx);
    printf("%d ", root->val);
    inorder_print(root->dx);
  }
}

void preorder_print(Node *root) {
  if (root != NULL) {
    printf("%d ", root->val);
    inorder_print(root->sx);
    inorder_print(root->dx);
  }
}

void postorder_print(Node *root) {
  if (root != NULL) {
    inorder_print(root->sx);
    inorder_print(root->dx);
    printf("%d ", root->val);
  }
}

int main(int argc, char *argv[]) {

  Node *root = new_node(20);
  insert_new_node(root, 1);
  insert_new_node(root, 10);
  insert_new_node(root, 25);
  insert_new_node(root, 29);
  insert_new_node(root, 18);
  insert_new_node(root, 40);
  insert_new_node(root, 60);
  insert_new_node(root, 54);
  insert_new_node(root, 8);
  insert_new_node(root, 4);

  puts("IN ORDER PRINT");
  inorder_print(root);
  puts("\nPRE ORDER PRINT");
  preorder_print(root);
  puts("\nPOST ORDER PRINT");
  postorder_print(root);

  return -1;
}