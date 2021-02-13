#include "RBTree.hpp"

void InOrder(NODE* n){
    if (n == nullptr) return;
    InOrder(n->left);
    if(n->key!=0)
        std::cout<<n->key<<" ("<<(n->color == color_t::BLACK ? "BLACK" : "RED")<<") / ";
    InOrder(n->right);
    
}
void PreOrder(NODE* n){
    if (n == nullptr) return;
    std::cout<<n->key<<" ";
    PreOrder(n->left);
    PreOrder(n->right);
}
void PosOrder(NODE* n){
    if (n == nullptr) return;
    PosOrder(n->left);
    PosOrder(n->right);
    std::cout<<n->key<<" ";
}

void NDReplace(NODE* root,NODE* x,NODE* y){
    if (x->parent == nullptr)
        root = y;
    else if(x==x->parent->left)  
        x->parent->left = y;
    else
        x->parent->right = y;
    y->parent = x->parent;
}


/*                          Class Implementation                    */

NODE* RBTree::TreeMinimum(NODE* node){
    while (node->left !=Tnil)
        node = node->left;
    return node;
    
}
NODE* RBTree::TreeMaximum(NODE* node){
    while (node->right != Tnil)
        node = node->right;
    return node;
}

void RBTree::RotateLeft(NODE* x){ // Voltar pro meu proprio rotate
    NODE* y = x->right;
		x->right = y->left;
		if (y->left != Tnil) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			(*this->root) = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
}

void RBTree::RotateRight(NODE* x){
    NODE* y = x->left;
		x->left = y->right;
		if (y->right != Tnil) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			(*this->root) = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
}


void RBTree::InsertRepairTree(NODE* pNode){
    NODE* pAux;
    while (pNode->parent->color == RED)
    {
        if(pNode->parent == pNode->parent->parent->right){
            pAux = pNode->parent->parent->left; // uncle
            if(pAux->color == RED){
                pAux->color = BLACK;
                pNode->parent->color = BLACK;
                pNode->parent->parent->color=RED;
                pNode = pNode->parent->parent;
            }else{
                if(pNode==pNode->parent->left){
                    pNode = pNode->parent;
                    RotateRight(pNode);
                }
                pNode->parent->color = BLACK;
                pNode->parent->parent->color = RED;
                RotateLeft(pNode->parent->parent);
            }
        }else{
            pAux = pNode->parent->parent->right;
            if(pAux->color == RED){
                pAux->color = BLACK;
                pNode->parent->color = BLACK;
                pNode->parent->parent->color = RED;
                pNode = pNode->parent->parent;
            }else{
                if(pNode ==  pNode->parent->right){
                    pNode = pNode->parent;
                    RotateLeft(pNode);
                }
                pNode->parent->color = BLACK;
                pNode->parent->parent->color = RED;
                RotateRight(pNode->parent->parent);

            }

        }
        if(pNode == *root)
            break;
    }
    (*this->root)->color = BLACK; 
}
void RBTree::DeleteRepairTree(NODE* pNode){
    NODE* pAux;
    while (pNode != *root && pNode->color == BLACK)
    {
        if(pNode == pNode->parent->left){
            pAux = pNode->parent->right;
            if (pAux->color==RED)//Case 3.1
            {
                pAux->color = BLACK;
                pNode->parent->color = RED;
                RotateLeft(pNode->parent);
                pAux = pNode->parent->right;
            }
            if(pAux->left->color == BLACK && pAux->right->color == BLACK){//case 3.2
                pAux->color = RED;
                pNode = pNode->parent;
            }else{
                if (pAux->right->color == BLACK)//case 3.3
                {
                    pAux->left->color = BLACK;
                    pAux->color = RED;
                    RotateRight(pAux);
                    pAux = pNode->parent->right;
                }
                //case 3.4
                pAux->color = pNode->parent->color;
                pNode->parent->color = BLACK;
                pAux->right->color = BLACK; 
                RotateLeft(pAux->parent);
                pNode = *root;
            }
            
        }else{
            pAux = pNode->parent->left;
            if(pAux->color == RED){ // case 3.1
                pAux->color = BLACK;
                pNode->parent->color = RED;
                RotateRight(pNode->parent);
                pAux = pNode->parent->left;
            }
            if (pAux->right->color == BLACK && pAux->left->color == BLACK)//case 3.2
            {
                pAux->color = RED;
                pNode = pNode->parent;
            }else{
                if(pAux->left->color == BLACK){//case 3.3
                    pAux->right->color = BLACK;
                    pAux->color = RED;
                    RotateLeft(pAux);
                    pAux = pNode->parent->left;
                }
                //case 3.4
                pNode->color = pNode->parent->color;
                pNode->parent->color = BLACK;
                pAux->left->color = BLACK;
                RotateRight(pNode->parent);
                pNode = *root;
            }
        }
    }
    pNode->color = BLACK; 
    
}
NODE* RBTree::search(const int key)const noexcept{
    NODE *pNode = *root;
    while (pNode != Tnil && pNode->key != key)
        if(key > pNode->key) pNode = pNode->right;
        else pNode = pNode->left;
    return pNode;
    
}



void RBTree::insert(const int key) noexcept{
    NODE* pNode = new NODE(key,Tnil,Tnil);// left = right = Null 
    NODE* pParent = nullptr;
    NODE* pSentinel = *this->root;
    
    while (pSentinel != Tnil)
    {
        pParent = pSentinel; // Ao final do loop pParent sera o parente de pNode
        if(pNode->key  > pSentinel->key)
            pSentinel = pSentinel->right;
        else 
            pSentinel = pSentinel->left;
    }
    pNode->parent= pParent;
    if (pParent == nullptr )
    {
        /*Caso seja o primeiro item,sera preto e nao precisara fazer nada*/
        *this->root = pNode;
        pNode->color = BLACK;
        return;
    }else{
        if(pNode->key > pParent->key)
            pParent->right = pNode;
        else 
            pParent->left = pNode;
    }

    if(pNode->parent->parent == nullptr){ // Testar se pode tirar isso
        return;
    }

    
    InsertRepairTree(pNode);
}





















void RBTree::erase(const int key) {
    NODE* z = this->search(key);
    if(z==Tnil || z==nullptr) {
        throw "Couldn`t find key in the tree";
        return;
    }
    NODE* y = z;
    NODE* x;
    color_t y_original_color = y->color;
    if(z->left == Tnil){
        x = z->right;
        NDReplace(*root,z,z->right);
    }else if(z->right == Tnil){
        x=z->left;
        NDReplace(*root,z,z->left);
    }else{
        y = TreeMinimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if(y->parent == z){
            x->parent = y;
        }else{
            NDReplace(*root,y,y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        NDReplace(*root,z,y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    z = nullptr;
    if(y_original_color == BLACK)
        // fixDelete(x);
        DeleteRepairTree(x);

}
RBTree::RBTree(){
    root = new NODE*();
    Tnil = new NODE(BLACK);
    *root = Tnil;
}
RBTree::~RBTree(){

    delete []root;
    root = nullptr;
    delete Tnil;
    Tnil = nullptr;
}

RBTree::RBTree(std::initializer_list<int> list):RBTree(){
    for (auto &&i : list)
        this->insert(i);
}