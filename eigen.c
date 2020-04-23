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
    assert(n == size);

}

void swap(double **a, double **b) {
    double *c = *a;
    *a = *b;
    *b = c;
}

double max(double a, double b) {
    if (a > b)
        return a;
    return b;

}

double dotProduct_(double *currentRow, double *vector, int size) {
    double *currentRowPointer = currentRow;
    double *currentCellInVector = vector;
    double *currentRowEnd = currentRow + size;
    double sum = 0;
    for (; currentRowPointer != currentRowEnd; currentRowPointer++, currentCellInVector++) {
        sum += *currentRowPointer * (*currentCellInVector);
    }
    return sum;
}

double calcVectorDivisor(double *vector, int size) {
    double *vectorEnd = vector + size;
    double *vectorPointer = vector;
    double sum = 0;
    for (; vectorPointer != vectorEnd; vectorPointer++) {
        sum += vectorPointer[0]*vectorPointer[0];
    }
    return sqrt(sum);
}

void normalizeVector(double *newVectorPointer, int vectorSize) {
    double vectorDivisor = 1;
    double *currentNewVectorPointer = newVectorPointer;
    double *NewVectorEnd = newVectorPointer + vectorSize;

    vectorDivisor = calcVectorDivisor(newVectorPointer, vectorSize);


    for (; currentNewVectorPointer != NewVectorEnd; currentNewVectorPointer++) {
        *currentNewVectorPointer /= vectorDivisor;

    }
}

double scanColumnAndWriteToNewVector(FILE *input, double *vector, double *newVector, int vectorSize,
                                     double *currentRow) {
    /*@todo problem with reading from file probably*/

    double largestDiff = 0;
    double *oldVectorEnd = vector + vectorSize;
    double *oldVectorPointer = vector;
    double *newVectorPointer = newVector;
    for (; oldVectorPointer != oldVectorEnd; oldVectorPointer++, newVectorPointer++) {
        double cellNewValue;
        readline(input, currentRow, vectorSize);

        cellNewValue = dotProduct_(currentRow, vector, vectorSize);
        *newVectorPointer = cellNewValue;

    }
    normalizeVector(newVector, vectorSize);

    for(oldVectorPointer=vector,newVectorPointer=newVector;oldVectorPointer != oldVectorEnd;oldVectorPointer++, newVectorPointer++)
    largestDiff = max(fabs(*oldVectorPointer - *newVectorPointer), largestDiff);


    return largestDiff;
}


void resetLine( FILE *input) {
    int readStatus;
    int dontcare[2];
    rewind(input);
    readStatus = fread(dontcare, sizeof(int), 2, input);
    assert(readStatus == 2);

}

double *iterateVector(FILE *input, double epsilon, double *vector, int vectorSize) {
    double *newVector = (double *) calloc(vectorSize, sizeof(double));
    double *currentRow = calloc(vectorSize,
                                sizeof(double));/* it's true that it should be inside scan, but it's better perf wise*/
    double largestDiff;

    do {

        largestDiff = scanColumnAndWriteToNewVector(input, vector, newVector, vectorSize, currentRow);

        swap(&newVector, &vector);
        resetLine(input);
    } while (largestDiff > epsilon);
    swap(&newVector, &vector);
    free(currentRow);
    free(vector);
    return newVector;
}

FILE *openOutputFile(char **argv) {
    FILE *outputFile = fopen(argv[2], "w");
    assert(outputFile != NULL);

    return outputFile;
}

void writeToFile(FILE *output, const int *dimension, const double *bk) {
    int numOfWrites = 0;
    int matrixSize = dimension[0] * dimension[1];
    numOfWrites = fwrite(dimension, sizeof(int), 2, output);
    assert(numOfWrites == 2);
    numOfWrites = fwrite(bk, sizeof(double), matrixSize, output);
    assert(numOfWrites == matrixSize);
}

int main(int argc, char *argv[]) {
    clock_t start;
    FILE *input, *output;
    int matrixDimension[2];
    const double epsilon = 0.00001;
    double *b0;/* iteration vector*/
    double *bk;
    int vectorDimension[2]={0,0};
    assert(argc == 3);
    srand(time(NULL));
    start=clock();

    input = openInputFile(argv);
    getDimension(input, matrixDimension);
    vectorDimension[1]=matrixDimension[0];
    vectorDimension[0]=1;
    b0 = getVector(matrixDimension[0]);
    bk = iterateVector(input, epsilon, b0, matrixDimension[0]);
    /* @todo write the output file*/
    output = openOutputFile(argv);
    writeToFile(output, vectorDimension, bk);

    free(bk);
    fclose(input);
    fclose(output);
    printf("%f ",((double)(clock()-start) / CLOCKS_PER_SEC));

    return 0;
}
