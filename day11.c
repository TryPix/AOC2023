#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h> 
#include <limits.h>
#include "tokenization.h"
#include "utilities.h"
#include "linkedlist.h"

int* distances_bfs(int n, int k, int adj[n][k], int start){

    int visited[n];
    memset(visited, 0, sizeof(visited));
    int* dist = malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) dist[i] = INT_MAX;

    linkedlist q = {NULL, NULL};
    enqueue(&q, start);
    visited[start] = 1;
    dist[start] = 0;

    while(!isempty(&q)){
        int curr = dequeue(&q);

        for (int i = 0; i < k; i++){
            if (adj[curr][i] != -1 && !visited[adj[curr][i]]){
                dist[adj[curr][i]] = min(dist[curr]+1, dist[adj[curr][i]]);
                visited[adj[curr][i]] = 1;
                enqueue(&q, adj[curr][i]);
            }
        }
    }

    return dist;
}   

int main() {

    char **tokens;
    int n;

    tokenize_input(&tokens, &n, "inputs/day11.txt", "\n");

    int m = strlen(tokens[0]);
    int expanded_lines[n]; memset(expanded_lines, 0, sizeof(expanded_lines));
    int expanded_cols[m]; memset(expanded_cols, 0, sizeof(expanded_cols));

    int nrows = n;
    int ncols = m;

    // detect lines and cols to double
    for (int i = 0; i < n; i++){
        int containsgalaxy = 0;
        for (int j = 0; j < m; j++){
            if (tokens[i][j] == '#'){
                containsgalaxy = 1;
                break;
            }
        }

        if (containsgalaxy){
            expanded_lines[i] = 1;
        } else {
            nrows++;
        }
    }

    for (int j = 0; j < m; j++){
        int containsgalaxy = 0;
        for (int i = 0; i < n; i++){
            if (tokens[i][j] == '#'){
                containsgalaxy = 1;
                break;
            }
        }

        if (containsgalaxy){
            expanded_cols[j] = 1;
        } else {
            ncols++;
        }
    }
    

    int r_offset = 0;

    char grid[nrows][ncols];
    memset(grid, 0, sizeof(grid));

    for (int i = 0; i < n; i++){
        int c_offset = 0;
        for (int j = 0; j < m; j++){
            grid[i+r_offset][j+c_offset] = tokens[i][j];
            if (expanded_cols[j] == 0){
                c_offset++;
                grid[i+r_offset][j+c_offset] = '.';
            }
        }
        if (expanded_lines[i] == 0){
            r_offset++;
            for (int j = 0; j < ncols; j++){
                grid[i+r_offset][j] = '.';
            }

        }
    }


    linkedlist galaxies = {NULL, NULL};

    for (int i = 0; i < nrows; i++){
        for (int j = 0; j < ncols; j++){
            int index = i*ncols+j;
            if (grid[i][j] == '#'){
                enqueue(&galaxies, index);
            }
        }
    }

    // printq(&galaxies);
    // Build Graph

    int adj[nrows*ncols][4];
    for (int i = 0; i < nrows*ncols; i++){
        for (int j = 0; j < 4; j++){
            adj[i][j] = -1;
        }
    }

    int sizes[nrows*ncols]; memset(sizes, 0, sizeof(sizes));
    int dr[4] = {0, 0, 1, -1};
    int dc[4] = {1, -1, 0, 0};

    for (int i = 0; i < nrows; i++){
        for (int j = 0; j < ncols; j++){
            int index = i*ncols + j;
            for (int k = 0; k < 4; k++){
                int ii = i + dr[k];
                int jj = j + dc[k];
                if (ii < 0 || ii >= nrows || jj < 0 || jj >= ncols) continue;
                adj[index][sizes[index]++] = ii*ncols + jj;
            }
        }
    }

    // for (int i = 0; i < nrows*ncols; i++){
    //     for (int j = 0; j < 4; j++){
    //         printf("%d ", adj[i][j]);
    //     }
    //     printf("\n");
    // }

    int gal[galaxies.l];
    node* curr = galaxies.front;
    for (int i = 0; i < galaxies.l; i++){
        gal[i] = curr->val;
        curr = curr->next;
    }

    int sum = 0;
    // printf("\n");

    for (int i = 0; i < galaxies.l; i++){
        int* dist = distances_bfs(nrows*ncols, 4, adj, gal[i]);
        for (int j = i+1; j < galaxies.l; j++){
            sum += dist[gal[j]];
            // printf("%d ", dist[gal[j]]);
        }
    }

    // printf("\n");




    // for (int i = 0; i < nrows; i++){
    //     for (int j = 0; j < ncols; j++){
    //         printf("%c", grid[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("%d ", sum);



    freelist(&galaxies);



    free_tokens(tokens, n);

    return 0;
}
