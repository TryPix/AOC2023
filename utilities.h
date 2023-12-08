#include <stdlib.h>
#include <string.h>

char* strrev(char* str){
    int l = strlen(str);
    char* temp = (char*) malloc((l+1) * sizeof(char));

    for (int i = 0; i < l; i++){
        temp[i] = str[l-1-i];
    }

    return temp;
}

int max(int a, int b){
    return a >= b ? a : b;
}

int min(int a, int b){
    return a <= b ? a : b;
}

void swap(int n, int arr[n], int i, int j){
    int t = arr[i];
    arr[i] = arr[j];
    arr[j] = i;
}

long gcd(long a, long b){
    if (b==0) return a;
    return gcd(b, a % b);
}

long lcm(long a, long b){
   return (a*b)/ gcd(a, b);
}





