#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h> 
#include "tokenization.h"
#include "utilities.h"

typedef struct Node {
    char* name;
    struct Node* left;
    struct Node* right;
} Node;


int search(char* name, int n, Node nodes[n]){
    for (int i = 0; i < n; i++){
        char* n = nodes[i].name;
        if (strcmp(n, name) == 0){
            return i;
        }
    }
    return -1;
}

int alldone(int n, int done[n]){
    for (int i = 0; i < n; i++){
        if (done[i] == 0) return 0;
    }
    return 1;
}


int main() {

    char **tokens;
    int n;

    tokenize_input(&tokens, &n, "inputs/day8.txt", "\n");
    char* directions = tokens[0];
    Node nodes[n];
    Node right[n];
    Node left[n];

    for (int i = 1; i < n; i++){
        char* token = strtok(tokens[i], " =(,)");
        Node n; 
        n.name = token;
        nodes[i-1] = n;

        token = strtok(NULL, " =(,)");
        Node n1;
        n1.name = token;
        left[i-1] = n1;

        token = strtok(NULL, " =(,)");
        Node n2;
        n2.name = token;
        right[i-1] = n2;
    }

    for (int i = 0; i < n-1; i++){
        int j = search(left[i].name, n-1, nodes);
        nodes[i].left = &nodes[j];

        int k = search(right[i].name, n-1, nodes);
        nodes[i].right = &nodes[k];      
    }

    int l = strlen(directions);
    int k = 0;
    Node currs[n];

    for (int i = 0; i < n-1; i++){
        if (nodes[i].name[2] == 'A'){
            currs[k] = nodes[i];
            k++;
        }
    }

    int d = 0;
    long cnt = 0;
    Node curr = currs[4];

    while (d == 0){
        for (int i = 0; i < l; i++){
            char dir = directions[i];
            if (strstr(curr.name, "ZZZ")){
                d = 1;
                break;
            }
            curr = dir == 'L' ? *(curr.left) : *(curr.right);
            cnt++;
        }
    }


    int count = 0;
    int done[k];
    memset(done, 0, sizeof(done));
    int end = 0;

    long counts[k];
    memset(counts, 0, sizeof(counts));

    while (end == 0){
        for (int i = 0; i < l; i++){
            char dir = directions[i];

            int finished = 1;
            for (int j = 0; j < k; j++){
                if (currs[j].name[2] == 'Z'){
                    done[j] = 1;
                    if (counts[j] == 0) counts[j] = count;
                }
            }

            if (alldone(k, done)){
                end = 1;
                break;
            }

            if (dir == 'L'){
                for (int j = 0; j < k; j++){
                    currs[j] = *(currs[j].left);
                }
            } else {
                for (int j = 0; j < k; j++){
                    currs[j] = *(currs[j].right);
                } 
            }
            count++;
        }
    }


    long ans = counts[0];

    for (int i = 0; i < k; i++){
        ans = lcm(ans, counts[i]);
    }

    printf("Part 1: %ld\n", cnt);
    printf("Part 2: %ld\n", ans);

    free_tokens(tokens, n);

    return 0;
}
