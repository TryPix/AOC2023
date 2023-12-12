#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int val;
    struct node* next;
} node;

typedef struct linkedlist {
    node* front;
    node* rear;
    int l;
} linkedlist;


int isempty(linkedlist* q){
    if (q->rear == NULL){
        return 1;
    }
    return 0;
}

void enqueue(linkedlist* q, int v){

    node* n = (node*) malloc(sizeof(node));
    n->val = v;
    q->l++;

    if (isempty(q)){
        q->front = n;
        q->rear = n;
        return;
    }
    q->rear->next = n;
    q->rear = n;
}

void push(linkedlist* q, int v){
    node* n = (node*) malloc(sizeof(node));
    n->val = v;
    q->l++;

    if (isempty(q)){
        q->front = n;
        q->rear = n;
        return;
    }
    n->next = q->front;
    q->front = n;
}

int dequeue(linkedlist* q){
    if (isempty(q)){
        printf("Nothing to dequeue\n");
        return -1;
    } else if (q->front==q->rear){
        q->l--;
        node* n = q->front;
        q->front = NULL;
        q->rear = NULL;
        return n->val;
    }
    q->l--;
    node* n = q->front;
    q->front = n->next;
    return n->val;
}

int pop(linkedlist* q){
    return dequeue(q);
}

void printq(linkedlist* q){
    if (isempty(q)) return;

    node* node = q->front;

    while (node != q->rear->next) {
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");
}

void freelist(linkedlist *q){
    node* curr = q->front;
    while (curr->next != NULL){
        node* prev = curr;
        curr = curr->next;
        free(prev);
    }
}
