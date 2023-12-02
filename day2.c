#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "utilities.h"
#include <errno.h>
#include "tokenization.h"

int getcolor(char* str){
    if (strstr(str, "red") != NULL) return 0;
    if (strstr(str, "green") != NULL) return 1;
    if (strstr(str, "blue") != NULL) return 2;
    return -1;
}

void part1(int arr[101][3]){
    int sum = 0;
    for (int i = 1; i <= 100; i++){
        if (arr[i][0] <= 12 && arr[i][1] <= 13 && arr[i][2] <= 14){
            sum += (i);
        }
    }
    printf("Part 1: %d\n", sum);
}

void part2(int arr[101][3]){
    int sum = 0;
    for (int i = 1; i <= 100; i++){
        sum += arr[i][0] * arr[i][1] * arr[i][2];
    }
    printf("Part 2: %d\n", sum);
}

int main() {

    char **tokens = (char**) malloc((INPUT_SIZE+1) * sizeof(char*));
    int n;

    tokenize_input(&tokens, &n, "day2.txt", ":;");

    int sum = 0;
    int k = 101;

    int arr[k][3];
    int gameIndex = 0;

    for (int i = 0; i < n; i++){
        if (strstr(tokens[i], "Game") != NULL){
            gameIndex++;
            arr[gameIndex][0] = 0;
            arr[gameIndex][1] = 0;
            arr[gameIndex][2] = 0;
            continue;
        }

        char* color = strtok(tokens[i], ",");
        while (color != NULL) {
            int j = getcolor(color);
            int val = strtol(color, NULL, 10);
            arr[gameIndex][j] = max(arr[gameIndex][j], val);
            color = strtok(NULL, ",");

        }
    }

    free_tokens(tokens, n);

    part1(arr);
    part2(arr);

    return 0;
}
