#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h> 
#include <limits.h>
#include "tokenization.h"
#include "utilities.h"

int main() {

    char **tokens;
    int n;

    tokenize_input(&tokens, &n, "inputs/day9.txt", "\n");

    int sequences[n][64];
    int sizes[n];
    memset(sequences, 0, sizeof(sequences));
    memset(sizes, 0, sizeof(sizes));

    int sequences1[n][64];
    memset(sequences1, 0, sizeof(sequences1));

    for (int i = 0; i < n; i++){
        char* token = strtok(tokens[i], " ");
        int j = 0;
        while (token != NULL){
            int v = strtol(token, NULL, 10);
            sequences[i][j] = v;
            sequences1[i][j] = v;
            token = strtok(NULL, " ");
            j++;
        }
        sizes[i] = j;
    } 

    for (int i = 0; i < n; i++){
        int allzeros = 0;
        int size = sizes[i];
        while(allzeros == 0 || size > 1){
            allzeros = 1;
            for (int j = 0; j < size-1; j++){
                sequences1[i][j] = sequences1[i][j+1] - sequences1[i][j];
                if (sequences1[i][j] != 0) allzeros = 0;
            }
            size--;
        }
    }

    for (int i = 0; i < n; i++){
    int allzeros = 0;
    int size = sizes[i];
    int dist = 0;
    while(allzeros == 0 || dist < size-1){
        allzeros = 1;
        for (int j = size-1; j > dist; j--){
            sequences[i][j] = sequences[i][j] - sequences[i][j-1];
            if (sequences[i][j] != 0) allzeros = 0;
        }
        dist++;
    }
}


    long sum = 0;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < sizes[i]; j++){
            sum += sequences1[i][j];
        }
    }


    long sum2 = 0;

    for (int i = 0; i < n; i++){
        int s = 0;
        for (int j = 0; j < sizes[i]; j++){
            if (j%2) s -= sequences[i][j];
            else s += sequences[i][j];
        }
        sum2 += s;
    }

    printf("Part 1: %ld\n", sum);
    printf("Part 2: %ld\n", sum2);

    free_tokens(tokens, n);

    return 0;
}
