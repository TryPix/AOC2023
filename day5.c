#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h> 
#include <limits.h>
#include <pthread.h>
#include "tokenization.h"
#include "utilities.h"

int n;
long transforms[7][64][3];
long sizes[7];
long seeds[32];
int nseeds;

typedef struct
{
    long start;
    long length;

    long min_location;
} Range;

long map1stage(long seed, long size, long transform[size][3]){
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

void map(void *arg){

    Range* r = (Range*) arg;

    long best = LONG_MAX;
    long start = r->start;
    long length = r->length;

    for (long i = start; i < start+length; i++){
        long val = i;
        for (long j = 0; j < 7; j++){
            val = map1stage(val, sizes[j], transforms[j]);
        }
        best = val < best ? val : best;
    }

    r->min_location = best;
}

void* map_threads(void *arg){
    Range* r = (Range*) arg;
    map(r);
    pthread_exit(NULL);
}

void parse(char*** tokens){

    long index = 1;
    while (isdigit((*tokens)[index][0])){
        seeds[index-1] = strtol((*tokens)[index], NULL, 10);
        index++;
    }
    nseeds = index-1;

    int transform_index = 0;
    int curr_index = 0;


    memset(sizes, 0, 7);
    long rot = 0;

    for (long i = index+2; i < n; i++){
        if (!isdigit((*tokens)[i][0])){
            sizes[transform_index] = curr_index;
            transform_index++;
            i++;
            curr_index = 0;
            rot = 0;
            continue;
        }
        transforms[transform_index][curr_index][rot] = strtol((*tokens)[i], NULL, 10);
        rot++;
        if(rot==3){
            curr_index++;
            rot=0;
        }
    }

    free_tokens((*tokens), n);

    sizes[6] = curr_index;

}

void part1(){
    long best = LONG_MAX;

    for (int i = 0; i < nseeds; i++){
        Range r;
        r.length = 1;
        r.start = seeds[i];
        map(&r);
        best = r.min_location < best ? r.min_location : best;
    }

    printf("Part 1: %ld\n", best);
}

void part2(){

    long best = LONG_MAX;
    Range ranges[nseeds];
    
    for (int i = 0; i < nseeds; i+=2){
        Range r;
        r.start = seeds[i];
        r.length = seeds[i+1];
        r.min_location = LONG_MAX;
        ranges[i / 2] = r;
    }

    int k = nseeds/2;
    pthread_t threads[k];

    for (int i = 0; i < k; i++){
        int rc = pthread_create(&threads[i], NULL, map_threads, (void*) &ranges[i]);
        if (rc) printf("Error: Unable to create thread #%d\n", i);
    }

    for (int i = 0; i < k; i++) {
        pthread_join(threads[i], NULL);
        best = ranges[i].min_location < best ? ranges[i].min_location : best;
    }

    printf("Part 2: %ld\n", best);

}

int main() {

    char **tokens;

    tokenize_input(&tokens, &n, "inputs/day5.txt", "\n ");

    parse(&tokens);

    part1();
    part2();

    return 0;
}
