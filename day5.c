#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h> 
#include <limits.h>
#include "tokenization.h"
#include "utilities.h"

long long applytransform(long long seed, long long size, long long transform[size][3]){
    for (long long i = 0; i < size; i++){
        long long dest_r = transform[i][0];
        long long source_r = transform[i][1];
        long long length = transform[i][2];
        // prlong longf("%d %d %d\n", dest_r, source_r, length);
        if (seed >= source_r && seed <= source_r+length-1){
            long long diff = dest_r-source_r;
            return seed + diff;
        }
    }
    return seed;

}

int main() {

    char **tokens;
    int n;

    tokenize_input(&tokens, &n, "inputs/day5.txt", "\n ");

    long long seeds[32];
    memset(seeds, 0, 32);
    long long s = 0;

    long long transforms[7][64][3];
    memset(transforms, 0, sizeof(transforms));
    long long t_index = 0;

    long long index = 1;
    while (isdigit(tokens[index][0])){
        seeds[index-1] = strtol(tokens[index], NULL, 10);
        index++;
    }
    long long nseeds = index-1;

    long long transform_index = 0;
    long long curr_index = 0;

    long long sizes[7];
    memset(sizes, 0, 7);
    long long rot = 0;

    for (long long i = index+2; i < n; i++){
        // prlong longf("%s ", tokens[i]);
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

    sizes[6] = curr_index;

    // prlong longf("\n\n");
    // for (long long i = 0; i < 7; i++){
    //     prlong longf("size: %d\n", sizes[i]);
    //     for (long long j = 0; j < sizes[i]; j++){
    //         for (long long k = 0; k < 3; k++){
    //             prlong longf("%d ", transforms[i][j][k]);
    //         }
    //         prlong longf("\n");
    //     }
    //     prlong longf("\n");
    // }

    long long best = LONG_MAX;

    for (long long seed = 0; seed < nseeds; seed++){
        long long val = seeds[seed];
        for (long long i = 0; i < 7; i++){
            val = applytransform(val, sizes[i], transforms[i]);
        }
        if (val < best){
            best = val;
        }
    }

    best = LONG_MAX;

    for (long long i = 0; i < nseeds; i += 2){
        long long start = seeds[i];
        long long length = seeds[i+1];
        for (long long seed = start; seed < start + length-1; seed++){
            // printf("%d %d\n", length, val);
            long long val = seed;
            for (long long i = 0; i < 7; i++){
                val = applytransform(val, sizes[i], transforms[i]);
            }
            if (val < best){
                best = val;
            }
        }

    }

    // prlong longf("%d %d", seeds[2], applytransform(seeds[2], sizes[0], transforms[0]));
    printf("%lld", best);
    




    free_tokens(tokens, n);

    return 0;
}
