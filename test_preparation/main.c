#define _GNU_SOURCE
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// stampa un messaggio d'errore su stderr e termina il programma
void termina(char *messaggio) {
  // se errno!=0 oltre al mio messaggio stampa il messaggio
  // associato alla variabile globale errno
  // utilizzando la funzione di libreria perror()
  if (errno != 0) {
    perror(messaggio);
  }
  // altrimenti stampa solo il mio messaggio
  else {
    fprintf(stderr, "%s\n", messaggio);
  }
  exit(1);
}

int *elabora(int a[], int n, int k, int *nuovon) {
  int size = 0;

  if (k == 0) {
    size = n;
  } else if (k > 0) {
    size = (k * n);
  } else {

    size = ((k * (-1)) * n);
  }

  int *result = malloc(sizeof(int) * size);
  *nuovon = size;

  if (result == NULL) {
    termina("IMPOSSIBILE ALLOCARE ARRAY");
  }

  if (k == 0) {
    for (int i = 0; i < size; i++) {
      result[i] = 0;
    }
  } else if (k > 0) {

    for (int i = 0; i < n; i++) {

      for (int j = 0; j < k; j++) {
        result[i + j] = a[i];
      }
    }
  } else {
    int idx = size - 1;

    // printf("K: %d\n", k);
    k *= (-1);
    // printf("K: %d\n", k);
    for (int i = 0; i < n; i++) {

      for (int j = 0; j < k; j++) {
        result[idx--] = a[i];
      }
    }
  }
  return result;
}

int main(int argc, char *argv[]) {

  // argv[1] = nome file
  // argv[2] = interoK
  // argv[3] = nomeK

  if (argc % 2 == 1) {
    termina("Numero di parametri sbagliato");
  }
  int size = 40;
  int inserted = 0;
  int *test_array = malloc(sizeof(int) * size);

  if (test_array == NULL) {
    termina("IMPOSSIBILE ALLOCARE ARRAY");
  }

  /////////////////////////////////////////////////
  // aprire file di input uguale per tutti
  FILE *input = fopen(argv[1], "r");

  if (input == NULL) {
    termina("File di input inesistente");
  }

  // popolare array
  while (true) {
    int n;
    int e = fscanf(input, "%d", &n);

    if (e == EOF)
      break;
    if (e != 1) {
      termina("Contenuto illegale nel file");
    }

    if (inserted >= size) {
      // fprintf(stderr, "OLD SIZE: %d\n", size);
      size *= 2;
      test_array = realloc(test_array, sizeof(int) * size);

      if (test_array == NULL) {
        fprintf(stderr, "REALLOC FAILED\n");
        exit(1);
      }
    }

    test_array[inserted] = n;
    inserted++;
  }

  size = inserted;
  test_array = realloc(test_array, sizeof(int) * size);

  // chiusura file di input
  if (fclose(input) == EOF) {
    termina("Errore chiusura file");
  }
  //////////////////////////////////////////

  for (int i = 2; i < argc; i += 2) {
    FILE *output = fopen(argv[i], "w");

    if (output == NULL) {
      termina("Errore file di output");
    }

    int new_len = 0;
    int *result_array = elabora(test_array, size, atoi(argv[i - 1]), &new_len);

    // scrivere array generato con elabora dentro il file
    //

    for (int i = 0; i < new_len; i++) {
      int element = result_array[i];
      printf("%d\n", element);
      int e = fprintf(output, "%d\n", element);

      if (e == EOF)
        break;
      if (e != 1) {
        termina("Contenuto illegale nel file");
      }
    }

    // chiudere file di output momentaneo
    if (fclose(output) == EOF) {
      termina("Errore chiusura file");
    }
  }

  return -1;
}