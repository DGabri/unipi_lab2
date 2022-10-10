#define _GNU_SOURCE 
#include <assert.h> 
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prints error message
void termina(char *messaggio) {
  if (errno != 0) {
    perror(messaggio);
  } else {
    fprintf(stderr, "%s\n", messaggio);
  }
  exit(1);
}

void print_array(int arr[], int len) {
  printf("[");

  for (int i = 0; i < len; i++) {
    if (i > 0)
      printf(",");
    printf("%d", arr[i]);
  }

  printf("]\n");
}

int search_val(int a[], int len, int val) {
  int found = 0;
  int i = 0;

  while (i < len) {
    if (a[i] == val) {
      found = 1;
      break;
    }
    i++;
  }
  return found;
}

int *create_array(int len, char *elems[]) {
  int *arr;
  int size = len - 1;

  arr = malloc(sizeof(int) * size);

  if (arr == NULL) {
    termina("insufficient space");
  }

  for (int i = 1; i < len; i++) {
    arr[i - 1] = atoi(elems[i]);
  }

  return arr;
}

int *somme_distinte(int a[], int n, int *size) {
    int inserted = 0;
    int dim = *size;
    int *arr;
    //int *result;

    arr = malloc(sizeof(int)*dim);
    
    if (arr == NULL) {
        termina("insufficient space");
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            int value = a[i] + a[j];
            //printf("VAL: %d", value);
            int is_duplicate = search_val(arr, dim, value);

            if (!is_duplicate) {
                //printf("DUPLICATE: %d", value);
                if (inserted > dim) {
                    dim *= 2;
                    arr = realloc(arr, dim);

                    if (arr == NULL) {
                         termina("insufficient space");
                    }
                }

                arr[inserted] = value;
                inserted++;
            }            
        }
    }
    *size = inserted;
    //print_array(arr, inserted);
    return arr;
}

int sum_array_val(int a[], int len) {
  int sum = 0;

  for (int i = 0; i < len; i++) {
      sum += a[i];
  }
  return sum;
}


int main(int argc, char *argv[]) {
    int *array = create_array(argc, argv);
    int sizeLen = 30;
    int *new_arr;
    new_arr = somme_distinte(array, argc-1, &sizeLen);
    printf("%d", sum_array_val(new_arr, sizeLen));
    free(array);
    free(new_arr);
    //print_array(new_arr, sizeLen);
    return 0;
}
