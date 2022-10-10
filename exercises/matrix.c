#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void check_error() {
    puts("error");
    exit(1);
}

void create_matrix() {
    //get matrix size
    //1. insert number of rows
    //2. insert number of columns
    //3. insert number of int elements
    int cols;
    int rows;
    int elements;
    int **matrix;

    puts("Insert number of rows");
    int col_getter = scanf("%d\n", &rows);
    if (col_getter != 1) {
        check_error();
    }
    puts("Insert number of columns");
    
    int row_getter = scanf("%d\n", &rows);
    if (row_getter != 1) {
        check_error();
    }

    matrix = malloc(sizeof(int)*rows);

    if (matrix == NULL) {
        check_error();
    }

    for (int i=0; i<cols; i++) {
        matrix[i] = malloc(sizeof(int)*cols);

        if (matrix[i] == NULL) {
            check_error();
        }
    }

    puts("Enter elements of 1st matrix");
    
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j) {
            printf("Enter a%d%d: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
    }
}

int main(int argc, char *argv[]) {

    
    return -1;
}