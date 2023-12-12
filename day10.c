#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h> 
#include <limits.h>
#include "tokenization.h"
#include "utilities.h"
#include "linkedlist.h"

int checkhit(int i, int j, int sq, char graph[sq][sq]){
    int inter = 0;
    for (int k = 0; k < sq; k++){
        for (int t = 0; t < sq; t++){
            
        } 
    }
    return 0;
}

linkedlist* find_loop_dfs(int n, int k, int adj[n][k], int start){
    int visited[n];
    memset(visited, 0, sizeof(visited));

    int length = 0;

    linkedlist* path = malloc(sizeof(linkedlist));
    path->front = NULL;
    path->rear = NULL;
    path->l = 0;

    linkedlist stack = {NULL, NULL};
    push(&stack, start);
    visited[start] = 1;
    int end = 0;

    while (!isempty(&stack) && !end){
        int curr = pop(&stack);
        length++;
        enqueue(path, curr);
        visited[curr] = 1;
        for (int i = 0; i < k; i++){
            if (adj[curr][i] == start && length >=3){
                end = 1;
                break;
            }

            if (adj[curr][i] != -1 && !visited[adj[curr][i]]){
                push(&stack, adj[curr][i]);
            }
        }
    }

    return path;
}

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
                dist[adj[curr][i]] = dist[curr]+1;
                visited[adj[curr][i]] = 1;
                enqueue(&q, adj[curr][i]);
            }
        }
    }


    return dist;
}   

double shoelace(linkedlist* flat_polygon, int rows, int cols){
    int A = 0;

    // printq(flat_polygon);

    node* curr = flat_polygon->front;
    while (curr->next != NULL){

        int coordinate = curr->val;
        int curr_row = coordinate / cols;
        int curr_col = coordinate % cols;

        int next_coor = curr->next->val;
        int next_row = next_coor / cols;
        int next_col = next_coor % cols;


        A += (curr_row+next_row) * (next_col-curr_col);

        curr = curr->next;
    }

    // edge case, last index
    A += ((curr->val)/cols + (flat_polygon->front->val)/cols) * ((flat_polygon->front->val)%cols - (curr->val)%cols);

    printf("\n");


    return 0.5 * abs(A);

}

int picks_theorem(int b, int A){
    return A - b/2 + 1;
}

int main() {

    char **tokens;
    int n;

    tokenize_input(&tokens, &n, "inputs/day10.txt", "\n");
    int ncols = strlen(tokens[0]);
    int length = (n+2) * (ncols+2);

    int graph[n+2][ncols+2];
    
    for (int i = 0; i < n+2; i++){
        graph[i][0] = '.';
        graph[i][ncols+1] = '.';
    }

    for (int i = 0; i < ncols+2; i++){
        graph[0][i] = '.';
        graph[n+1][i] = '.';
    }

    for (int i = 1; i < n+1; i++){
        for (int j = 1; j < ncols+1; j++){
            graph[i][j] = tokens[i-1][j-1];
        }
    }

    int adj[length][4];
    int pattern = -1;
    memset_pattern4(adj, &pattern, sizeof(int) * 4 * length);

    int sizes[(n+2)*(ncols+2)];
    memset(sizes, 0, sizeof(sizes));


    int start;
    // Building graph
    for (int i = 1; i < n+1; i++){
        for (int j = 1; j < ncols+1; j++){
            int index = i*(ncols+2) + j;
            int k = -1;
            int l = -1;
            if (graph[i][j] == 'S'){
                start = index;
                if (graph[i][j-1] == '-' || graph[i][j-1] == 'L' || graph[i][j-1] == 'F') {
                    adj[index][sizes[index]++] = index-1;
                }
                if (graph[i][j+1] == '-' || graph[i][j+1] == 'J' || graph[i][j+1] == '7') {
                    adj[index][sizes[index]++] = index+1;
                }
                if (graph[i+1][j] == '|' || graph[i+1][j] == 'L' || graph[i+1][j] == 'J') {
                    adj[index][sizes[index]++] = index+(ncols+2);
                }
                if (graph[i-1][j] == '|' || graph[i-1][j] == '7' || graph[i-1][j] == 'F'){
                    adj[index][sizes[index]] = index-(ncols+2);
                }
                continue;

            }


            if (graph[i][j] == '|'){
                k = index - (ncols+2);
                l = index + (ncols+2);
            }

            if (graph[i][j] == '-'){
                k = index -1;
                l = index +1;
            }

            if (graph[i][j] == 'L'){
                k = index -(ncols+2);
                l = index + 1;
            }

            if (graph[i][j] == 'J'){
                k = index - (ncols+2);
                l = index -1;
            }

            if (graph[i][j] == '7'){
                k = index + (ncols+2);
                l = index - 1;
            }

            if (graph[i][j] == 'F'){
                k = index + (ncols+2);
                l = index + 1;
            }


            adj[index][sizes[index]++] = k;
            adj[index][sizes[index]] = l;
        }
       //  printf("\n");
    }

    linkedlist* cycle = find_loop_dfs((n+2)*(ncols+2), 4, adj, start);

    int adj2[cycle->l][2]; // Build graph of cycle
    memset(adj2, 0, sizeof(adj2));
    adj2[0][0] = 1;
    adj2[0][1] = cycle->l -1;

    for (int i = 1; i < cycle->l; i++){
        adj2[i][0] = (i-1)%(cycle->l);
        adj2[i][1] = (i+1)%(cycle->l);
    }
   
    int* dist = distances_bfs(cycle->l, 2, adj2, 0);

    int maximum = INT_MIN;

    for (int i = 0; i < cycle->l; i++){
        if (dist[i] < INT_MAX){
            maximum = max(dist[i], maximum);
        }
    }


    printf("Part 1: %d", maximum);

    double A = shoelace(cycle, n+2, ncols+2);
    int inner = picks_theorem(cycle->l, A);

    printf("Part 2: %d\n", inner);

    free(dist);
    freelist(cycle);
    free_tokens(tokens, n);

    return 0;
}
