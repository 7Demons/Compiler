#ifndef LEX_H_
#define LEX_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "readFile.c"
#include "Util/DynamicArray.c"

typedef int boolean; 

// As defined in the microsoft visual studio C language reference 2022.
// https://learn.microsoft.com/en-us/cpp/c-language/lexical-grammar?view=msvc-170
// Some of the definitions have been codified into their respective structure here.
// others will be done during lexing.
//

/** 
 * ========== TOKEN ==========
 * Lexical Token Structure
 * one of: *see definition*
*/
struct lexToken_s;
    enum lexCKeyword_e; //int
    struct lexIdentifier_s;
    struct lexConstant_s;
    struct lexStringLiteral_s;
    enum lexPunctuator_s; //int

struct lexToken_s {
    enum lexCKeyword_e keyWord;

};

/**
 * Lexical preprocessing token.
 * This is unimplemented. The preprocessor will be rather
 * primitive as I do not like function macros.
 * TODO: implement the preprocessor.
*/
struct preprocessingToken;
    // unimplemented.


/**
 * ========== Keywords ==========
 * Lexical keywords defined in the C language grammar.
 * if set to empty = 0, then this is unused.
 * Also includes modern keywords which are not currently planned to be 
 * implemented.
 * TODO: implement logic for newer key words.
*/
typedef enum lexCKeyword_e {
    // sentinal
    empty_kw = 0, 
    
    // standard key words.
    auto_kw, break_kw, case_kw, char_kw, const_kw, continue_kw, default_kw,
    do_kw, double_kw, else_kw, enum_kw, extern_kw, float_kw, for_kw, goto_kw,
    if_kw, inline_kw, int_kw, long_kw, register_kw, restrict_kw, return_kw,
    short_kw, signed_kw, sizeof_kw, static_kw, struct_kw, switch_kw, typedef_kw,
    union_kw, unsigned_kw, void_kw, volatile_kw, while_kw,
    
    // microsoft specific key words.
    _Alignas_kw, _Alignof_kw, _Atomic_kw, _Bool_kw, _Complex_kw, _Generic_kw,
    _Imaginary_kw, _Noreturn_kw, _Static_assert_kw, _Thread_local_kw,
} lexKW_t;


/**
 * ========== Identifiers ==========
 * Lex identifier 
*/
struct lexIdentifier_s;
    struct lexIdentifierNonDigit_s;
    // identifier + identifier-nondigit $recursve def$
    // identifier + digit $recursive def$

//*Lex: token/identifier/identifier-nondigit/universal-character-name
struct lexUniversalCharacterName_s;

typedef struct lexIdentifier_s {
    char *identifier;

} lexIdentifier_t;
 
/**
 * Lex identifier-nondigit
 *      nondigit
 *      universal-character name
*/

/**
 * Lex nondigit: one of
 * [aA-zZ] | _
*/

/**
 * Lex digit: one of
 * [0-9]
*/
    
/**
 * Lex universal-character-name
 *      \u hex-quad
 *      \U hex-quad hex-quad
*/
struct lexHexQuad_s;

typedef struct lexUniversalCharacterName_s {
    struct lexHexQuad_s *quad;
    struct lexHexQuad_s *quad2;
} lexUniCharName;

/**
 * Lex hex-quad 
*/
// TODO: implement hexidecimal digits.
typedef struct lexHexQuad_s {
    void *a;
    // hexadecimal-digit ^ 4
} lexHexQuad;

/**
 *  ========== Constants ==========
 * Lex constant
 *      integer-constant
 *      floating-constant
 *      enumeration-constant
 *      character-constant
*/
typedef struct lexConstant_s {
    unsigned long long uintConst;
    signed long long intConst;
    double ufloatConst;
    char *characterConstant;
    
} lexConst_t;

