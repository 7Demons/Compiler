#include "lex2.h"

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

Keyword getKeyword(span_t *fSpan) {
    size_t windowSize = fSpan->right - fSpan->left;
    char *charWindow = malloc(sizeof(char)*windowSize);
    memcpy(charWindow, fSpan->left, windowSize);

    Keyword result = 0;
    // this is silly and wasteful.
    result += (memcmp(charWindow, &"auto", sizeof(char)*4) == 0) ? _auto : 0;
    result += (memcmp(charWindow, &"break", sizeof(char)*5) == 0) ? _break : 0;
    result += (memcmp(charWindow, &"case", sizeof(char)*4) == 0) ? _case : 0;
    result += (memcmp(charWindow, &"char", sizeof(char)*4) == 0) ? _char : 0;
    result += (memcmp(charWindow, &"const", sizeof(char)*5) == 0) ? _const : 0;
    result += (memcmp(charWindow, &"continue", sizeof(char)*8) == 0) ? _continue : 0;
    result += (memcmp(charWindow, &"default", sizeof(char)*7) == 0) ? _default : 0;
    result += (memcmp(charWindow, &"do", sizeof(char)*2) == 0) ? _do : 0;
    result += (memcmp(charWindow, &"double", sizeof(char)*6) == 0) ? _double : 0;
    result += (memcmp(charWindow, &"else", sizeof(char)*4) == 0) ? _else : 0;
    result += (memcmp(charWindow, &"enum", sizeof(char)*4) == 0) ? _enum : 0;
    result += (memcmp(charWindow, &"extern", sizeof(char)*6) == 0) ? _extern : 0;
    result += (memcmp(charWindow, &"float", sizeof(char)*5) == 0) ? _float : 0;
    result += (memcmp(charWindow, &"for", sizeof(char)*3) == 0) ? _for : 0;
    result += (memcmp(charWindow, &"goto", sizeof(char)*4) == 0) ? _goto : 0;
    result += (memcmp(charWindow, &"if", sizeof(char)*2) == 0) ? _if : 0;
    result += (memcmp(charWindow, &"int", sizeof(char)*3) == 0) ? _int : 0;
    result += (memcmp(charWindow, &"long", sizeof(char)*4) == 0) ? _long : 0;
    result += (memcmp(charWindow, &"register", sizeof(char)*8) == 0) ? _register : 0;
    result += (memcmp(charWindow, &"return", sizeof(char)*6) == 0) ? _return : 0;
    result += (memcmp(charWindow, &"short", sizeof(char)*5) == 0) ? _short : 0;
    result += (memcmp(charWindow, &"signed", sizeof(char)*6) == 0) ? _signed : 0;
    result += (memcmp(charWindow, &"sizeof", sizeof(char)*6) == 0) ? _sizeof : 0;
    result += (memcmp(charWindow, &"static", sizeof(char)*6) == 0) ? _static : 0;
    result += (memcmp(charWindow, &"struct", sizeof(char)*6) == 0) ? _struct : 0;
    result += (memcmp(charWindow, &"switch", sizeof(char)*6) == 0) ? _switch : 0;
    result += (memcmp(charWindow, &"typedef", sizeof(char)*7) == 0) ? _typedef : 0;
    result += (memcmp(charWindow, &"union", sizeof(char)*5) == 0) ? _union : 0;
    result += (memcmp(charWindow, &"unsigned", sizeof(char)*8) == 0) ? _unsigned : 0;
    result += (memcmp(charWindow, &"void", sizeof(char)*4) == 0) ? _void : 0;
    result += (memcmp(charWindow, &"volatile", sizeof(char)*8) == 0) ? _volatile : 0;
    result += (memcmp(charWindow, &"while", sizeof(char)*5) == 0) ? _while : 0;

    return result;
}

// might want to move span to a different file.
span_t *spanInit(unsigned char *data, unsigned int length) {
    span_t *span = (span_t *)malloc(sizeof(span_t));
    if (span == NULL) {
        return NULL;
    }

    span->bp = data;
    span->left = data;
    span->right = data;
    span->end = data + length;
    return span;
}

BOOL span_popU8(span_t* span, unsigned char* U8) {
    if (U8 == NULL || span->right >= span->end) {
        return FALSE;
    }

    *U8 = *span->right++;
    return TRUE;
}

BOOL span_peekU8(span_t* span, unsigned char* U8) {
    if (U8 == NULL || span->right >= span->end) {
        return FALSE;
    }
    unsigned char *temp = span->right;
    *U8 = *temp;
    return TRUE;
}

BOOL span_advanceU8(span_t* span) {
    if (span->right >= span->end) {
        return FALSE;
    }
    span->right++;
    return TRUE;
}

void charScanner(span_t *fSpan) {
    char peekChar;
    fSpan->left = fSpan->right;
    while(span_peekU8(fSpan, &peekChar)) {

        if (isSeperator(peekChar) || isOperator(peekChar) ||  isspace(peekChar)) {

            Keyword kw = getKeyword(fSpan);
            if (kw != 0) {
                printf("Keyword %d\n", kw);
                return;
            }

            // else identifier
            char *charSpanDEBUG = malloc(sizeof(char)*1024);
            // THIS IS FOR DEBUGGING. REMOVE SOON.
            int windowSize = (fSpan->right - fSpan->left)/ sizeof(char);
            memcpy(charSpanDEBUG, fSpan->left, windowSize); // unsafe
            charSpanDEBUG[windowSize] = '\0';
            printf("Identifier: _%s_\n", charSpanDEBUG);
            free(charSpanDEBUG);
            return;
        }
        if (!span_advanceU8(fSpan)) {
            return;
        }
    }
}

void numScanner() {
    return;
}

void lexScanner(rdBuf *file) {
    // our view window of the character stream.
    span_t *fSpan = spanInit(file->fileContents, file->size);
    if (fSpan == NULL) {
        exit(0);
    }

    // lexical tokens
    DynamicArray *tokenStream = (DynamicArray *)createDynamicArray(sizeof(lexToken));
    if (!tokenStream) {
        exit(0);
    }

    char peekChar = ' ';
    char popChar = ' ';
    
    // we will peek the next character to decide the state of the machine during the loop.
    // and will when eaching the end of the loop.
    while(span_peekU8(fSpan, &peekChar)) {
        
        // We will have a keyword or identifier. Transfer control to the charScanner.
        if (isalpha(peekChar)) {
            charScanner(fSpan);
            fSpan->left = fSpan->right; 
        }
        // we will have a NUMERIC literal.
        else if (isdigit(peekChar)) {
            span_popU8(fSpan, &popChar);
            printf("digit UNIMPLEMENTED %c\n", popChar);
            fSpan->left = fSpan->right;
        }
        else if (isspace(peekChar)) {
            span_popU8(fSpan, &popChar);
            fSpan->left = fSpan->right;
        }
        // note if it is a "" we want to treat it differently.
        else if (isSeperator(peekChar)) {
            span_popU8(fSpan, &popChar);
            printf("Seperator %c\n", popChar);
            fSpan->left = fSpan->right;
        }
        // note some operators are special eg ==
        else if (isOperator(peekChar)) {
            span_popU8(fSpan, &popChar);
            printf("Operator %c\n", popChar);
            fSpan->left = fSpan->right;
        }
    }
    printf("finished!");
}

int main() {
    rdBuf *file = readFile("test.txt");

    lexScanner(file);
    return 0;
}