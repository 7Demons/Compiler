#include <stdlib.h>
#include <stdio.h>

// we want to open a file and make this "window" so we can scan through
// looking for lexemes moving the window after each lexeme.

// maybe call this the lex buffer.
typedef struct rdBuf {
    char *fileContents;
    int size;
} rdBuf;

/** Read whole files into memory
*/
rdBuf *readFile(const char* fileName) {
    // get file handle
    FILE *pFile;
    pFile= fopen(fileName, "r");
    if (!pFile) {
        printf("No file! \n");
        exit(1);
    }

    // get file size for malloc
    fseek(pFile, 0L, SEEK_END);
    int fileSize = ftell(pFile);
    fseek(pFile, 0L, SEEK_SET);
    if (fileSize < 0) {
        exit(1);
    }
    rdBuf *buf = (rdBuf *)malloc(sizeof(rdBuf));
    if (!buf) {
        exit(0);
    }
    buf->size = fileSize;

    buf->fileContents = (char *)malloc(fileSize);
    if (!buf->fileContents) {
        printf("Malloc failed when reading file!\n");
        exit(1);
    }
    
    fread(buf->fileContents, sizeof(char), fileSize, pFile);
    fclose(pFile);

    return buf;
}
/*
int main() {

    fWindow fileWin = getFileContentsWindow("test.txt");

    printf("file size: %d\n", fileWin.size);
    printf("file start: %d\n", fileWin.start);
    printf("file end: %d\n", fileWin.end);
    printf("file contents: \n");
    printf("%s", fileWin.fileContents);
    printf("\n\n");

    return EXIT_SUCCESS;
}
*/