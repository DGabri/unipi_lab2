#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

void termina(char *messaggio) {
    if(errno!=0) {
        perror(messaggio);
    }
    else {
        fprintf(stderr,"%s\n", messaggio);
    }

  exit(1);
}

void print_array(int arr[], int len) {
  printf("[");

  for (int i = 0; i < len-1; i++) { 
    if(i>0) printf(",");
    printf("%d", arr[i]);
  }

  printf("]\n");
}

int compare( const void* a, const void* b) {
    int int_a = * ( (int*) a );
    int int_b = * ( (int*) b );

    if ( int_a == int_b ) return 0;
    else if ( int_a < int_b ) return -1;
    else return 1;
}

int *create_array(int len, char *elems[]) {
    int *arr;
    int size = len-1;

    arr = malloc(sizeof(int)*size);
    
    if (arr == NULL) {
        termina("insufficient space");
    }

    for (int i = 1; i < len; i++) {
        arr[i-1] = atoi(elems[i]);
    }
    
    return arr;
}

int find_max(int a[], int len) {
    int max = -1000000;
    
    for(int i = 0; i < len; i++) {
        if (a[i] > max) {
            max = a[i];
            //printf("MAX: %d\n", max);
        }
    }

    return max;
}

int max_val(int a[], int len) {
    int size = len;
    int inserted = 0;
    int num_seen = 0;
    int *res = malloc(sizeof(int)*(size));

    if (res == NULL) {
        termina("spazio insufficiente");
    }

    //sort array to search for duplicates
    qsort(a, len, sizeof(int), compare);
    //print_array(a, len);
    //search fro duplicates
    for(int i = 0; i < size-1; i++) {
        if (a[i] == a[i+1]) {

          if(num_seen == 0) {
            //printf("a[%d]: %d\n",i, a[i]);
            
            if (inserted <= size) {
                res[inserted] = a[i];
                inserted++;
            } else {
                size *= 2;
                res = realloc(res, size);
                if (res == NULL) {
                    termina("insufficient space");
                }
                else {
                    res[inserted] = a[i];
                    inserted++;
                }
            }

              num_seen++;
        } else {
            
        }
          } else  num_seen = 0;
    }
    //print_array(res, inserted+1);
    return find_max(res, inserted);
}

int main(int argc, char *argv[]) {
    //int test[5] = {8,7,6,5,4};

    //int *array = create_array(argc, argv);
    //print_array(array, argc);
    int *array = create_array(argc, argv);
    printf("%d\n",max_val(array, argc));
    free(array);
    return -1;
}
