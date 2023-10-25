#ifndef LEX_H_
#define LEX_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "readFile.c"
#include "Util/DynamicArray.c"

#define BOOL int
#define FALSE 0
#define TRUE 1

typedef enum tokenName {
    tknInit = 0,
    tknListen = 1,
    tknDigitListen = 2,
    tknSeperator = 32,
    tknKeyword = 64,
    tknIdentifier = 128,
    tknLiteral = 512,
    tknOperator = 256,
    tknComment = 1024
} tokenName;

typedef struct lexToken {
    tokenName name;
    char *value;

} lexToken;

typedef struct span_s {
    unsigned char* bp;
    unsigned char* left;
    unsigned char* right;
    unsigned char* end;

} span_t;

typedef enum Keyword {
    _auto             = 32, 
    _break            = 1,
    _case             = 2,
    _char             = 3,
    _const            = 4,
    _continue         = 5,
    _default          = 6,
    _do               = 7,
    _double           = 8,
    _else             = 9,
    _enum             = 10,
    _extern           = 11,
    _float            = 12,
    _for              = 13,
    _goto             = 14,
    _if               = 15,
    _int              = 16,
    _long             = 17,
    _register         = 18,
    _return           = 19,
    _short            = 20,
    _signed           = 21,
    _sizeof           = 22,
    _static           = 23,
    _struct           = 24,
    _switch           = 25,
    _typedef          = 26,
    _union            = 27,
    _unsigned         = 28,
    _void             = 29,
    _volatile         = 30,
    _while            = 31,
} Keyword;

void lexScanner__OLD(rdBuf *file);
void lexScanner(rdBuf *file);
BOOL isOperator(char value);
BOOL isSeperator(char value);
span_t *spanInit(unsigned char *data, unsigned int length);
BOOL span_popU8(span_t* span, unsigned char* U8);


#endif