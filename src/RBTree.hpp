#pragma once
#include <iostream>
/* 
Esse codigo foi baseado no livro do cormen 
Foram testados varios tipos de implemetacoes 
A menos complexa, e de melhor manutencao se baseia no fato que cada
folha e qualquer outro node que aponte para NULL(nullptr) na realidade
aponte para um ponto na memoria que seja do mesmo tipo do node,com cor preta

*/

enum color_t{BLACK,RED};
enum show_t{INORDER,PREORDER,POSORDER,PLOT};

struct NODE
{
    int key;
    NODE* parent = nullptr;
    NODE* left = nullptr;
    NODE* right = nullptr;
    color_t color = RED;
    NODE()=default;
    NODE(color_t color):color(color){}//Nodenil
    NODE(color_t color,NODE* parent):color(color),parent(parent){}
    NODE(int data,NODE* left=nullptr,NODE* right=nullptr,NODE *parent=nullptr):
    key(data),parent(parent),left(left),right(right){}
};



/* Class Definition */
class RBTree
{
    private:
        NODE *root;
        NODE *Tnil;
        void NDReplace(NODE* x,NODE* y);
        void PlotRecurse(NODE* node,std::string separator,bool last);
        NODE* TreeMinimum(NODE* node);
        NODE* TreeMaximum(NODE* node);
        void RotateRight(NODE* x);
        void RotateLeft(NODE* x);
        void InsertRepairTree(NODE* pNode);
        void DeleteRepairTree(NODE* x);
        void fixDelete(NODE* x);
        void preOrder(NODE* n);
        void posOrder(NODE* n);
        void inOrder(NODE* n);
        void eraseTree(NODE* n);
        void  plot() noexcept;
    public:

        void show(const show_t show = PLOT)  noexcept;
        void insert(const int key)  noexcept;
        void erase(const int key);
        NODE* search(const int key)const noexcept;
        RBTree();
        RBTree(std::initializer_list<int> list);
        RBTree(RBTree &obj) = delete;
        RBTree(RBTree &&obj) = delete;
        RBTree operator=(RBTree &obj) = delete;
        RBTree operator=(RBTree &&obj) = delete;
        ~RBTree();
};


