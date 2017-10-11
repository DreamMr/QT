#ifndef CHAINNODE_H
#define CHAINNODE_H

template<class T>
class chainnode
{
public:
    chainnode *next;
    T data;
    chainnode(T x = 0, chainnode *Next = 0) { data = x; next = Next; }
};
#endif // CHAINNODE_H
