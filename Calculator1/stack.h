#ifndef STACK_H
#define STACK_H

#include"chain.h"
template<class T>
class Stack
{
    chain<T> list;
    bool checktop();
    int length;
public:
    Stack();
    void push(T x);
    void pop();
    bool empty();
    T top();
};
template<class T>
bool Stack<T>::empty()
{
    return checktop();
}

template<class T>
bool Stack<T>::checktop()
{
    if (length)
    {
        return true;
    }
    else
    {
        return false;
    }
}
template<class T>
Stack<T>::Stack()
{
    length = 0;
}
template<class T>
void Stack<T>::push(T x)
{
    list.addfirst(x);
    length++;
}
template<class T>
void Stack<T>::pop()
{
    if (checktop())
    {
        list.delhead();
        length--;
    }
    else
    {
        //cout << "No value in Stack" << endl;
    }
}
template<class T>
T Stack<T>::top()
{
    if (checktop())
    {
        return list.getheadvalue();
    }
    else
    {
        //cout << "No value in Stack" << endl;
        return -1;
    }
}

#endif // STACK_H
