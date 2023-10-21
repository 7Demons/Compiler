#include <stdio.h>
#include <stdlib.h>
#include "readFile.c"
#include "Util/DynamicArray.c"

#define BOOL int
#define FALSE 0
#define TRUE 1

// Boris says: use an enum.
typedef enum tokenName {
    Identifier = 1,
    Keyword = 2,
    Seperator = 4,
    Operator = 8,
    Literal = 16,
    Comment = 32
} tokenName;

typedef struct lexicalToken {
    tokenName name;
    char *value;

} lexicalToken;

/*
typedef struct fileContentsWindow {
    char *fileContents;
    int size;
    int start;
    int end;
} fWindow;
typedef struct DynamicArray {
    void *data;
    int elementSize;
    int size;
    int maxCapacity;
} DynamicArray;

*/

// need to know what state we are in ... probably use last added operator to know?
// so currently we are reading the buffer like a window:
    //          ----> |base --------> +offset|---------->
void lexScanner(rdBuf *file) {
    int base = 0;
    int offset = 1;
    printf("start\n");
    for (int i = base; i <= file->size; i++) {

        char *val = calloc(i, sizeof(char));
        void *windowStart = (char *)file->fileContents + (base*sizeof(char));

        memcpy(val, windowStart, sizeof(char)*offset);
        char lastVal = val[offset-1];

        printf("debug: %c\n", lastVal);
        printf("%s \n", val);
        
        if (isOperator(lastVal)) {
            printf("this: %c is an operator\n", lastVal);
            base+= offset;
            offset = 0;
        }

        if (isSeperator(lastVal)) {
            printf("this: %c is a seperator\n", lastVal);
            base+= offset;
            offset = 0;
        }

        offset++;
        
        // continue moving cursor
    }
}

BOOL isOperator(char value) {
    switch(value) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '=':
            return TRUE;
            break;
    }
    return FALSE;
}

BOOL isSeperator(char value) {
    switch(value) {
        case '(':
        case ')':
        case '\'':
        case '\"':
        case '{':
        case '}':
        case ';':
        case ',':
            return TRUE;
            break;
    }
    return FALSE;
}

typedef struct span_s {
    unsigned char* cur;
    unsigned char* end;

}   span_t;

span_t *spanInit(unsigned char *data, unsigned int length) {
    span_t *span = (span_t *)malloc(sizeof(span_t));
    if (span == NULL) {
        return NULL;
    }

    span->cur = data;
    span->end = data + length;
    return span;
}

BOOL span_popU8(span_t* span, unsigned char* U8) {
    if (U8 == NULL || span->cur >= span->end) {
        return FALSE;
    }

    *U8 = *span->cur++;
    return TRUE;
}

int main() {
    rdBuf *file = readFile("test.txt");

    unsigned char *fdata = file->fileContents;
    
    // span_t *span = spanInit(fdata, 7);
    // char *test = malloc(sizeof(char)*7);
    // for (int i = 0; i < 7; i++) {
    //     span_popU8(span, test);
    //     printf("data 5: %s\n", test);  
    // }
    

    lexScanner(file);
    return 0;


}