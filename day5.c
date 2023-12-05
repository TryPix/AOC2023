#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h> 
#include <limits.h>
#include "tokenization.h"
#include "utilities.h"

long applytransform(long seed, long size, long transform[size][3]){
    for (long i = 0; i < size; i++){
        long dest_r = transform[i][0];
        long source_r = transform[i][1];
        long length = transform[i][2];
        if (seed >= source_r && seed <= source_r+length-1){
            long diff = dest_r-source_r;
            return seed + diff;
        }
    }
    return seed;
}


int main() {

    char **tokens;
    int n;

    tokenize_input(&tokens, &n, "inputs/day5.txt", "\n ");

    long seeds[32];
    memset(seeds, 0, 32);

    long transforms[7][64][3];
    memset(transforms, 0, sizeof(transforms));

    long index = 1;
    while (isdigit(tokens[index][0])){
        seeds[index-1] = strtol(tokens[index], NULL, 10);
        index++;
    }
    long nseeds = index-1;

    long transform_index = 0;
    long curr_index = 0;

    long sizes[7];
    memset(sizes, 0, 7);
    long rot = 0;

    for (long i = index+2; i < n; i++){
        if (!isdigit(tokens[i][0])){
            sizes[transform_index] = curr_index;
            transform_index++;
            i++;
            curr_index = 0;
            rot = 0;
            continue;
        }
        transforms[transform_index][curr_index][rot] = strtol(tokens[i], NULL, 10);
        rot++;
        if(rot==3){
            curr_index++;
            rot=0;
        }
    }

    free_tokens(tokens, n);

    sizes[6] = curr_index;

    long best = LONG_MAX;

    for (long seed = 0; seed < nseeds; seed++){
        long val = seeds[seed];
        for (long i = 0; i < 7; i++){
            val = applytransform(val, sizes[i], transforms[i]);
        }
        if (val < best){
            best = val;
        }
    }

    printf("Part 1: %ld\n", best);

    best = LONG_MAX;

    for (long i = 0; i < nseeds; i += 2){
        long start = seeds[i];
        long length = seeds[i+1];
        for (long seed = start; seed < start + length-1; seed++){
            long val = seed;
            for (long i = 0; i < 7; i++){
                val = applytransform(val, sizes[i], transforms[i]);
            }
            if (val < best){
                best = val;
            }
        }

    }
    printf("Part 2: %ld\n", best);
    

    return 0;
}
