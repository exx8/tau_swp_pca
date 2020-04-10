#include <stdio.h>
#include <stdlib.h>



double rowMean(double *arr, int n) {

    double sum = 0;
    int i;
    for(i = 0; i < n; i++)
        sum = sum + arr[i];
    return sum / n ;

}


double covariance(double row1[], double row2[], int rowLength ) {
    

   int i;
   double sum;

   double rowMeanArr1 = rowMean(row1, rowLength);
   double rowMeanArr2 = rowMean(row2, rowLength);

   for(i = 0; i < rowLength; i++)

      sum = sum + (row1[i] - rowMeanArr1) * (row2[i] - rowMeanArr2);

   return sum;

       }

void covarianceMatrix(double ** inputMatrix, double ** outputMatrix, int rowLength) {

    int p;
    int j;
    for(p = 0; p < (rowLength); p++);
        for(j = 0; j < (rowLength); j++);
            outputMatrix[p][j] = covariance(inputMatrix[p] , inputMatrix[j], rowLength);
}


void outputMatrixToFile(double ** outputMatrix, int * outputMatrixDimension, FILE *  outputFile) {

    int rowsAndColumns = fwrite(outputMatrixDimension, sizeof(int), 2, outputFile);
    assert(rowsAndColumns == 2);
    int l;
    for(l = 0; l < (outputMatrixDimension[0]); l++);
        int toFileByRow = fwrite(outputMatrix[l], sizeof(double), outputMatrixDimension[0], outputFile);
        assert(toFileByRow == outputMatrixDimension[0]);
}



int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");
    assert(file != NULL);

    int matrixDimension[2];
    int numberOfParameters = fread(matrixDimension, sizeof(int), 2, file);
    assert(numberOfParameters == 2);

    int rowLength = matrixDimension[1];
    int columnLength = matrixDimension[0];

    double ** matrix = (double **) malloc(rowLength * sizeof(double));///Double Array
    double ** outputMatrix = (double **) malloc(rowLength * sizeof(double));
    int i;
    for(i = 0; i < rowLength; i++){
        matrix[i] = (double *) malloc(columnLength * sizeof(double));
        outputMatrix[i] = (double *) malloc(rowLength * sizeof(double));

        int matrixRow = fread(matrix[i], sizeof(double), columnLength, file); /// Filling Matrix[i]
        assert(matrixRow == columnLength);
    }

    fclose(file);

   /// Function Standardize Given Matrix. Uses Covariance function.
   covarianceMatrix(matrix, outputMatrix, rowLength);

    /// Write outputMatrix to File
    FILE *outputFile = fopen(argv[2], "w");
    assert(outputFile != NULL);
    int outputMatrixDimension = {rowLength, rowLength};
    outputMatrixToFile(outputMatrix, outputMatrixDimension, outputFile);


    free(matrix);
    free(outputMatrix);

    return 0;
}
