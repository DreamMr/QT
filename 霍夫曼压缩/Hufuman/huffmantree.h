#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include"binarytreenode.h"
template<class T>
class HuffmanTree
{
    BinaryTreeNode<T> *root;
    void destory(BinaryTreeNode<T> *cur);
public:
    HuffmanTree(BinaryTreeNode<T> *Left, BinaryTreeNode<T> *Right) { root = new BinaryTreeNode<T>(Left->data + Right->data, Left, Right);  }
    HuffmanTree() { root = NULL; }
    void Destory() { destory(root); }
    ~HuffmanTree()
    {

    }
    void setRoot(T a,T ch){ root = new BinaryTreeNode<T>(a); root->LeftChild = new BinaryTreeNode<T>(ch); }
    BinaryTreeNode<T>* GetRoot() { return root; }
    bool operator<(HuffmanTree &tree)
    {
        return root->data < tree.root->data;
    }
    bool operator>(HuffmanTree &tree) { return root->data > tree.root->data; }
    HuffmanTree& operator =(HuffmanTree &tree) {
        root = tree.root;
        return *this;
    }
};
template<class T>
void HuffmanTree<T>::destory(BinaryTreeNode<T> *cur)
{
    if (cur == NULL) { return; }
    destory(cur->LeftChild);
    destory(cur->RightChild);
    if (cur->LeftChild != NULL)
    {
        delete cur->LeftChild;
        cur->LeftChild = NULL;
    }
    if (cur->RightChild != NULL)
    {
        delete cur->RightChild;
        cur->RightChild = NULL;
    }
}
template<class T>
HuffmanTree<T>& setTree(HuffmanTree<T> left, HuffmanTree<T> right)
{
    HuffmanTree<T> *tree = new HuffmanTree<T>(left.GetRoot(), right.GetRoot());
    return *tree;
}

#endif // HUFFMANTREE_H
