#include <iostream>
#pragma once

enum color_t{BLACK,RED};
enum show_t{PRE,IN,POS};

struct NODE{
    int key;
    enum color_t color;
    NODE *left;
    NODE *right;
    NODE *parent;
    NODE(const int key):
        key(key),color(RED),
        left(nullptr),right(nullptr),parent(nullptr){}
};

NODE* GetParent(NODE* n);
NODE* GetGrandParent(NODE* n);
NODE* GetSibling(NODE* n);
NODE* GetUncle(NODE* n);
void RotateLeft(NODE* n);
void RotateRight(NODE* n);

void InsertRecurse(NODE* root,NODE* n);
void InsertRepairTree(NODE* n);
void InsertCase1(NODE* n);
void InsertCase2(NODE* n);
void InsertCase3(NODE* n);
void InsertCase4(NODE* n);
void InsertCase4Step2(NODE* n);

void InOrder(NODE* n);
void PreOrder(NODE* n);
void PosOrder(NODE* n);

void CleanTreeRecurse(NODE* n);

// void ReplaceNode(NODE* n,NODE* child);
// void DeleteOneChild(NODE* n);
// void DeleteCase1(NODE* n);
// void DeleteCase2(NODE* n);
// void DeleteCase3(NODE* n);
// void DeleteCase4(NODE* n);
// void DeleteCase5(NODE* n);
// void DeleteCase6(NODE* n);
class RBTree{
    private:
        NODE **root;
    public:
        void insert(const int key);
        void remove(const int key);
        void show(enum show_t show) const noexcept;
        NODE * search(const int key) const noexcept;
        NODE * rootNode() const;

        RBTree();
        ~RBTree();
};

