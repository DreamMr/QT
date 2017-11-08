#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H

struct Point
{
    int x;
    int y;
    Point(int x1=0, int y1=0) { x = x1; y = y1; }
};
template <class T>
class BinaryTreeNode
{
public:
    T data;
    BinaryTreeNode<T>* LeftChild;
    BinaryTreeNode<T>* RightChild;
    int level;
    Point point;
    BinaryTreeNode(T Data, BinaryTreeNode<T> *left = NULL, BinaryTreeNode<T> *right = NULL, int l = 0) { data = Data; LeftChild = left; RightChild = right; level = l; }
};

#endif // BINARYTREENODE_H
