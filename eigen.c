#include <assert.h>
#include <stdio.h>

FILE *openInputFile(char *const *argv) {
    FILE *input = fopen(argv[1], "r");
    assert(input != NULL);
    return input;
}

int main(int argc, char *argv[]) {
    FILE *input;
    assert(argc == 2);

    input = openInputFile(argv);


}

