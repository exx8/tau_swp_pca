#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


double rowMean(const double *arr, int n) {

    double sum = 0;
    int i;

    for (i = 0; i < n; i++)
        sum = sum + arr[i];
    return sum / n;

}


double fillCovDiffInCell(double row1[], double row2[], double rowMeanArr1, double rowMeanArr2, int columnSpace) {


    int i;
    double sum = 0;

    for (i = 0; i < columnSpace; i++) {

        sum = sum + (row1[i] - rowMeanArr1) * (row2[i] - rowMeanArr2); }

    return sum;

}

void covarianceMatrixByRow(double **inputMatrix, double *inputMatrixRow, double rowMean, double *rowMeansArray,
        double *outputMatrixRow, int rowLength, int columnLength) {

    int i;

    for (i = 0; i < (rowLength); i++){

        outputMatrixRow[i] = fillCovDiffInCell(inputMatrixRow, inputMatrix[i], rowMean,
                                                   rowMeansArray[i], columnLength); }
}

void outputMatrixToFile(double *outputMatrixRow, int *outputMatrixDimension, FILE *outputFile) {

    int toFileByRow=0;

    toFileByRow= fwrite(outputMatrixRow, sizeof(double), outputMatrixDimension[0], outputFile);
    assert(toFileByRow == outputMatrixDimension[0]);
}


int main(int argc, char *argv[]) {
    int matrixDimension[2];
    int numberOfParameters=0;
    int rowLength=0;
    int columnLength;
    double **matrix;
    double **outputMatrix;
    int i;
    int matrixRow;
    FILE *outputFile;
    int outputMatrixDimension[2] = {0, 0};
    int rowsAndColumns;

    double *rowMeansArray;
    double checker1;

    FILE *file = fopen(argv[1], "r");
    assert(file != NULL);

    numberOfParameters = fread(matrixDimension, sizeof(int), 2, file);
    assert(numberOfParameters == 2);

    rowLength= matrixDimension[1];
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



    /* Write outputMatrix to File*/
    outputFile = fopen(argv[2], "w");
    assert(outputFile != NULL);
    outputMatrixDimension[1]=rowLength;
    outputMatrixDimension[0]=rowLength;

    rowsAndColumns = fwrite(outputMatrixDimension, sizeof(int), 2, outputFile);
    assert(rowsAndColumns == 2);

    rowMeansArray = (double *) malloc(rowLength * sizeof(double));

    for (i = 0; i < (rowLength); i++){
        rowMeansArray[i] = rowMean(matrix[i], columnLength);}


    /* Calculates covariance, and writes it to output matrix then to output File, one by one. */
    for (i = 0; i < rowLength; i++){

        covarianceMatrixByRow(matrix, matrix[i], rowMeansArray[i], rowMeansArray, outputMatrix[i],
                rowLength, columnLength);

        outputMatrixToFile(outputMatrix[i], outputMatrixDimension, outputFile);

    }

    fclose(outputFile);

    for (i = 0; i < rowLength; i++){
        free(matrix[i]);
        free(outputMatrix[i]); }

    (void)argc ;/*we don't want any warnings*/
    return 0;
}
