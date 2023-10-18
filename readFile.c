#include <stdlib.h>
#include <stdio.h>

int main() {

    FILE *fptr;
    fptr = fopen("test.txt", "r");
    if (fptr == NULL) {
        printf("No file! \n");
        return EXIT_FAILURE;
    }
    char testString[1000];
    fptr += sizeof(char);

    fread(testString, sizeof(char), 100, fptr);

    printf("%s", testString);

    fclose(fptr);

    return EXIT_SUCCESS;
}
