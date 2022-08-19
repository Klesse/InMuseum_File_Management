#include "ABBB.h"


void loadFromFile(ABBB *arvore)
{
    ifstream file;

    file.open("file", ios::in | ios::binary);
    if (!file){
        cout << "Error opening the file\n";
        return;
    }

    item readItem;

    while(file.read((char *)&readItem,sizeof(item)))
    {
        arvore->root = arvore->insert(arvore->root,readItem.id,readItem.rrn);
    }

    file.close();
}

void insertFIle(ABBB *arvore, item data)
{
  ofstream file;

  file.open("file", ios::out | ios::binary);

  if(!file){
    cout << "Error opening the file\n";
    return;
  }

  arvore->root = arvore->insert(arvore->root,data.id,data.rrn);  //insert on ABBB
  file.write((char *)&data,sizeof(item)); //insert on file
}



int main(){
    ABBB *arvore = new ABBB();
    cout<<"Inserindo elementos:"<<endl;
    arvore->root = arvore->insert(arvore->root,0,1);
    arvore->root = arvore->insert(arvore->root,1,1);
    arvore->root = arvore->insert(arvore->root,2,1);
    arvore->root = arvore->insert(arvore->root,3,1);
    arvore->root = arvore->insert(arvore->root,4,1);
    arvore->root = arvore->insert(arvore->root,5,1);
    arvore->root = arvore->insert(arvore->root,6,1);
    arvore->root = arvore->insert(arvore->root,7,1);
    arvore->root = arvore->insert(arvore->root,8,1);
	arvore->root = arvore->insert(arvore->root,9,1);
    arvore->printInorder(arvore->root);
    cout<<endl;
    cout<<"Removendo..."<<endl;
    arvore->root = arvore->deleteNode(arvore->root,3);
    arvore->printInorder(arvore->root);
		cout<<"\nRAIZ:"<<arvore->root->id<<endl;
		cout<<arvore->root->left->id<<arvore->root->right->id<<endl;
    return 0;
}