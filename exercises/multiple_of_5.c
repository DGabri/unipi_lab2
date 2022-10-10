#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

void print_array(int arr[], int len) {
  printf("[");
  for (int i = 0; i < len; i++) { // nota manca incremento
    printf("%d", arr[i]);
  }
  printf("]\n");
}


int cancella5x(int *a, int n) {
    assert(a != NULL);
    assert(n >= 0);
    int index = 0;
    int right = 0;

    while (index < n) {
        if (a[index] % 5 != 0) {
          a[right] = a[index];
          right++;
        } 
      index++;
    }
    //print_array(a, n);
    return right;
}

int main(int argc, char *argv[]) {
    int test[5] = {5, 3, 1, 10, 5};
    cancella5x(test, 5);
}