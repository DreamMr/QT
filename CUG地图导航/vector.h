
#ifndef VECTOR_H
#define VECTOR_H


template<class T>
struct LinkNode
{
    LinkNode<T> *next;
     T ver;
     LinkNode<T>(T v, LinkNode<T> *cur = NULL) { ver=v; next = cur; }
};
template<class T>
class Vector
{
    LinkNode<T> *first;
    int size_v;
public:
    Vector() { size_v = 0; first =new LinkNode<T>(NULL); }
    ~Vector()
    {
        LinkNode<T> *cur=first->next;
        LinkNode<T> *del=first;
        while(cur)
        {
            delete del;
            del=cur;
            cur=cur->next;
        }
        delete del;
    }
    T operator[](int x);
    bool push_back(T x);
    bool isEmpty() {
        if (size_v) { return false; }
        else
        {
            return true;
        }
    }
    int size() { return size_v; }
};
template<class T>
bool Vector<T>::push_back(T x)
{
    LinkNode<T> *cur = first->next;
    LinkNode<T> *pre = first;
    while (cur != NULL)
    {
        pre = cur;
        cur = cur->next;
    }

    if (cur = new LinkNode<T>(x))
    {
        pre->next = cur;
        size_v++;
        return true;
    }
    else
        return false;
}
template<class T>
T Vector<T>::operator[](int x)
{
    if (x < size_v)
    {
        LinkNode<T> *cur = first->next;
        for (int i = 0; i < x; i++)
            cur = cur->next;
        return cur->ver;
    }
}

#endif // VECTOR_H
