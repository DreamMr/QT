#ifndef HEAP_H
#define HEAP_H

template<class T>
class MinHeap
{
    int size;
    int length;
    T *heap;

public:
    MinHeap(T *a, int s);
    void push(T element);
    void pop();
    T top();
    int GetSize() { return length; }
    bool isEmpty();
};
template<class T>
T MinHeap<T>::top()
{
    return heap[1];
}
template<class T>
void MinHeap<T>::pop()
{
    if (isEmpty()) { return; }
    int cur = 1, child = 2;
    T element = heap[length--];
    while (child<=length)
    {
        if (child<length && heap[child] > heap[child + 1]) { child++; }
        if (heap[child] < element)
        {
            heap[child / 2] = heap[child];
            child = child * 2;
        }
        else
        {
            break;
        }
    }
    heap[child / 2] = element;
    return;
}
template<class T>
void MinHeap<T>::push(T element)
{
    int cur = ++length;
    while (cur!=1 && heap[cur/2]>element)
    {
        heap[cur] = heap[cur / 2];
        cur = cur / 2;
    }
    heap[cur] = element;
}
template<class T>
MinHeap<T>::MinHeap(T *a, int s)
{
    size = s + 11;
    heap = new T[size];
    length = s;
    for (int i = 0; i < s; i++)
        heap[i + 1] = a[i];
    int cur = length / 2;
    while (cur>=1)
    {
        int child = cur * 2;
        while (child<=length)
        {
            if (child<length && heap[child]>heap[child + 1])
                child++;
            if (heap[child/2] > heap[child])
            {
                T tmp = heap[child];
                heap[child] = heap[child/2];
                heap[child/2] = tmp;
                child = child * 2;
            }
            else
            {
                break;
            }
        }
        cur--;
    }
}
template<class T>
bool MinHeap<T>::isEmpty()
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

#endif // HEAP_H
