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

    tokenize_input(&tokens, &n, "inputs/day6.txt", "\n ");

    int times[5];
    int dists[5];

    for (int i = 1; i  < 5; i++){
        times[i-1] = strtol(tokens[i], NULL, 10);
        dists[i-1] = strtol(tokens[i+5], NULL, 10);
    }

    long sum = 1;

    for (int i = 0; i < 4; i++){
        long ways = 0;
        int max = times[i]-1;
        int dist = dists[i];
        for (int j = 1; j < times[i]-1; j++){
            long distance = j * (times[i]- j);  
            if (distance > dist){
                ways++;
            }
        }
        sum *= ways;
        
    }

    char t[32];
    char d[64];

    long time;
    long dist;
    long w = 0;

    for (int i = 1; i < 5; i++){
        strcat(t, tokens[i]);
        strcat(d, tokens[i+5]);
    }
    time = strtol(t, NULL, 10);
    dist = strtol(d, NULL, 10);

    for (int i = 1; i < time-1; i++){
        if (i * (time - i) > dist) w++;
    }

    printf("Part 1: %ld\n", sum);
    printf("Part 2: %ld\n", w);


    free_tokens(tokens, n);

    return 0;
}
