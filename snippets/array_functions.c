#include <stdio.h>

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