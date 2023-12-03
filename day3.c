#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h> 
#include "tokenization.h"
#include "utilities.h"

void parsetogrid(int n, int l, int gears[n][l], char*** tokens){

    int start = -1;
    int end = -1;
    

    for (int i = 0; i < n; i++){
        char str[l+1];
        strcpy(str, (*tokens)[i]);
        str[l] = '.';
    
        for (int j = 0; j < l+1; j++){ // l+1 for edge case of number at the end of the line
            if (j < l+1) gears[i][j] = -str[j];

            if (start == -1 && isdigit(str[j])) {start = j;}

            else if (start != -1 && !isdigit(str[j])){

                end = j;

                char num[4];
                memset(num, 0, sizeof(num));

                for (int k = 0; k < end-start; k++) num[k] = str[start+k];

                int val = strtol(num, NULL, 10);

                for (int k = start; k < end; k++) gears[i][k] = val;

                start = -1; end = -1;
            }
        }
    }

}

void part1(int dr[8], int dc[8], int n, int l, int gears[n][l]){

    int sum = 0;
    int i = 0;
    int j = 0;
    int last = 0;

    while (i < n){
        
        while (j < l){
            if (gears[i][j] < 0 || gears[i][j] == last){
                j++; continue;
            }

            for (int t = 0; t < 8; t++){
                int row = i + dr[t];
                int col = j + dc[t];
                if (row < n && col < l && -gears[row][col] != '.' && gears[row][col] < 0){
                    last = gears[i][j];
                    sum += gears[i][j];
                    break;
                }
            }
            j++;

        }
        j = 0;
        i++;
    }

    printf("sum: %d \n", sum);

}

void part2(int dr[8], int dc[8], int n, int l, int gears[n][l]){
    int i = 0;
    int j = 0;
    int sum = 0;
    int nums[6] = {0};
    int last = 0;
    int check[8]; memset(check, 1, sizeof(check));

    while (i < n){
        
        while (j < l){
            int k = 0;
            if (-gears[i][j] == '*'){

                for (int t = 0; t < 8; t++){
                    if (check[t] == 0) continue;
                    int row = i + dr[t];
                    int col = j + dc[t];
                    if (row < n && col < l && gears[row][col] > 0){
                        nums[k++] = gears[row][col];
                        if (t == 2 || t == 5){
                            check[t+1] = 0;
                            check[t+2] = 0;
                        }
                    }
                }
                
                if (nums[2] == 0){
                    sum += nums[0] * nums[1];
                }

                memset(nums, 0, sizeof(nums));
                memset(check, 1, sizeof(check));

            }
            j++;

        }
        j = 0;
        i++;
    }

    printf("sum: %d \n", sum);




}

int main() {

    char **tokens;
    int n;

    tokenize_input(&tokens, &n, "inputs/day3.txt", "\n");
    int l = strlen(tokens[0]);

    

    int sum = 0;

    int gears[n][l];
    memset(gears, 0, sizeof(gears));

    parsetogrid(n, l, gears, &tokens);


    int dr[8] = {0, 0, -1, -1, -1, 1, 1, 1}; // order not arbitrary for part 2
    int dc[8] = {-1, 1, 0, -1,  1, 0,-1 ,1};

    part1(dr,dc,n,l,gears);
    part2(dr,dc,n,l,gears);
    
    free_tokens(tokens, n);

    return 0;
}
