#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h> // For isdigit and isxdigit
#include <math.h>
#include "caosculator.h"

char* bitToString(long bits, int word_size) {
    char* bitString = calloc(sizeof(char),word_size + 1);
    if (bitString == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    for (int i = word_size-1; i >= 0; --i) {
        if(bits % 10 == 1){
            bitString[i] = '1';
        } else {
            bitString[i] = '0';
        }
        bits /= 10;
    }
    return bitString;
}

void hello() {
    printf("Hello and welcome to the bit calculator!\n");
    printf("Developed and serviced by - Thomas Andersen \n\n");

    printf("This calculator can perform the following bit operations:\n");
    printf("(+) Addition\n");
    printf("(-) Subtraction\n");
    printf("(*) Multiplication\n");
    printf("(/) Division\n");
    printf("(%%) Modulus\n");
    printf("(&) Bitwise AND\n");
    printf("(|) Bitwise OR\n");
    printf("(^) Bitwise XOR\n");
    printf("(<) Bitwise Left Shift\n");
    printf("(a) Arithmetic Right Shift\n");
    printf("(l) Logical Right Shift\n");
    printf("\n");
    printf("\n");

}

long bits_to_hex(long bits, long word_size) {
    long hex = 0;
    int i = 0;
    for (i = 0; i < word_size / 4; ++i) {
        hex += (bits % 10) * pow(2, i);
        bits /= 10;
    }
    return hex;
}

long hex_to_decimal(char *hex) {
    long decimal = strtol(hex, NULL, 16);
    return decimal;
}

long bits_to_decimal(long bits, int word_size, bool is_signed) {
    long decimal = 0;
    int terminator = is_signed ? 1 : 0;
    int i = 0;
    for (i = 0; i < word_size - terminator; ++i) {
        decimal += (bits % 10) * pow(2, i);
        bits /= 10;
    }

    if (is_signed) {
        decimal -= (bits % 10) * pow(2, i);
    }
    return decimal;
}

unsigned long decimalToBits(unsigned long decimal, int word_size) {
    unsigned long bits = 0;
    int i = 0;
    for (i = 0; i < word_size; ++i) {
        bits += (decimal % 2) * pow(10, i);
        decimal /= 2;
    }

    return bits;
}


long scanInputAsBit(long word_size) {
    char type;
    char input1[100];

    long InputBit1;
    bool try_again = true;

    while (try_again ) {
        printf("(H)exadecimal, (D)ecimal, (B)it: ");
        scanf(" %c", &type);



        if ( type == 'H' || type == 'h' ) {
            printf("Give hex input: ");
            scanf("%s", input1);
            InputBit1 = decimalToBits( hex_to_decimal( input1 ), word_size );
            try_again = false;
        } else if ( type == 'D' || type == 'd' ) {
            printf("Give decimal input: ");
            scanf("%s", input1);
            InputBit1 = decimalToBits( strtol( input1, NULL, 10 ), word_size );
            try_again = false;
        } else if ( type == 'B' || type == 'b' ) {
            printf("Give bit input: ");
            scanf("%s", input1);
            InputBit1 = decimalToBits( strtol( input1, NULL, 2 ), word_size );
            try_again = false;
        }else{
            printf("Invalid input, try again!");
        }
    }
    printf("\n");
    char* bitString = bitToString(InputBit1, word_size);

    unsigned UVal = bits_to_decimal(InputBit1, word_size, false);
    printf("SD: %ld, UD: %ld, Hx: %lx.      Bit input: %s \n", bits_to_decimal(InputBit1, word_size, true),
           UVal, UVal, bitString);
    free(bitString);
    return InputBit1;
}

void calculate(char *operator, long TDecVal1, unsigned long UDecVal1, int word_size) {
    printf("\n");
    unsigned long unsignedRes = 0;
    long signedRes = 0;
    unsigned long UDecVal2;
    long TDecVal2;
    switch (*operator) {
        case '+':
            UDecVal2 = bits_to_decimal(scanInputAsBit(word_size), word_size, false);
            unsignedRes = UDecVal1 + UDecVal2;
            break;
        case '-':
            UDecVal2 = bits_to_decimal(scanInputAsBit(word_size), word_size, false);
            unsignedRes = UDecVal1 - UDecVal2;
            break;
        case '*':
            UDecVal2 = bits_to_decimal(scanInputAsBit(word_size), word_size, false);
            unsignedRes = UDecVal1 * UDecVal2;
            break;
        case '/':
            UDecVal2 = bits_to_decimal(scanInputAsBit(word_size), word_size, false);
            unsignedRes = UDecVal1 / UDecVal2;
            break;
        case '%':
            UDecVal2 = bits_to_decimal(scanInputAsBit(word_size), word_size, false);
            unsignedRes = UDecVal1 % UDecVal2;
            break;
        case '&':
            UDecVal2 = bits_to_decimal(scanInputAsBit(word_size), word_size, false);
            unsignedRes = UDecVal1 & UDecVal2;
            break;
        case '|':
            UDecVal2 = bits_to_decimal(scanInputAsBit(word_size), word_size, false);
            unsignedRes = UDecVal1 | UDecVal2;
            break;
        case '^':
            UDecVal2 = bits_to_decimal(scanInputAsBit(word_size), word_size, false);
            unsignedRes = UDecVal1 ^ UDecVal2;
            break;
        case '<':
            UDecVal2 = bits_to_decimal(scanInputAsBit(word_size), word_size, false);
            unsignedRes = UDecVal1 << UDecVal2;
            break;
        case 'l':
            UDecVal2 = bits_to_decimal(scanInputAsBit(word_size), word_size, false);
            unsignedRes = (unsigned long)((long)UDecVal1 >> UDecVal2);
            break;
        case 'a':
            UDecVal2 = bits_to_decimal(scanInputAsBit(word_size), word_size, false);
            unsignedRes = TDecVal1 >> TDecVal2;
            break;
        default:
            unsignedRes = UDecVal1;
            signedRes = TDecVal1;
            break;
    }

    unsignedRes = bits_to_decimal(decimalToBits(unsignedRes, word_size), word_size, false);
    signedRes = bits_to_decimal(decimalToBits(unsignedRes, word_size), word_size, true);

    printf("\n");
    printf("Signed Decimal Result: %ld\n", signedRes);
    printf("Unsigned Decimal Result: %ld\n", unsignedRes);
    printf("Hexadecimal Result: %lX\n", unsignedRes);
    char* bitString = bitToString( decimalToBits(unsignedRes, word_size), word_size);
    printf("Binary Result: %s\n", bitString);
    free(bitString);
    printf("\n");
}

void runCalculator(int word_size) {
    char operator;

    printf("Operator or (n): ");
    scanf(" %c", &operator);

    long InputBit1 = scanInputAsBit(word_size);

    unsigned long UDecVal1 = bits_to_decimal(InputBit1, word_size, false);
    long TDecVal1 = bits_to_decimal(InputBit1, word_size, true);

    calculate(&operator, TDecVal1, UDecVal1, word_size);
}

int main() {
    int word_size = 0;
    while (true) {
        hello();
        printf("Give word size w: ");
        scanf("%d", &word_size);
        runCalculator(word_size);
        printf("Continue? (y/n): ");
        char cont;
        scanf(" %c", &cont);
        if (cont == 'n') {
            break;
        }
        printf("\n");
        printf("\n");
    }
}
