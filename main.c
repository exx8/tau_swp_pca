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

int main(int argc, char *argv[], double sum) {

    FILE *file = fopen(argv[1], "r");
    assert(file != NULL);

    int matrixDimension[2];
    int numberOfParameters = fread(matrixDimension, sizeof(int), 2, file);
    assert(numberOfParameters == 2);

    int rowLength = matrixDimension[0];    /// @todo find out which one is column/row.
    int columnLength = matrixDimension[1];

    double ** matrix = (double *) malloc(rowLength * sizeof(double));  ///Double Array
    int i;
    for(i = 0; i < rowLength; i++){
        matrix[i] = (double *) malloc(columnLength * sizeof(double));
    }

    fclose(file);

   /// Function Standardize Given Matrix. Uses Mean Function.
    int i;
    for(i = 0; i < (rowLength); i++)
        double sum = 0;
        sum = rowMean(matrix[(rowLength) * i], columnLength);
        int j;
        for(j = 0; j < (rowLength); j++)
            matrix[(rowLength) * (i) + j] - sum;

    /// Function Standardize Given Matrix. Uses Mean Function.
    matrix2
    int i;
    for(i = 0; i < (*rowLength); i++)
        double sum = 0;
    sum = rowMean(matrix[(*rowLength) * i], *columnLength);
    int j;
    for(j = 0; j < (*rowLength); j++)
        matrix[(*rowLength) * (i) + j] - sum;



    return 0;
}
