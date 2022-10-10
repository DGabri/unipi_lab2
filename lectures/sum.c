#define _GNU_SOURCE //usiamo estensioni GNU
#include <stdio.h> //print, scan
#include <stdlib.h> //conversione tipi, exit()
#include <stdbool.h> //booleani
#include <assert.h> //permette di usare la funzione assert
#include <string.h> //confronto/copia stringa

//leggere un intero N da tastiera
// creare un array di N int
//legge N interi mettendoli nell'array
//calcola la somma degli elementi dell'array
//stampa la somma

int main(int argc, char* argv[]) {
    
    int n;
    //devo controllare il codice di ritorno e se non va bene mi fermo
    //scanf("%d", &n);
    printf("Inserire il numero di elementi: ");
    int error = scanf("%d", &n);

    if (error != 1) {
        puts("Valore non trovato");
        exit(1);
    }

    //crea vettore lungo n elementi
    int a[n];

    //leggera da tastiera n numeri

    for (int i = 0; i < n; i++){
        printf("Inserire elemento di indice %d:", i);
        int code = scanf("%d", &a[i]);
        if (code != 1) {
            puts("Valore non trovato");
            exit(1);
        }
    }

    //calcolo della somma
    int sum = 0;
    
    for (int j = 0; j < n; j++){
        sum += a[j];
    }
    printf("SUM: %d \n", sum);

    return 0;
}