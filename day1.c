#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h> 
#include "tokenization.h"
#include "utilities.h"


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

void part1(char **tokens, int n){
     int sum = 0;

    for (int i = 0; i < n; i++){
        char* str = tokens[i];
        int l = strlen(str);

        char num[3];

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

        sum += strtol(num, NULL, 10);
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

            int curr1 = wordToNumber(prefix);
            if (!d1 && curr1 != -1){
                num[0] = curr1;
                d1 = 1;
            }

            if (!d2 && isdigit(str[l-1-j])){
                num[1] = str[l-1-j];
                d2 = 1;
            }
            
            int curr2 = wordToNumber(strrev(suffix));
            if (!d2 && curr2 != -1){
                num[1] = curr2;
                d2 = 1;
            }
        }

        sum += strtol(num, NULL, 10);

    }

    printf("Part 2: %d\n", sum);

}

int main() {

    char **tokens;
    int n;

    tokenize_input(&tokens, &n, "inputs/day1.txt", "\n ");

    part1(tokens, n);
    part2(tokens, n);

    free_tokens(tokens, n);

    return 0;
}
