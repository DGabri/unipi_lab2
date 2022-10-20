#define _GNU_SOURCE // avverte che usiamo le estensioni GNU
#include <assert.h> // permette di usare la funzione assert
#include <errno.h>
#include <stdbool.h> // gestisce tipo bool (variabili booleane)
#include <stdio.h>   // permette di usare scanf printf etc ...
#include <stdlib.h>  // conversioni stringa/numero exit() etc ...
#include <string.h>  // confronto/copia/etc di stringhe

// stampa un messaggio d'errore e termina il programma
void termina(const char *messaggio);

// scrivere questa funzione
bool stringhe_uguali_puntatore(char s[], char q[]) {

  char *s_char = s;
  char *q_char = q;
  bool equal = true;

  while (*s_char != '\0') {
    if ((*q_char != '\0')) {

      if (*s_char != *q_char) {
        equal = false;
        break;
      }
      s_char++;
      q_char++;
    } else {
      equal = false;
      break;
    }
  }

  if ((*s_char == '\0') && (*q_char != '\0')) {
    equal = false;
  }

  return equal;
}

bool stringhe_uguali(char s[], char q[]) {

  int s_index = 0;
  int q_index = 0;
  bool equal = true;

  while (s[s_index] != '\0') {
    if ((q[q_index] != '\0')) {

      if (s[s_index] != q[q_index]) {
        equal = false;
        break;
      }
      s_index++;
      q_index++;
    } else {
      equal = false;
      break;
    }
  }

  if ((s[s_index] == '\0') && (q[q_index] != '\0')) {
    equal = false;
  }

  return equal;
}

// scrivere questa funzione
bool stringhe_uguali2(char s[], char q[]) {
  int i;

  for (i = 0; s[i] != '\0'; i++) {
    if (s[i] != q[i])
      return (false);
  }

  if (q[i] != '\0')
    return (false);

  return (true);
}

bool stringhe_uguali_punt2(char s[], char q[]) {
  for (; *s != '\0';) {
    if (*s != *q)
      return (false);

    s++;
    q++;
  }

  if (*q != '\0')
    return (false);

  return (true);
}
// non modificate il main!
int main(int argc, char *argv[]) {

  if (argc != 3) {
    fprintf(stderr, "Uso: %s stringa1 stringa2\n", argv[0]);
    exit(1);
  }

  if (stringhe_uguali_punt2(argv[1], argv[2]))
    puts("Uguali!");
  else
    puts("Diverse!");

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
