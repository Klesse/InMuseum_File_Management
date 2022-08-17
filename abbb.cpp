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

node *NewNode(key id, rrn rrn);
avl rotationRight(avl r);
avl rotationLeft(avl r);
avl insertAVL(node *r, node *novo, int *increased_height);
avl insert(avl r, key id, rrn rrn);
avl AVLmax(avl r);
avl AVLmin(avl r);
avl balancing_left(avl r, int *decreased_height);
avl balancing_right(avl r, int *decreased_height);
avl search_remove(avl r, avl node_key, int *decreased_height);
avl removeAVL(avl r, key id, int *decreased_height);
avl remove(avl r, key id);

