#define _GNU_SOURCE
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    
    int n;
    // check return cose
    // scanf("%d", &n);
    printf("Inserire il numero di elementi: ");
    int error = scanf("%d", &n);

    if (error != 1) {
        puts("Valore non trovato");
        exit(1);
    }

    // create an array of lenght N
    int a[n];

    // read n intS from cmd

    for (int i = 0; i < n; i++){
        printf("Inserire elemento di indice %d:", i);
        int code = scanf("%d", &a[i]);
        if (code != 1) {
            puts("Valore non trovato");
            exit(1);
        }
    }

    // calc sum
    int sum = 0;
    
    for (int j = 0; j < n; j++){
        sum += a[j];
    }
    printf("SUM: %d \n", sum);

    return 0;
}