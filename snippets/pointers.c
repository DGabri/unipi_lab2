#define _GNU_SOURCE
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function to return an array

// call by reference to modify values
// double_elements(array, length) NOT double_elements(&array, length)
void print_array(int arr[], int arr_len) {
  printf("[");
  for (int i = 0; i < arr_len; i++) {
    if (i < arr_len - 1) {
      printf("%d,", arr[i]);
    } else {
      printf("%d", arr[i]);
    }
  }
  printf("]\n");
}

void copy_string(char string[]) {
  // A copy of source is created dynamically
  // and pointer to copy is returned.
  char *target = strdup(string);
  free(target);
}
// arguments int arr[] == int *arr
void double_elements(int arr[], int arr_len) {
  for (int i = 0; i < arr_len; i++) {
    arr[i] *= 2;
  }
}

void print_char(char word[]) {
  // create pointer to char
  // word is already a pointer
  char *word_ptr = word;

  while (*word_ptr != '\0') {
    printf("CHAR: %c", *word_ptr);
    word_ptr++; // update pointer counter
  }
}

// get string length
int str_length(char word[]) {
  int i = 0;

  while (word[i] != '\0') {
    i++;
  }

  return i;
}

int main(int argc, char *argv[]) {

  int v = 15;
  int *variable = &v;

  printf("VARIABLE ADDRESS: %p\n", &variable);
  printf("VARIABLE VALUE: %3d\n", *variable);

  // modify value
  variable += 20;
  printf("VARIABLE UPDATED VALUE: %d\n", *variable);

  return -1;
}