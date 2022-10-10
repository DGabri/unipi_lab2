#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }

    char *fname = argv[1];
    FILE *f = fopen(fname, "wt");

    if (f == NULL) {
        return -1;
    }

    for (int i = 2; i <= n; i++) {
        if (isprime(i)) {
            int e = fprintf(f, "%d\n", i);
            if (e < 0) return -1
        }
    }
    if (fclose(f) == EOF) { //file close succesfully
        return -1;
    }
}