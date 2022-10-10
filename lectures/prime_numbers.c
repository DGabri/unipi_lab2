#define _GNU_SOURCE //usiamo estensioni GNU
#include <stdio.h> //print, scan
#include <stdlib.h> //conversione tipi, exit()
#include <stdbool.h> //booleani
#include <assert.h> //permette di usare la funzione assert
#include <string.h> //confronto/copia stringa


bool is_prime(int k);

bool is_prime(int k) {
    for (int i=2; i<k; i++) {
        if (k%i == 0) return false;
    }
    return true;
}

void termina(char *message) {
    puts(message);
    exit(1);
}

//scopo programma
// leggere un numero da tastiera
//creare array dinamico e inserire i primi n numeri dat
//riallocare

int main (int argc, char *argv[]) {
    int n;
    printf("Insert a number:");

    int error = scanf("%d", &n);
    if (error != 1) {
        termina("Value not found");
    }
    
    if (n<2) {
        termina("There are non prime numbers");
    }

    int *a; //a is used as an array
    int size = 10; //actual array size
    int messi = 0; //number of inserted elements

    //initialize dynamic array of size = size
    a = malloc(size * sizeof(int));

    //check if a == NULL => error, always check return codes
    if (a == NULL) {
        termina("Can't allocate array!");
    }

    //fill arrray 
    for (int i=2; i<=n; i++) {
        if (is_prime(i)) {
            //insert i inside the table of primes
            //check if there is space
            if (messi == size) {
                size *= 2;
                a = realloc(a, size*sizeof(int));
                if (a==NULL) {
                    termina("Realloc failed!");
                }
                // insert the first i inside the table a
            }
            a[messi] = i;
            messi++;
        }
    }
    
    //reduce array to minimum size neede so that the least amount of memory possible is used
    a = realloc(a, messi*sizeof(int));

    if (a==NULL) {
        termina("Realloc failed!");
    }

    for (int i=0; i<messi; i++) {
        printf("%8d", a[i]);
    }
    
    free(a);
    return 0;
}




