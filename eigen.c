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

double calculateNotNormalizedVectorCellValue(double *currentRow, double *vector, int size) {
    double *currentCellInVector = vector;
    double *currentRowCell = currentRow;
    double *currentRowEnd = currentRow + size;
    int sum = 0;
    for (; currentRow != currentRowEnd; currentRow++, currentCellInVector++) {
        sum += *currentRow * (*currentCellInVector);
    }
    return sum;
}

double calcVectorDivisor(double* vector,int size)
{
    double * vectorEnd = vector + size;
    double sum=0;
    for(;vector!=vectorEnd;vector++)
        sum+=*vector;

    return sqrt(sum);
}
double normalizeVector(double *newVectorPointer, int vectorSize, const double *oldVectorPointer) {
    double largestDiff = 0;
    double vectorDivisor=1;
    double* currentNewVectorPointer=newVectorPointer;
    double* NewVectorEnd=newVectorPointer+vectorSize;
    vectorDivisor=calcVectorDivisor(newVectorPointer,vectorSize);


    for (; currentNewVectorPointer != NewVectorEnd; currentNewVectorPointer++) {
        *currentNewVectorPointer/=vectorDivisor;
        largestDiff = max(fabs(*currentNewVectorPointer - *oldVectorPointer), largestDiff);

    }
    return largestDiff;
}

double scanColumnAndWriteToNewVector(FILE *input, double *vector, double *newVectorPointer, int vectorSize,
                                     double *currentRow) {
    double largestDiff = 0;
    double *oldVectorEnd = vector + vectorSize;
    double *oldVectorPointer = vector;
    double vectorDivisor = 1;
    for (; oldVectorPointer != oldVectorEnd; oldVectorPointer++, newVectorPointer++) {
        double cellNewValue;
        readline(input, currentRow, vectorSize);
        cellNewValue = calculateNotNormalizedVectorCellValue(currentRow, vector, vectorSize);
        *newVectorPointer = cellNewValue;

    }
    largestDiff = normalizeVector(newVectorPointer, vectorSize, oldVectorPointer);

    return largestDiff;
}


double *iterateVector(FILE *input, double epsilon, double *vector, int vectorSize) {
    double *newVector = (double *) calloc(vectorSize, sizeof(double));
    double *currentRow = calloc(vectorSize,
                                sizeof(double));/* it's true that it should be inside scan, but it's better perf wise*/
    double largestDiff;

    do {
        largestDiff = scanColumnAndWriteToNewVector(input, vector, newVector, vectorSize, currentRow);
        swap(&newVector, &vector);
        rewind(input);
    } while (largestDiff > epsilon);
    swap(&newVector, &vector);
    free(currentRow);
    return newVector;
}

int main(int argc, char *argv[]) {
    FILE *input;
    int dimension[2] = {0, 0};
    int readStatus = 0;
    const double epsilon = 0.00001;
    double *b0;/* iteration vector*/
    double *bk;

    assert(argc == 2);
    srand(time(NULL));


    input = openInputFile(argv);
    getDimension(input, dimension);
    b0 = getVector(dimension[0]);
    bk = iterateVector(input, epsilon, b0, dimension[0]);
    /* @todo write the output file*/
    free(b0);
    free(bk);
    fclose(input);
}

