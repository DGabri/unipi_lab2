#define _GNU_SOURCE // avverte che usiamo le estensioni GNU
#include <assert.h> // permette di usare la funzione assert
#include <errno.h>
#include <stdbool.h> // gestisce tipo bool (variabili booleane)
#include <stdio.h>   // permette di usare scanf printf etc ...
#include <stdlib.h>  // conversioni stringa/numero exit() etc ...
#include <string.h>  // confronto/copia/etc di stringhe

// stampa un messaggio d'errore e termina il programma
void termina(const char *messaggio);

int sum_missing_vals(const char *fname) {
  // read file
  // create array of 1000 ints
  // increase the occurrences
  // iterate the array, if arr[i] == 0, sum += arr[i]

  int sum_value = 0;
  bool result_arr[1000] = {0};
  int value = 0;
  FILE *f = fopen(fname, "rt");

  if (f == NULL) {
    termina("File non leggibile");
  }

  while (fscanf(f, "%d", &value) == 1) {
    if ((value > 0) && (value <= 1000)) {
      // printf("VALUE: %d\n", value);
      result_arr[value - 1] = true;
    }
  }

  for (int i = 0; i < 1000; i++) {
    if (result_arr[i] == false) {
      sum_value += i + 1;
    }
  }
  if (fclose(f) == EOF) {
    termina("Errore chiusura file");
    ;
  }

  return sum_value;
}

// scheletro del main della soluzione
int main(int argc, char *argv[]) {

  if (argc != 2) {
    fprintf(stderr, "Uso:\n\t   %s nome_file\n", argv[0]);
    exit(1);
  }

  int somma = 0;
  somma = sum_missing_vals(argv[1]);
  fprintf(stderr, "Visualizzo il risultato (%d) su stdout:\n", somma);
  printf("%d\n", somma);

  return 0;
}

void termina(const char *messaggio) {
  if (errno != 0) {
    perror(messaggio);
  } else {
    fprintf(stderr, "%s\n", messaggio);
    exit(1);
  }
}