#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE *openInputFile(char *const *argv) {
    FILE *input = fopen(argv[1], "r");
    assert(input != NULL);
    return input;
}

void getDimension(FILE *input, int *dimension) {
    int readStatus;
    readStatus = fread(dimension, sizeof(int), 2, input);
    assert(readStatus == 2);
}

double *getVector(int size) {
    double *vector = (double *) calloc(size, sizeof(double));
    const double *end = vector + size;
    double *current = vector;
    for (; current != end; current++)
        *current = rand();
    return vector;
}

int main(int argc, char *argv[]) {
    FILE *input;
    int dimension[2] = {0, 0};
    int readStatus = 0;
    double *b0; /* iteration vector*/

    assert(argc == 2);
    srand(time(NULL));


    input = openInputFile(argv);
    getDimension(input, dimension);
    b0 = getVector(dimension[0]);
    free(b0);
    fclose(input);
}

