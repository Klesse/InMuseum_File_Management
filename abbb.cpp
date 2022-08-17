#include <stdio.h>
#include <stdlib.h>

typedef int rrn;
typedef int key;

typedef struct node{
    int bal;
    key id;
    rrn rrn;
    struct node *root;
    struct node *left;
    struct node *right;
} node;

typedef node *avl;



