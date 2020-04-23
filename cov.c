#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

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

        sum = sum + (row1[i] - rowMeanArr1) * (row2[i] - rowMeanArr2);
    }

    return sum;

}

void covarianceMatrix(double **inputMatrix, int rowSpace, int columnSpace, FILE *outputFile) {

    int p;
    int j;
    int i;
    int writeNum=0;

    double *rowMeansArray = (double *) malloc(rowSpace * sizeof(double));
    double *row = calloc(rowSpace, sizeof(double));
    for (i = 0; i < (rowSpace); i++) {
        rowMeansArray[i] = rowMean(inputMatrix[i], columnSpace);
    }

    for (p = 0; p < (rowSpace); p++) {

        for (j = 0; j < (rowSpace); j++) {

            row[j] = fillCovDiffInCell(inputMatrix[p], inputMatrix[j], rowMeansArray[p],
                                       rowMeansArray[j], columnSpace);

        }
        writeNum=fwrite(row, sizeof(double), rowSpace, outputFile);
        assert(writeNum==rowSpace);
    }
    free(row);
    free(rowMeansArray);
}


int main2(int argc, char *argv[]) {
    int matrixDimension[2];
    int numberOfParameters = 0;
    int rowLength = 0;
    int columnLength;
    double **matrix;
    int i;
    int matrixRow;
    FILE *outputFile;
    int writeStatus=0;
    int outputMatrixDimension[2] = {0, 0};
    time_t start = clock();
    FILE *file = fopen(argv[1], "r");
    assert(file != NULL);

    numberOfParameters = fread(matrixDimension, sizeof(int), 2, file);
    assert(numberOfParameters == 2);

    rowLength = matrixDimension[1];
    columnLength = matrixDimension[0];

    matrix = (double **) malloc(rowLength * sizeof(double *));
    for (i = 0; i < rowLength; i++) {
        matrix[i] = (double *) malloc(columnLength * sizeof(double));

        matrixRow = fread(matrix[i], sizeof(double), columnLength, file); /* Filling Matrix[i]*/
        assert(matrixRow == columnLength);
    }

    fclose(file);

    /* Write outputMatrix to File*/
    outputFile = fopen(argv[2], "w");
    assert(outputFile != NULL);
    outputMatrixDimension[1] = rowLength;
    outputMatrixDimension[0] = rowLength;
    writeStatus=fwrite(outputMatrixDimension,sizeof(int),1,outputFile);
    assert(writeStatus==1);

    writeStatus=fwrite(outputMatrixDimension,sizeof(int),1,outputFile);

    assert(writeStatus==1);
    /* Function Standardize Given Matrix. Uses Covariance function.*/
    covarianceMatrix(matrix, rowLength, columnLength, outputFile);



    fclose(outputFile);

    for (i = 0; i < rowLength; i++) {
        free(matrix[i]);
    }

    (void) argc;/*we don't want any warnings*/
    free(matrix);
    printf("%f", ((double) (clock() - start) / CLOCKS_PER_SEC));

    return 0;
}
