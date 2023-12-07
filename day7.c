#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h> 
#include <limits.h>
#include "tokenization.h"
#include "utilities.h"

#define JOKER_INDEX 3

char CARDS[13] = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};

typedef struct {
    char* hand;
    int bid;
    int strength;
} Hand;

int cardstrength(int card){ // less is more!
    for (int i = 0; i < 13; i++){
        if (card == CARDS[i]) return i;
    }
    return -1;
}

void countNcards(int ncards[13], Hand* hand){

    char* str = hand->hand;

    for (int i = 0; i < 5; i++){
        char c = str[i];
        ncards[cardstrength(c)]++;
    }
}

int hasksame(Hand* hand, int k, int part2){
    int ncards[13];
    memset(ncards, 0, 13* sizeof(int));
    countNcards(ncards, hand);

    if (part2){
        int maxIndex = 0;
        int mmax = INT_MIN;

        for (int i = 0; i < 13; i++){
            if (i == JOKER_INDEX) continue;
            if (ncards[i] > mmax){
                mmax = ncards[i];
                maxIndex = i;
            }
        }
        ncards[maxIndex] = ncards[maxIndex] + ncards[JOKER_INDEX];
        ncards[JOKER_INDEX] = 0;
    }

    for (int i = 0; i < 13; i++){
        if (ncards[i] == k) return 1;
    }

    return 0;
}

int istwopair(Hand* h){
    int ncards[13];
    memset(ncards, 0, sizeof(ncards));
    countNcards(ncards, h);

    int cnt = 0;
    for (int i = 0; i < 13; i++){
        if (ncards[i] == 2) cnt++;
    }

    return cnt == 2;
}

void findhand(Hand* hand, int part2){
    if (hasksame(hand, 5, part2)) hand->strength = 7;
    else if (hasksame(hand, 4, part2)) hand->strength = 6;
    else if (hasksame(hand, 3, part2) && hasksame(hand, 2, part2)) hand->strength = 5;
    else if (hasksame(hand, 3, part2)) hand->strength = 4;
    else if (istwopair(hand)) hand->strength = 3;
    else if (hasksame(hand, 2, part2)) hand->strength = 2;
    else if (hasksame(hand, 1, part2)) hand->strength = 1;
}

int comparehands(const void* v1, const void* v2){


    Hand *h1 = (Hand *) v1;
    Hand *h2 = (Hand *) v2;
    
    if (h1->strength > h2->strength){
        return 1;
    } else if (h1->strength < h2->strength){
        return -1;
    } else{
        for (int i = 0; i < 5; i++){
            char c1 = h1->hand[i];
            char c2 = h2->hand[i];

            int s1 = cardstrength(c1);
            int s2 = cardstrength(c2);

            if (s1 < s2) return 1;
            if (s1 > s2) return -1;
        }
    }
    return 0;
}

int comparehands2(const void* v1, const void* v2){


    Hand *h1 = (Hand *) v1;
    Hand *h2 = (Hand *) v2;
    
    if (h1->strength > h2->strength){
        return 1;
    } else if (h1->strength < h2->strength){
        return -1;
    } else{
        for (int i = 0; i < 5; i++){
            char c1 = h1->hand[i];
            char c2 = h2->hand[i];

            int s1 = cardstrength(c1);
            int s2 = cardstrength(c2);

            if (c1 == 'J') s1 = 100;
            if (c2 == 'J') s2 = 100;

            if (s1 < s2) return 1;
            if (s1 > s2) return -1;
        }
    }
    return 0;
}

void parse(char*** tokens, int n, Hand hands[n], int part){
    for (int i = 0; i < n; i++){
        Hand h;
        char* token;
        token = strtok((*tokens)[i], " "); 
        h.hand = token;
        token = strtok(NULL, " "); 
        h.bid = strtol(token, NULL, 10);
        findhand(&h, 0);
        hands[i] = h;
    }
}

long winnings(int n, Hand hands[n]){
    long count = 0;
     for (int i = 0; i < n; i++){
        count += (i+1) * hands[i].bid;
    }   
    return count;
}

void modhands(int n, Hand hands[n]){
    for (int i = 0; i < n; i++) findhand(&hands[i], 1);
}

int main() {

    char **tokens;
    int n;

    tokenize_input(&tokens, &n, "inputs/day7.txt", "\n");

    Hand hands[n];
    parse(&tokens, n, hands, 0);

    qsort(hands, n, sizeof(Hand), comparehands);
    printf("Part 1: %ld\n",  winnings(n, hands));

    modhands(n, hands);
    qsort(hands, n, sizeof(Hand), comparehands2);
    printf("Part 2: %ld\n", winnings(n, hands));  

    free_tokens(tokens, n);


    return 0;
}
