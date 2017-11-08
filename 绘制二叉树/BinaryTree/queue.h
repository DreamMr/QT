#ifndef QUEUE_H
#define QUEUE_H


template<class T>
class chainnode
{
public:
    chainnode *next;
    T data;
    chainnode(T x = NULL, chainnode *Next = 0) { data = x; next = Next; }
};
template <class T>
class chain
{
    chainnode<T> *first;
    chainnode<T> *last;
public:
    chain();
    T GetHead();
    T GetTail();
    bool AddTail(T x);
    bool DelHead();
};
template<class T>
bool chain<T>::DelHead()
{
    chainnode<T> *del = first->next;

    if (first->next == last)
        last = first;
    first->next = del->next;
    delete del;
    return true;
}
template<class T>
chain<T>::chain()
{
    first = new chainnode<T>;
    last = first;
}
template<class T>
T chain<T>::GetHead()
{
    return first->next->data;
}
template<class T>
T chain<T>::GetTail()
{
    return last->data;
}
template<class T>
bool chain<T>::AddTail(T x)
{
    if (chainnode<T> *newnode = new chainnode<T>(x))
    {
        last->next = newnode;
        last = newnode;
        return true;
    }
    else
    {
        return false;
    }
}
template<class T>
class Queue
{
    chain<T> list;
    int length;
public:
    bool push(T x);
    bool pop();
    T front();
    T tail();
    bool isEmpty();
    Queue();
};
template <class T>
bool Queue<T>::isEmpty()
{
    if (length)
    {
        return false;
    }
    else
    {
        return true;
    }
}

template<class T>
T Queue<T>::tail()
{
    if (!isEmpty())
    {
        return list.GetTail();
    }
    else
    {
        return NULL;
    }
}

template<class T>
T Queue<T>::front()
{
    if (!isEmpty())
    {
        return list.GetHead();
    }
    else
    {
        return NULL;
    }
}

template<class T>
bool Queue<T>::pop()
{
    if (!isEmpty())
    {
        list.DelHead();
        length--;
        return true;
    }
    else
    {
        return false;
    }
}

template<class T>
bool Queue<T>::push(T x)
{
    if (list.AddTail(x))
    {
        length++;
        return true;
    }
    else
    {
        return false;
    }
}
template<class T>
Queue<T>::Queue()
{
    length = 0;
}


#endif // QUEUE_H
