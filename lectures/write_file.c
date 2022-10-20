#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }
    char *fname;
    int file_number;

    for (int i = 0; i < file_number; i++) {
      char *s = NULL;
      int e = asprintf(&s, "%s.%d", fname, i);
      if (e < 0)
        exit(1);
      // FILE * =
    }

    return -1;
}