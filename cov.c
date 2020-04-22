 #include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "time.h"

double rowMean(const double *arr, int n) {

    double sum = 0;
    int i;
    for (i = 0; i < n; i++)
        sum = sum + arr[i];
    return sum / n;

}

void subtractMeanFromRow(double row1, int columnLength){

    double mean = rowMean(row1, columnLength);
    int i;
    for(i = 0; i < columnLength; i++) {
        row1[i] = row1[i] - mean;
    }
}



double fillCovDiffInCell(const double row1[], double row2[], int columnLength) {


    double sum = 0;
    double const* row1Cell=row1;
    double * row2Cell=row2;
    double const* rowEnd=row1+columnLength;
    for (; row1Cell!=rowEnd; row1Cell++,row2Cell++) {

        sum = sum + (*row1Cell) * (*row2Cell);
    }
    return sum;

}



int main(int argc, char *argv[]) {
    int matrixDimension[2];
    int numberOfParameters = 0;
    int rowLength = 0;
    int columnLength;
    double **matrix;
    double **outputMatrix;
    int i;
    int j;
    int matrixRow;
    FILE *outputFile;
    int outputMatrixDimension[2] = {0, 0};
    clock_t start,end;
    FILE *file;

    start=clock();
    file = fopen(argv[1], "r");
    assert(file != NULL);

    numberOfParameters = fread(matrixDimension, sizeof(int), 2, file);
    assert(numberOfParameters == 2);

    rowLength = matrixDimension[1];
    columnLength = matrixDimension[0];

    ///Input Matrix is standardized while being read
    matrix = (double **) malloc(rowLength * sizeof(double *));
    outputMatrix = (double **) malloc(rowLength * sizeof(double *));
    for (i = 0; i < rowLength; i++) {
        matrix[i] = (double *) malloc(columnLength * sizeof(double));
        outputMatrix[i] = (double *) malloc(columnLength * sizeof(double));

        matrixRow = fread(matrix[i], sizeof(double), columnLength, file); /* Filling Matrix[i]*/
        assert(matrixRow == columnLength);
        meanRowSubtraction(matrix[i], columnLength) ///Subtracts mean from each row of input matrix
    }

    fclose(file);

    ///Going over input matrix, calculating and writing covariance row by row
    outputFile = fopen(argv[2], "w");
    assert(outputFile != NULL);
    outputMatrixDimension[1] = rowLength;   /// output Matrix is square
    outputMatrixDimension[0] = rowLength;

    int rowsAndColumns = fwrite(outputMatrixDimension, sizeof(int), 2, outputFile);
    assert(rowsAndColumns == 2);

    /// Calculating covariance and writing done row by row
    for(i = 0; i < rowLength; i++) {
        for(j = 0; j < rowLength; j++){
            outputMatrix[i][j] = fillCovDiffInCell(matrix[i], matrix[j], columnLength)  ///Iteration by columns
        }

        int toFileByRow = 0;
        toFileByRow = fwrite(outputMatrix[i], sizeof(double), outputMatrixDimension[0], outputFile);
        assert(toFileByRow == outputMatrixDimension[0]);
    }

    fclose(outputFile);

    for (i = 0; i < rowLength; i++) {
        free(matrix[i]);
        free(outputMatrix[i]);
    }

    free(matrix);
    free(outputMatrix);

    (void) argc;/*we don't want any warnings*/
    end=clock();
    printf("%f",((double)(end-start) / CLOCKS_PER_SEC));
    return 0;
}
