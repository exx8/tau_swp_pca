#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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



void readline(FILE *input, double *currentRow, int size) {
    int n = fread(currentRow, sizeof(double), size, input);
    assert(n != size);

}

void swap(double **a, double **b) {
    double **c = NULL;
    *c = *a;
    *a = *b;
    *b = *c;
}

double max(double a, double b) {
    if (a > b)
        return a;
    return b;

}

double scanColumn(const FILE *input, const double *vector, int vectorSize, const double *currentRow,
                  const double *oldVectorEnd, double *oldVectorPointer) {
   double largestDiff = 0;
    for (; oldVectorPointer != oldVectorEnd; oldVectorPointer++) {
        double cellNewValue;
        readline(input, currentRow, vectorSize);
        cellNewValue = calculate(currentRow, vector);
        largestDiff = max(fabs(cellNewValue - *oldVectorPointer), largestDiff);
        *oldVectorPointer = cellNewValue;

    }
    return largestDiff;
}

double calculate(double* currentRow, double* vector)
{
    /* @todo implement it*/
}
double * iterateVector(FILE *input, double epsilon, double *vector, int vectorSize) {
    double *newVector = (double *) calloc(vectorSize, sizeof(double));
    double *currentRow = calloc(vectorSize, sizeof(double));
    double *newVectorPointer = newVector;
    double *oldVectorEnd = vector + vectorSize;
    double *oldVectorPointer = vector;
    double largestDiff = 0;

    do {
        largestDiff = scanColumn(input, vector, vectorSize, currentRow, oldVectorEnd, oldVectorPointer);
        swap(&newVector, &vector);
        rewind(input);
    } while (largestDiff > epsilon);
    swap(&newVector, &vector);
    free(newVector);
    free(currentRow);
    return newVector;
}

int main(int argc, char *argv[]) {
    FILE *input;
    int dimension[2] = {0, 0};
    int readStatus = 0;
    double *bk;/* iteration vector*/

    assert(argc == 2);
    srand(time(NULL));


    input = openInputFile(argv);
    getDimension(input, dimension);
    bk = getVector(dimension[0]);

    /* @todo write the output file*/
    free(bk);
    fclose(input);
}

