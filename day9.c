#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h> 
#include <limits.h>
#include "tokenization.h"
#include "utilities.h"

void parse(int n, char*** tokens, int sequences[n][64], int sequences1[n][64], int sizes[n]){

    for (int i = 0; i < n; i++){
        char* token = strtok((*tokens)[i], " ");
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

}

void part1(int n, int sequences[n][64], int sizes[n]){

    long sum = 0;

    for (int i = 0; i < n; i++){
    int size = sizes[i];
    for (int k = size; k > 1; k--){
        for (int j = 0; j < k-1; j++){
            sequences[i][j] = sequences[i][j+1] - sequences[i][j];
            }
        }   
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < sizes[i]; j++){
            sum += sequences[i][j];
        }
    }

    printf("Part 1: %ld\n", sum);

}

void part2(int n, int sequences[n][64], int sizes[n]){

    long sum = 0;

    for (int i = 0; i < n; i++){
        int size = sizes[i];
        for (int k = 0; k < size-1; k++){
            for (int j = size-1; j > k; j--){
                sequences[i][j] = sequences[i][j] - sequences[i][j-1];
            }
        }
    }


    for (int i = 0; i < n; i++){
        int s = 0;
        for (int j = 0; j < sizes[i]; j++){
            if (j%2) s -= sequences[i][j];
            else s += sequences[i][j];
        }
        sum += s;
    }

    printf("Part 2: %ld\n", sum);
}


int main() {

    char **tokens;
    int n;

    tokenize_input(&tokens, &n, "inputs/day9.txt", "\n");
    int sequences[n][64];
    int sequences1[n][64]; // copy for part 2
    int sizes[n];

    parse(n, &tokens, sequences, sequences1, sizes);

    part1(n, sequences, sizes);
    part2(n, sequences1, sizes);

    free_tokens(tokens, n);

    return 0;
}
