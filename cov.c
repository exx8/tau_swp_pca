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


double fillCovDiffInCell(const double row1[], double row2[], double rowMeanArr1, double rowMeanArr2, int rowLength) {


    double sum = 0;
    double const* row1Cell=row1;
    double * row2Cell=row2;
    double const* rowEnd=row1+rowLength;
    for (; row1Cell!=rowEnd; row1Cell++,row2Cell++) {

        sum = sum + (*row1Cell - rowMeanArr1) * (*row2Cell - rowMeanArr2);
    }
    return sum;

}

void covarianceMatrix(double **inputMatrix, double **outputMatrix, int rowLength) {

    int p;
    int j;
    int i;

    double *rowMeansArray = (double *) malloc(rowLength * sizeof(double));

    for (i = 0; i < (rowLength); i++) {
        rowMeansArray[i] = rowMean(inputMatrix[i], rowLength);
    }
    for (p = 0; p < (rowLength); p++) {
        for (j = 0; j < (rowLength); j++) {
            outputMatrix[p][j] = fillCovDiffInCell(inputMatrix[p], inputMatrix[j], rowMeansArray[i],
                                                   rowMeansArray[j], rowLength);
        }
    }
    free(rowMeansArray);
}


void outputMatrixToFile(double **outputMatrix, int outputMatrixDimension[], FILE *outputFile) {
    double* outputMatrixCell=outputMatrix[0];
    double* outputMatrixEnd=outputMatrix[0]+(outputMatrixDimension[0]);
    int toFileByRow = 0;
    int rowsAndColumns = fwrite(outputMatrixDimension, sizeof(int), 2, outputFile);
    assert(rowsAndColumns == 2);


    for (; outputMatrixCell!=outputMatrixEnd; outputMatrixCell++) {
        toFileByRow = fwrite(outputMatrixCell, sizeof(double), outputMatrixDimension[0], outputFile);
    }
    assert(toFileByRow == outputMatrixDimension[0]);
}


int main(int argc, char *argv[]) {
    int matrixDimension[2];
    int numberOfParameters = 0;
    int rowLength = 0;
    int columnLength;
    double **matrix;
    double **outputMatrix;
    int i;
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

    matrix = (double **) malloc(rowLength * sizeof(double *));
    outputMatrix = (double **) malloc(rowLength * sizeof(double *));
    for (i = 0; i < rowLength; i++) {
        matrix[i] = (double *) malloc(columnLength * sizeof(double));
        outputMatrix[i] = (double *) malloc(rowLength * sizeof(double));

        matrixRow = fread(matrix[i], sizeof(double), columnLength, file); /* Filling Matrix[i]*/
        assert(matrixRow == columnLength);
    }

    fclose(file);

    /* Function Standardize Given Matrix. Uses Covariance function.*/
    covarianceMatrix(matrix, outputMatrix, rowLength);

    /* Write outputMatrix to File*/
    outputFile = fopen(argv[2], "w");
    assert(outputFile != NULL);
    outputMatrixDimension[0] = rowLength;
    outputMatrixDimension[1] = columnLength;
    outputMatrixToFile(outputMatrix, outputMatrixDimension, outputFile);

    fclose(outputFile);


    free(matrix);
    free(outputMatrix);

    (void) argc;/*we don't want any warnings*/
    end=clock();
    printf("%f",((double)(end-start) / CLOCKS_PER_SEC));
    return 0;
}