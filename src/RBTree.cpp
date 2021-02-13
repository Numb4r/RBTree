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

void RBTree::NDReplace(NODE* root,NODE* x,NODE* y){
    if (x->parent == Tnil )
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
			root = y;
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
			root = y;
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
        if(pNode == root)
            break;
    }
    root->color = BLACK; 
}

void RBTree::DeleteRepairTree(NODE* x){
    NODE* w;
    while (x != root && x->color == BLACK) 
    {
        if(x == x->parent->left){ // left
            w = x->parent->right;
            if (w->color==RED)//Case 1
            {
                w->color = BLACK;
                x->parent->color = RED;
                RotateLeft(x->parent);
                w = x->parent->right;
            }
            if(w->left->color == BLACK && w->right->color == BLACK){//case 2
                w->color = RED;
                x = x->parent;
            }else{
                if (w->right->color == BLACK)//case 3
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    RotateRight(w);
                    w = x->parent->right;
                }
                //case 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK; 
                RotateLeft(x->parent);
                x = root;
            }
            
        }else{//right
            w = x->parent->left;
            if(w->color == RED){ // case 1
                w->color = BLACK;
                x->parent->color = RED;
                RotateRight(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK)//case 2
            {
                w->color = RED;
                x = x->parent;
            }else{
                if(w->left->color == BLACK){//case 3
                    w->right->color = BLACK;
                    w->color = RED;
                    RotateLeft(w);
                    w = x->parent->left;
                }
                //case 4
                x->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RotateRight(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK; 
    
}
NODE* RBTree::search(const int key)const noexcept{
    NODE *pNode = root;
    while (pNode != Tnil && pNode->key != key)
        if(key > pNode->key) pNode = pNode->right;
        else pNode = pNode->left;
    return pNode;
    
}
void RBTree::PlotRecurse(NODE* node,std::string separator,bool last)  {
    if(node != Tnil){
        std::cout<< separator;
        if(last){
            std::cout<<"R----";
            separator+="     ";
        }else{
            std::cout<<"L----";
            separator+="|    ";
        }
        std::cout
            <<node->key
            <<"("<<(node->color ? "RED" : "BLACK") <<")"<<std::endl;

        PlotRecurse(node->left,separator,false);
        PlotRecurse(node->right,separator,true);
    }
}

void RBTree::plot() {
    PlotRecurse(root,"",false);


}


void RBTree::insert(const int key) noexcept{
    NODE* pNode = new NODE(key,Tnil,Tnil);// left = right = Null 
    NODE* pParent = nullptr;
    NODE* pSentinel = root;
    
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
        root = pNode;
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
    if(z == Tnil) {
        throw "Couldn`t find key in the tree";
        return;
    }
    NODE* y = z;
    NODE* x;
    color_t y_original_color = y->color;
    if(z->left == Tnil){
        std::cout<<"filho a esquerda nil\n";
        x = z->right;
        NDReplace(root,z,z->right);
    }else if(z->right == Tnil){
        std::cout<<"filho a direita nil\n";

        x=z->left;
        NDReplace(root,z,z->left);
    }else{
        std::cout<<"nenhum filho nil\n";

        y = TreeMinimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if(y->parent == z){
            x->parent = y;
        }else{
            NDReplace(root,y,y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        NDReplace(root,z,y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
        std::cout<<x->key<<std::endl;
    }
    delete z;
    z = nullptr;
    if(y_original_color == BLACK)
        // fixDelete(x);
        DeleteRepairTree(x);

}
RBTree::RBTree(){
    Tnil = new NODE(BLACK);
    root = Tnil;
}
RBTree::~RBTree(){

    
    delete Tnil;
    Tnil = nullptr;
}

RBTree::RBTree(std::initializer_list<int> list):RBTree(){
    for (auto &&i : list)
        this->insert(i);
}