#ifndef QUEUE_H
#define QUEUE_H
#include"chain.h"
template<class T>
class queue
{
public:
    queue();
   // ~queue();
   T front();
   void push(T x);
   void pop();
  bool empty();
private:
    chain<T> list;
    //check();
    int length;
};
template<class T>
bool queue<T>::empty()
{
    if(length)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class T>
queue<T>::queue()
{
    length=0;
}
template<class T>
T queue<T>::front()
{
   if(empty())
   {
       return list.getheadvalue();
   }
   else
   {
       return 0;
   }
}
template<class T>
void queue<T>::pop()
{
    if(empty())
    {
        list.delhead();
        length--;
    }
}
template<class T>
void queue<T>::push(T x)
{
    list.addtail(x);
    length++;
}

#endif // QUEUE_H
