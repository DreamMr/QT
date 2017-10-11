#ifndef CHAIN_H
#define CHAIN_H

#include"chainnode.h"
template <class T>
class chain
{
private:
    chainnode<T> *first;
    chainnode<T> *last;
    //bool checkindex(int i);
    //int length;
public:
    chain();
    void addfirst(T x);
    T getheadvalue();
    void delhead();
    void addtail(T x);
};
template<class T>
void chain<T>::addtail(T x)
{
    chainnode<T> *node=new chainnode<T>(x);
    last->next=node;
    last=node;
}

template<class T>
void chain<T>::delhead()
{
    chainnode<T> *node = first->next->next;
    delete first->next;
    first->next = node;
    //length--;
}
template <class T>
T chain<T>::getheadvalue()
{
    return first->next->data;
}
template<class T>
chain<T>::chain()
{

    first = new chainnode<T>;
    last=first;
    //length = 0;
}
template<class T>
void chain<T>::addfirst(T x)
{
    chainnode<T> *node = new chainnode<T>(x, first->next);
    first->next = node;
    //length++;
}
#endif // CHAIN_H
