#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

//read int N from terminal
//create array of N elements
//read N int's inserting them in the array
//calc the sum of the array elements
//print final sum

int main(int argc, char* argv[]) { 
    int *a;
    int n;
    printf("Insert number of elements:");
    int error = scanf("%d", &n);

    if (error != 1) {
        puts("Invalid value!");
        exit(1);
    }

    a = malloc(n*sizeof(int));

    if (a == NULL) {
        puts("can't allocate array!");
        exit(1);
    }

    //read N numbers from terminal

    for (int i = 0; i < n; i++){
        printf("Insert number of index i = %d:", i);
        int code = scanf("%d", &a[i]);
        if (code != 1) {
            puts("Invalid value!");
            exit(1);
        }
    }

    //calc sum
    int sum = 0;
    
    for (int j = 0; j < n; j++){
        sum += a[j];
    }
    printf("SUM: %d \n", sum);

    free(a);
}
 