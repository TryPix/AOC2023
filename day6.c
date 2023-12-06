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

    long long time =  49979494;
    long long dist = 263153213781851;
    long w = 0;

    for (int i = 1; i  < 5; i++){
        times[i-1] = strtol(tokens[i], NULL, 10);
        dists[i-1] = strtol(tokens[i+5], NULL, 10);
    }

    for (int i = 1; i < 5; i++){

    }

    long sum = 1;

    for (int i = 0; i < 4; i++){
        long ways = 0;
        int max = times[i]-1;
        int dist = dists[i];
        for (int j = 1; j < max; j++){
            long distance = j * (times[i]- j);  
            if (distance > dist){
                ways++;
            }
        }
        if (ways!=0){
            sum *= ways;
        }
        
    }

    for (int i = 1; i < time-1; i++){
        if (i * (time - i) > dist) w++;
    }

    printf("Part 1: %ld\n", sum);
    printf("Part 2: %ld\n", w);


    free_tokens(tokens, n);

    return 0;
}
