#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H
template<class T>
class  BinaryTreeNode
{
public:
    BinaryTreeNode<T> *LeftChild;
    BinaryTreeNode<T> *RightChild;
    T data;
    BinaryTreeNode(T d=0, BinaryTreeNode<T> *l = NULL, BinaryTreeNode<T> *r = NULL) { data = d; LeftChild = l; RightChild = r; }
};


#endif // BINARYTREENODE_H
