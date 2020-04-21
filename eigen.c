#include <assert.h>
#include <stdio.h>

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

int main(int argc, char *argv[]) {
    FILE *input;
    int dimension[2] = {0, 0};
    int readStatus = 0;
    assert(argc == 2);

    input = openInputFile(argv);

    getDimension(input, dimension);
    fclose(input);
}