/**
 * integer-constant:
 *      decimal-constant (integer-suffix)
 *      binary-constan-1 (integer-suffix)
 *      octal-constant (integer-suffix)
 *      hexadecimal-constant (integer-suffix)
 * 
 * decimal-constant:
 *      nonzero-digit
 *      decimal-constant digit $see above for digit def.
 * 
 * binary-constant-1:
 *      binary-prefix binary-digit
 *      binary-constant binary-digit $recursive definition$
 * 
 * binary-prefix: $one of$
 *      0b || 0B
 * 
 * binary-digit: $one of$
 *      0 | 1
 * 
 * octal-constant:
 *      0
 *      octal-constant octal-digit
 * 
 * hexadecimal-constant:
 *      hexadecimal-prefix hexidecimal-digit
 *      hexadecimal-constant hexadecimal-digit
 * 
 * hexadecimal-prefix: $one of$
 *      0x 0X
 * 
 * nonzero-digit: 
 *      [1-9]
 * 
 * octal-digit:
 *      [0-7]
 * 
 * hexadecimal-digit: &one of&
 *      [0-9]U[a-f]U[A-F]
 * 
 * integer-suffix:
 *      unsigned-suffix (long-suffix)
 *      unsigned-suffix (long-long-suffix)
 *      long-suffix (unsigned-suffix)
 *      long-long-suffix (unsigned-suffix)
 * 
 * unsigned-suffix: $one of$
 *      u U
 * 
 * long-suffix: one of
 *      l L
 * 
 * long-long-suffix: one of
 *      ll LL 
 *
 * 
*/
 
/**
 * floating-constant:
        decimal-floating-constant
        hexadecimal-floating-constant

decimal-floating-constant:
    fractional-constant (exponent-part) (floating-suffix)
    digit-sequence exponent-part (floating-suffix)

hexadecimal-floating-constant:
    hexadecimal-prefix hexadecimal-fractional-constant (binary-exponent-part) (floating-suffix)
    hexadecimal-prefix hexadecimal-digit-sequence binary-exponent-part (floating-suffix)

fractional-constant:
    (digit-sequence) . digit-sequence
    digit-sequence .

exponent-part:
    e (sign) digit-sequence
    E (sign) digit-sequence

sign: one of
    + -

digit-sequence:
    digit
    digit-sequence digit

hexadecimal-fractional-constant:
    (hexadecimal-digit-sequence) . hexadecimal-digit-sequence
    hexadecimal-digit-sequence .

binary-exponent-part:
    p (sign) digit-sequence
    P (sign) digit-sequence

hexadecimal-digit-sequence:
    hexadecimal-digit
    hexadecimal-digit-sequence hexadecimal-digit

floating-suffix: one of
    f l F L

enumeration-constant:
    identifier

character-constant:
    ' c-char-sequence '
    L' c-char-sequence '

c-char-sequence:
    c-char
    c-char-sequence c-char

c-char:
    Any member of the source character set except the single quotation mark ('), backslash (\), or new-line character
    
    escape-sequence

escape-sequence:
    simple-escape-sequence
    octal-escape-sequence
    hexadecimal-escape-sequence
    universal-character-name $see above defintion$

simple-escape-sequence: one of
    \a \b \f \n \r \t \v
    \' \" \\ \?

octal-escape-sequence:
    \ octal-digit
    \ octal-digit octal-digit
    \ octal-digit octal-digit octal-digit

hexadecimal-escape-sequence:
    \x hexadecimal-digit
    hexadecimal-escape-sequence hexadecimal-digit
    */

/**
 * ========== String literal ==========
 * string-literal:
    encoding-prefix " s-char-sequenceopt "

 encoding-prefix:
    u8
    u
    U
    L

s-char-sequence:
    s-char
    s-char-sequence s-char

s-char:
    any member of the source character set except the double-quotation mark ("), backslash (\), or new-line character
    escape-sequence
*/
typedef struct lexStringLiteral_s {
    char *stringLiteral;
} lexStrLiteral_t;

/**
 * ========== Punctuators ==========
*/
typedef enum lexPunctuator_s {
    empty_op = 0,
    _oSquare, _cSquare, _oParen, _cParen, _oCurly, _cCurcly, _dot, _arrow,
    _increment, _decrement, _bwAnd, _multiply, _plus, _minus, _tilda, /*TILDA?*/ _negation,
    _divide, _modulo, _bsLeft, _bsRight, _logicalLess, _logicalGreater,
    _logicalLessEqual, _logicalGreaterEqual, _logicalEqual, _logicalNotEqual, 
    _Raise, /*RAISE?*/ _bwOr, _logicalAnd, _logicalOr, _ternary, _colon,
    _semiColon, _ellipses /*really?*/, _assignment, _multiplyAssign, _divideAssign,
    _moduloAssign, _plusAssign, _minusAssign, _bsLeftAssign, _bsRightAssign, 
    _bwAndAssign, _tildaAssign, _bwOrAssign, _comma, _hashtag, _doubleHashTag,
    _whack1, _whack2, _whack3, _whack4, _whack5, _whack6 /*<: :> <% %> %: %:%:*/
} lexPunc_t;

int main() {
    printf("%d", empty_op);
    return 0;
}

#endif