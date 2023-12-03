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

    tokenize_input(&tokens, &n, "inputs/day3.txt", "\n");
    int l = strlen(tokens[0]);

    int start = -1;
    int end = -1;

    int sum = 0;

    int gears[n][l];
    memset(gears, 0, sizeof(gears));

    int index = 0;


    for (int i = 0; i < n; i++){
        char* str = tokens[i];
    
        for (int j = 0; j < l+1; j++){
            if (j < l+1) gears[i][j] = -str[j];
            if (start == -1 && isdigit(str[j])) {start = j;}
            else if (start != -1 && !isdigit(str[j])){
                end = j;

                char num[32];
                for (int k = 0; k < 32; k++){
                    num[k] = ' ';
                }

                for (int k = 0; k < end-start; k++){
                    num[k] = str[start+k];
                }

                int val = strtol(num, NULL, 10);

                for (int k = start; k < end; k++){
                    gears[i][k] = val;
                }

                start = -1;
                end = -1;
            }
        }
    }


    int i = 0;
    int j = 0;
    int last = 0;
    int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[8] = {-1,  0,  1,-1, 1,-1, 0, 1};

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

    
    i = 0;
    j = 0;
    last = 0;
    long sum3 = 0;
    int nums[6] = {0};

    while (i < n){
        
        while (j < l){
            int k = 0;
            if (-gears[i][j] == '*'){



                if (gears[i][min(j+1, l-1)] > 0) nums[k++] = gears[i][min(j+1, l-1)];
                if (gears[i][max(j-1, 0)] > 0) nums[k++] = gears[i][max(j-1, 0)];
                if (gears[max(i-1, 0)][j] > 0) nums[k++] = gears[max(i-1, 0)][j];
                
                else if (gears[max(i-1, 0)][min(j+1, l-1)] > 0){
                    nums[k++] = gears[max(i-1, 0)][min(j+1, l-1)];
                    
                    if (gears[max(i-1, 0)][max(j-1, 0)] > 0){
                        nums[k++] = gears[max(i-1, 0)][max(j-1, 0)];
                    }
                }
                else if (gears[max(i-1, 0)][max(j-1, 0)] > 0){
                    nums[k++] = gears[max(i-1, 0)][max(j-1, 0)];
                    if (gears[max(i-1, 0)][min(j+1, l-1)] > 0){
                        nums[k++] = gears[max(i-1, 0)][min(j+1, l-1)];
                    }
                }

                if (gears[min(i+1, n-1)][j] > 0) nums[k++] = gears[min(i+1, n-1)][j];
                
                else if (gears[min(i+1, n-1)][max(j-1, 0)] > 0) {
                    nums[k++] = gears[min(i+1, n-1)][max(j-1, 0)];
                    if (gears[min(i+1, n-1)][min(j+1, l-1)] > 0){
                        nums[k++] = gears[min(i+1, n-1)][min(j+1, l-1)];
                    }
                } 
                else if (gears[min(i+1, n-1)][min(j+1, l-1)] > 0){
                    nums[k++] = gears[min(i+1, n-1)][min(j+1, l-1)];
                    if (gears[min(i+1, n-1)][max(j-1, 0)] > 0){
                        nums[k++] = gears[min(i+1, n-1)][max(j-1, 0)];
                    }
                }
                
                if (nums[2] == 0){
                    sum3 += nums[0] * nums[1];
                }

                for (int t = 0; t < 6; t++){
                    nums[t] = 0;
                }
                // vals[0] = 0;
                // vals[1] = 0;

            }
            j++;

        }
        j = 0;
        i++;
    }



    printf("sum: %d \n", sum3);


    free_tokens(tokens, n);

    return 0;
}
