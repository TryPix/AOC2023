#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h> 
#include "tokenization.h"
#include "utilities.h"

int main() {

    char **tokens;
    int n;

    tokenize_input(&tokens, &n, "inputs/day4.txt", "\n");

    int sum = 0;
    int sum2 = 0;

    int scratch[n];

    int pattern = 1;
    memset_pattern4(scratch, &pattern, sizeof(scratch));

    for (int i = 0; i < n; i++) scratch[i] = 1;

    for (int i = 0; i < n; i++){
        char* str = tokens[i];
        char* num = strtok(str, ":");
        int win[10];
        int all[25];
        int j = -1;
        int k = 0;
        int ch = 1;
        while (num != NULL){
            if (strstr(num, "|")){
                ch = 0;
            } else if (ch) {
                win[j] = strtol(num, NULL, 10);
                j++;
            } else { all[k] = strtol(num, NULL, 10);
                k++;
            }
            num = strtok(NULL, " ");
        }

        int factor = 0;
        int nCards = 0;

        for (int t = 0; t < j; t++){
            int v = win[t];

           
            for (int l = 0; l < k; l++){
                if (v == all[l]){
                    if (factor == 0) {factor = 1; nCards++; break;}
                    factor *= 2;
                    nCards++;
                    break;
                }
            }
        }
        sum += factor;

        for (int t = 0; t < nCards; t++){
            scratch[i+t+1] += scratch[i];
            
            ;
        }
    }

    for (int i = 0; i < n; i++){
        sum2 += scratch[i];
    }

    printf("Part 1: %d\n", sum);
    printf("Part 2: %d\n", sum2);


    free_tokens(tokens, n);

    return 0;
}
