#include <iostream>


using namespace std;


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
void exibeElementos(avl r);

node *NewNode(key id, rrn rrn){
    node *New;
    New = (node *)malloc(sizeof(node));
    New->bal = 0;
    New->id = id;
    New->rrn = rrn;
    New->left = NULL;
    New->right = NULL;
    New->root = NULL;
    return New;
}

avl rotationRight(avl r){
    node *aux;
    aux = r->left;
    r->left = aux->right;
    if (aux->right != NULL) aux->right->root = r;
    aux->right = r;
    r->root = aux;
    return aux;
}

avl rotationLeft(avl r){
    node *aux;
    aux = r->right;
    r->right = aux->left;
    if (aux->left != NULL) aux->left->root = r;
    aux->left = r;
    r->root = aux;
    return aux;
}

avl insertAVL(node *r, node *novo, int *increased_height){
    if (r == NULL){ 
        novo->root = NULL; 
        *increased_height = 1;
        return novo;
    }
    if (novo->id <= r->id){ 
        r->left = insertAVL(r->left,novo,increased_height);
        r->left->root = r;
        if (*increased_height == 1){ 
            if (r->bal == +1){ 
                r->bal = 0;
                *increased_height = 0;
            }
            else if (r->bal == 0){ 
                r->bal = -1;
                *increased_height = 1;
            }
            else if (r->bal == -1){ 
                if (r->left->bal == -1){ 
                    r = rotationRight(r); 
                    r->right->bal = 0;
                }
                else{ 
                    r->left = rotationLeft(r->left);
                    r = rotationRight(r);
                    if (r->bal == 0){ 
                        r->left->bal = 0;
                        r->right->bal = 0;
                    }
                    else if (r->bal == -1){ 
                        r->left->bal = 0;
                        r->right->bal = +1;
                    }
                    else{ 
                        r->left->bal = -1;
                        r->right->bal = 0;
                    }
                }
                r->bal = 0;
                *increased_height = 0;
            }
        }
    }
    else{
        r->right = insertAVL(r->right, novo, increased_height);
        r->right->root = r;
        if (*increased_height == 1){ 
            if (r->bal == -1){ 
                r->bal = 0;
                *increased_height = 0;
            }
            else if (r->bal == 0){ 
                r->bal = 1; 
                *increased_height = 1;
            }
            
            else if (r->bal == 1){ 
                if (r->right->bal == 1){ 
                    r = rotationLeft(r);
                    r->left->bal = 0;
                }
                else{ 
                    r->right = rotationRight(r->right);
                    r = rotationLeft(r);
                    if (r->bal == 0){ 
                        r->left->bal = 0;
                        r->right->bal = 0;
                    }
                    else if (r->bal == -1){ 
                        r->left->bal = 0;
                        r->right->bal = 1;
                    }
                    else{ 
                        r->left->bal = -1;
                        r->right->bal = 0;
                    }
                }
                r->bal = 0;
                *increased_height = 0;
            }
        }
    }
    return r;
}


avl insert(avl r, key id, rrn rrn){
    int increased_height;
    node *New = NewNode(id,rrn);
    return insertAVL(r, New, &increased_height);
}

avl AVLmax(avl r){
    if(r->right == NULL) return r;
    return AVLmax(r);
}

avl AVLmin(avl r){
    if (r == NULL) return r;
    return AVLmin(r->left);
}

avl balancing_left(avl r, int *decreased_height){
    if (r->bal == -1){ 
        r->bal = 0;
        r->left->bal = 0;
    }
    else if (r->bal == 0){
        r->bal = 1;
        *decreased_height = 0;
    }
    else{ 
        if (r->right->bal >= 0){
            r = rotationLeft(r);
            if (r->bal == 0){
                r->left->bal = 1;
                r->bal = -1;
                *decreased_height = 0;
            }
            else{ 
                r->left->bal = 0;
                r->bal = 0;
            }
        }
        else{
            r->right = rotationRight(r);
            r = rotationLeft(r);
            if (r->bal == -1){
                r->left->bal = 0;
                r->right->bal = 1; 
            }
            else if (r->bal == 1){
                r->left->bal = -1;
                r->right->bal = 0;
            }
            else{
                r->left->bal = 0;
                r->right->bal = 0;
            }
            r->bal = 0;
        }
    }
    return r;
}


avl balancing_right(avl r, int *decreased_height){
    if (r->bal == 1){ 
        r->bal = 0;
        r->left->bal = 0;
    }
    else if (r->bal == 0){
        r->bal = -1;
        *decreased_height = 0;
    }
    else{ 
        if (r->left->bal <= 0){
            r = rotationRight(r);
            if (r->bal == 0){
                r->right->bal = -1;
                r->bal = 1;
                *decreased_height = 0;
            }
            else{ 
                r->right->bal = 0;
                r->bal = 0;
            }
        }
        
        else{
            r->left = rotationLeft(r);
            r = rotationRight(r);
            if (r->bal == -1){
                r->left->bal = 0;
                r->right->bal = 1; 
            }
            else if (r->bal == 1){
                r->left->bal = 0;
                r->right->bal = 1;;
            }
            else{
                r->left->bal = 0;
                r->right->bal = 0;
            }
            r->bal = 0;
        }
    }
    return r;
}


avl search_remove(avl r, avl node_key, int *decreased_height){
    node *aux;
    if (r->right != NULL){
        r->right = search_remove(r, node_key, decreased_height);
        if (*decreased_height == 1){
            r = balancing_right(r, decreased_height);
        }
    }
    else{
        node_key->id = r->id;
        aux = r;
        r = r->left;
        free(aux);
        *decreased_height = 1;
    }
    return r;
}

avl removeAVL(avl r, key id, int *decreased_height){
    node *aux = NULL;
    if (r == NULL){ 
        *decreased_height = 0;
    }
    else if(id < r->id){ 
        r->left = removeAVL(r->left, id, decreased_height);
        if (*decreased_height == 1){
            r = balancing_left(r, decreased_height);
        }
    }
    else if(id > r->id){
        r->right = removeAVL(r->right, id, decreased_height);
        if (*decreased_height == 1){
            r = balancing_right(r, decreased_height);
        }
    }
    else{
        if (r->right == NULL){ 
            aux = r;
            r = r->left;
            free(aux);
            *decreased_height = 1;
        }
        else if (r->left == NULL){ 
            aux = r;
            r = r->right;
            free(aux);
            *decreased_height = 1;
        }
        
        else{
            r->left = search_remove(r->left, r, decreased_height);
            if (*decreased_height == 1){
                r = balancing_left(r, decreased_height);
            }
        }
    }
    return r;
}

avl remove(avl r, key id){
    int decreased_height = 0;
    node *removed = removeAVL(r, id, &decreased_height);
    return removed;
}

void exibeElementos(avl r){
    if (r != NULL){
        exibeElementos(r->right);
        cout<< "%d ->"<< r->id<<endl;
        exibeElementos(r->left);
    }
}

int main(int argc, char const *argv[]){
    avl r = NULL;
    cout<<"Inserindo elementos:"<<endl;
    for (int i = 0; i < 10; i++){
        r = insert(r, i, i);
    }
    exibeElementos(r);
    cout<<endl;
    cout<<"Removendo..."<<endl;
    r = remove(r, 1);
    exibeElementos(r);
    return 0;
}
