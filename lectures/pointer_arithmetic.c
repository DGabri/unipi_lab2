#define _GNU_SOURCE
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// calculate sring length
int str_length(char s[]) {
  assert(s != NULL);
  int i = 0;
  while (s[i] != '\0') { //*(s+i) != '\0' or (*s != '\0', s++)
    i++;
  }

  return i;
}

int main(int argc, char *argv[]) {
  int a = 1, b = 2, c = 3;
  int *vector;

  vector = malloc(sizeof(int) * 10);

  if (vector == NULL) {
    exit(1);
  }

  for (int i = 0; i < 10; i++) {
    vector[i] = (10 * i);
  }

  printf("Addresses: a %p\n, b %p\n, c %p \n", &a, &b, &c);
  printf("Array address: vector %p\n, vector %p\n", &vector, vector);

  int *pb = &b;
  c = vector[0];
  a = *pb;

  // the following is the same
  c = *vector; // takes what is inside the vector, which points to the address
               // vector[0]
  a = pb[0];   // the same as *pb

  assert(&vector[0] == vector);
  //&vector[1]; // address of vector[1]
  // vector + 1; // address of vector[1]
  // calculate string length
}