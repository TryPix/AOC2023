#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h> 
#include "tokenization.h"


char wordToNumber(char* word){
    if (strstr(word, "zero")) return '0';
    if (strstr(word, "one") ) return '1';
    if (strstr(word, "two") ) return '2';
    if (strstr(word, "three") ) return '3';
    if (strstr(word, "four") ) return '4';
    if (strstr(word, "five") ) return '5';
    if (strstr(word, "six") ) return '6';
    if (strstr(word, "seven")) return '7';
    if (strstr(word, "eight")) return '8';
    if (strstr(word, "nine")) return '9';
    return -1;
}

char wordToNumberRev(char* word){
    if (strstr(word, "orez") != NULL) return '0';
    if (strstr(word, "eno") != NULL) return '1';
    if (strstr(word, "owt") != NULL) return '2';
    if (strstr(word, "eerht") != NULL) return '3';
    if (strstr(word, "ruof") != NULL) return '4';
    if (strstr(word, "evif") != NULL) return '5';
    if (strstr(word, "xis") != NULL) return '6';
    if (strstr(word, "neves")!= NULL) return '7';
    if (strstr(word, "thgie")!= NULL) return '8';
    if (strstr(word, "enin")!= NULL) return '9';
    return -1;
}

void part1(char **tokens, int n){
     int sum = 0;

    for (int i = 0; i < n; i++){
        char* str = tokens[i];
        int l = strlen(str);

        char num[32];

        int d1 = 0;
        int d2 = 0;

        for (int j = 0; j < l || (d1 == 0 && d2 == 0); j++){
            if (!d1 && isdigit(str[j])){
                num[0] = str[j];
                d1 = 1;
            }

            if (!d2 && isdigit(str[l-1-j])){
                num[1] = str[l-1-j];
                d2 = 1;
            }
        }

        int val;
     
        sum += atoi(num);
    }

    printf("Part 1: %d\n", sum);
}

void part2(char **tokens, int n){

    int sum = 0;
    for (int i = 0; i < n; i++){
        char* str = tokens[i];
        int l = strlen(str);

        char num[256];

        int d1 = 0;
        int d2 = 0;

        char prefix[256] = "";
        char suffix[256] = "";


        for (int j = 0; j < l || (d1 == 0 && d2 == 0); j++){
            prefix[j] = str[j];
            suffix[j] = str[l-1-j];

            if (!d1 && isdigit(str[j])){
                num[0] = str[j];
                d1 = 1;
            }

            if (!d1 && wordToNumber(prefix) != -1){
                num[0] = wordToNumber(prefix);
                d1 = 1;
            }

            if (!d2 && isdigit(str[l-1-j])){
                num[1] = str[l-1-j];
                d2 = 1;
            }

            if (!d2 && wordToNumberRev(suffix) != -1){
                num[1] = wordToNumberRev(suffix);
                d2 = 1;
            }
        }

        sum+= atoi(num);

    }

    printf("Part 2: %d\n", sum);

}

int main() {

    char **tokens = (char**) malloc((INPUT_SIZE+1) * sizeof(char*));
    int n;

    tokenize_input(&tokens, &n, "day1.txt", "\n ");

    part1(tokens, n);
    part2(tokens, n);

    free_tokens(tokens, n);

    return 0;
}
