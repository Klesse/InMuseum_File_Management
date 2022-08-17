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
    if (r == NULL){ //Caso 1: subárvore era vazia
        novo->root = NULL; //Irrelevante (não precisava)
        *increased_height = 1;
        return novo;
    }
    if (novo->id <= r->id){ //desce à esquerda
        r->left = insertAVL(r->left,novo,increased_height);
        r->left->root = r;
        if (*increased_height == 1){ //altura da subárvore esquerda aumentou após a inserção
            if (r->bal == +1){ //Caso 2: inseriu do lado mais baixo (ARVORE FICA BALANCEADA)
                r->bal = 0;
                *increased_height = 0;
            }
            else if (r->bal == 0){ //Caso 3 dois lados tinham a mesma altura
                r->bal = -1;
                *increased_height = 1;
            }
            else if (r->bal == -1){ // Caso 4: inseriu do lado mais alto
                if (r->left->bal == -1){ //Caso 4.1: inseriu à esquerda do filho direito
                    r = rotationRight(r); //Rotacao a direita entre o x e o filho esquerdo, faz descer o C e subir o A;
                    r->right->bal = 0;
                }
                else{ //Caso 4.2: inseriu à direita do filho esquerdo
                    r->left = rotationLeft(r->left);
                    r = rotationRight(r);
                    if (r->bal == 0){ // z foi o nó inserido
                        r->left->bal = 0;
                        r->right->bal = 0;
                    }
                    else if (r->bal == -1){ //inserção à esquerda de z
                        r->left->bal = 0;
                        r->right->bal = +1;
                    }
                    else{ //r->bal == +1 (inserção a direita de z)
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
        if (*increased_height == 1){ //altura da subárvore direita aumentou após a inserção
            if (r->bal == -1){ //Caso 2: inseriu do lado mais baixo (filho direito da subarvore direita)(ARVORE FICA BALANCEADA)  //OK
                r->bal = 0;
                *increased_height = 0;
            }
            else if (r->bal == 0){ //Caso 3 dois lados tinham a mesma altura //Ok
                r->bal = 1; //inseri do lado direito, fat bal = 1;
                *increased_height = 1;
            }
            //alterar daqui pra baixo
            else if (r->bal == 1){ // Caso 4: inseriu do lado mais alto
                if (r->right->bal == 1){ //Caso 4.1: inseriu à direita do filho direito
                    r = rotationLeft(r);
                    r->left->bal = 0;
                }
                else{ //Caso 4.2: inseriu à esquerda do filho direito
                    r->right = rotationRight(r->right);
                    r = rotationLeft(r);
                    if (r->bal == 0){ //INSERIU O Z (VER NO PDF QUAL QUE É O Z)
                        r->left->bal = 0;
                        r->right->bal = 0;
                    }
                    else if (r->bal == -1){ 
                        r->left->bal = 0;
                        r->right->bal = 1;
                    }
                    else{ //r->bal == 1;
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
    if (r->bal == -1){ //estou removendo do lado esquerdo, isso implica  que o meu fator de balanceamento fica 0
        r->bal = 0;
        r->left->bal = 0;
    }
    else if (r->bal == 0){
        r->bal = 1;
        *decreased_height = 0;
    }
    else{ //altura foi altera e desbalanceou
    //em qual caso estou? (vou fazer rotação simples ou dupla?)
        if (r->right->bal >= 0){
            r = rotationLeft(r);
            if (r->bal == 0){
                r->left->bal = 1;
                r->bal = -1;
                *decreased_height = 0;
            }
            else{ //r->bal == 1;
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
    if (r->bal == 1){ //estou removendo do lado direito, isso implica  que o meu fator de balanceamento fica 0
        r->bal = 0;
        r->left->bal = 0;
    }
    else if (r->bal == 0){
        r->bal = -1;
        *decreased_height = 0;
    }
    else{ //altura foi altera e desbalanceou
    //em qual caso estou? (vou fazer rotação simples ou dupla?)
        if (r->left->bal <= 0){
            r = rotationRight(r);
            if (r->bal == 0){
                r->right->bal = -1;
                r->bal = 1;
                *decreased_height = 0;
            }
            else{ //r->bal == -1;
                r->right->bal = 0;
                r->bal = 0;
            }
        }
        //CASOS ROTAÇÃO DUPLA
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
    if (r == NULL){ //Ou a arvore ta vazia, ou em uma das recursões a gente chega em um ponteiro nulo->chave não encontrada;
        *decreased_height = 0;
    }
    else if(id < r->id){ //se a raiz for diferente de nulo e a chave que eu to buscando eh menor do que a chave do nó corrente, olhamos para a esquerda
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
    else{ //encontrei a chave que to procurando
        if (r->right == NULL){ //ou eh uma folha, ou eh um nóh que tem apenas um filho(filho esquerdo)
            aux = r;
            r = r->left;
            free(aux);
            *decreased_height = 1;
        }
        else if (r->left == NULL){ //ou eh uma folha, ou eh um nóh que tem apenas um filho (filho direito)
            aux = r;
            r = r->right;
            free(aux);
            *decreased_height = 1;
        }
        //tem dois filhos
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
