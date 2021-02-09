#include "RBTree.hpp"

NODE* GetParent(NODE* n){
    return n == nullptr ? nullptr : n->parent;
}
NODE* GetGrandParent(NODE* n){
    return GetParent(GetParent(n));
}
NODE* GetSibling(NODE* n){
    NODE* p = GetParent(n);
    if (p == nullptr) return nullptr;
    return (n==p->left ? p->right : p->left);
}
NODE* GetUncle(NODE* n){
    NODE * p = GetParent(n);
    return GetSibling(p);
}
void RotateLeft(NODE* n){
    NODE * nnew = n->right;
    NODE* p = GetParent(n);
    if(nnew == nullptr) return ;


    n->right = nnew->left;
    nnew->left = n;
    n->parent=nnew;

    if (n->right) n->right->parent = n;

    if(p != nullptr){
        if(n==p->left) p->left=nnew;
        else if(n== p->right) p->right = nnew;
    }

    nnew->parent = p;
}

void RotateRight(NODE* n){
    NODE* nnew = n->left;
    NODE* p = GetParent(n);
    if(!nnew) return;

    n->left = nnew->right;
    nnew->right = n;
    n->parent = nnew;

    if (n->left)   n->left->parent = n;

    if (p != nullptr){ 
        if (n == p->left)  p->left = nnew;
        else if (n == p->right)  p->right = nnew;
    }

    nnew->parent = p;
}

#include <string>
void InsertRecurse(NODE* root,NODE* n){
     if (root != nullptr)
    {
        if (n->key < root->key) {
            if (root->left != nullptr) {
                InsertRecurse(root->left, n);
                return;
            } else {
                root->left = n;
            }
        } else { // n->key >= root->key
            if (root->right != nullptr) {
                InsertRecurse(root->right, n);
                return;
            } else {
                root->right = n;
            }
        }
    }
    n->parent = root;
    n->left = nullptr;
    n->right = nullptr;
    
}

void InsertRepairTree(NODE* n){
    if (GetParent(n) == nullptr) {
        InsertCase1(n);
    } else if (GetParent(n)->color == BLACK) {
        InsertCase2(n);
    } else if (GetUncle(n) != nullptr && GetUncle(n)->color == RED) {
        InsertCase3(n);
    } else {
        InsertCase4(n);
    }
}

void InsertCase1(NODE* n){
    n->color=BLACK;
}
void InsertCase2(NODE* n){
    return;
}
void InsertCase3(NODE* n){
    GetParent(n)->color = BLACK;
    GetUncle(n)->color = BLACK;
    GetGrandParent(n)->color = RED;
    InsertRepairTree(GetGrandParent(n));
}
void InsertCase4(NODE* n){
    NODE* tParent = GetParent(n);
    NODE* tGrandParent = GetGrandParent(n);
    if (n == tParent->right && tParent == tGrandParent->left)
    {
        RotateLeft(tParent);
        n=n->left;
    }else if(n==tParent->left && tParent == tGrandParent->right){
        RotateRight(tParent);
        n=n->right;
    }
    InsertCase4Step2(n);

}
void InsertCase4Step2(NODE* n){
    NODE* tParent = GetParent(n);
    NODE* tGrandParent = GetGrandParent(n);
    if (n==tParent->left) RotateRight(tGrandParent);
    else RotateLeft(tGrandParent);
    tParent->color = BLACK;
    tGrandParent->color = RED;
}
/*==========================================Print========================================*/

 
void InOrder(NODE* n){
    if (n == nullptr) return;
    InOrder(n->left);
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
/*==========================================Print========================================*/



/*==========================================Deleting========================================*/


/*==========================================Deleting========================================*/
/*                                          Class Manipulation                              */
void RBTree::insert(const int key){
    if (!root) root = new NODE*();

    NODE* newNode = new NODE(key);

    InsertRecurse(*this->root,newNode);
    
    InsertRepairTree(newNode);

    *root = newNode;

    while (GetParent(*this->root) != nullptr) *this->root=GetParent(*this->root);
  
}
void RBTree::remove(const int key){
   
}
NODE* RBTree::search(const int key)const noexcept{
    NODE* pNode = *root;
    while (pNode->key != key && pNode != nullptr)
    {
        pNode = (key > pNode->key ? pNode->right : pNode->left);
    }
    return pNode;
}

void RBTree::show(enum show_t show=IN)const noexcept{
    switch (show)
    {
        case PRE:
            PreOrder(*this->root);
        break;
        case POS:
            PosOrder(*this->root);
        break;
        case IN:
        default:
            InOrder(*this->root);
    }
}
NODE *RBTree::rootNode()const{
    return *root;
}

RBTree::RBTree(): root(nullptr){}
RBTree::~RBTree(){
}