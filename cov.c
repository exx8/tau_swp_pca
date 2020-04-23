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

void covarianceMatrix(double **inputMatrix, double **outputMatrix, int rowSpace, int columnSpace) {

    int p;
    int j;
    int i;


    double *rowMeansArray = (double *) malloc(rowSpace * sizeof(double));

    for (i = 0; i < (rowSpace); i++){
        rowMeansArray[i] = rowMean(inputMatrix[i], columnSpace);}

    for (p = 0; p < (rowSpace); p++){
        for (j = 0; j < (rowSpace); j++){

            outputMatrix[p][j] = fillCovDiffInCell(inputMatrix[p], inputMatrix[j], rowMeansArray[p],
                    rowMeansArray[j], columnSpace); } }

    free(rowMeansArray);
}


void outputMatrixToFile(double **outputMatrix, int *outputMatrixDimension, FILE *outputFile) {
    int l;
    int toFileByRow=0;
    int rowsAndColumns = fwrite(outputMatrixDimension, sizeof(int), 2, outputFile);
    assert(rowsAndColumns == 2);

    for (l = 0; l < (outputMatrixDimension[0]); l++){
        toFileByRow= fwrite(outputMatrix[l], sizeof(double), outputMatrixDimension[0], outputFile);
        assert(toFileByRow == outputMatrixDimension[0]); }
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

    /* Function Standardize Given Matrix. Uses Covariance function.*/
    covarianceMatrix(matrix, outputMatrix, rowLength, columnLength);

    /* Write outputMatrix to File*/
    outputFile = fopen(argv[2], "w");
    assert(outputFile != NULL);
    outputMatrixDimension[1]=rowLength;
    outputMatrixDimension[0]=columnLength;
    outputMatrixToFile(outputMatrix, outputMatrixDimension, outputFile);

    fclose(outputFile);

    for (i = 0; i < rowLength; i++){
        free(matrix[i]);
        free(outputMatrix[i]); }

    (void)argc ;/*we don't want any warnings*/
    return 0;
}
