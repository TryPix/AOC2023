#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024
#define INPUT_SIZE 1024

void tokenize_input(char ***tokens, int* n, char* file, char* delimiters){

    int size = INPUT_SIZE+1;

    *tokens = (char**) malloc((INPUT_SIZE+1) * sizeof(char*));

    char buffer[BUFFER_SIZE];
    const char *delimiter_characters = delimiters;

    FILE *fp = fopen(file, "r");
    if (!fp){
        fprintf(stderr, "cannot open %s: %s\n", "test.txt", strerror(errno));
    }

    char *token;

    int i = 0;
    while (fgets(buffer, BUFFER_SIZE, fp)) {
        token = strtok(buffer, delimiter_characters);

        while (token != NULL){ 

            if (i >= size){ // dynamically change size of array
                size *= 2;
                char** temp = (char**) realloc(*tokens, (size+1) * sizeof(char*));
                if (temp == NULL){
                    printf("Error in allocation");
                    return;
                }
                tokens = &temp;
            }

            char* temp = (char*) malloc((strlen(token)+1) * sizeof(char));
            if (temp == NULL){
                printf("Error in allocation");
                return;
            }   
            (*tokens)[i] = temp;
            strcpy((*tokens)[i], token);
            token = strtok(NULL, delimiter_characters);
            i++;
        }            
    }

    *n = i;
    
    fclose(fp);
}

void free_tokens(char** tokens, int n){
    for (int i = 0; i < n; i++){
        free(tokens[i]);
    }
    free(tokens);
}
