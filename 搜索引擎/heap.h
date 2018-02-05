#ifndef HEAP_H
#define HEAP_H
#include<vector>
using namespace std;
//***********大根堆*****
//使用时需要重载= ，<
//用途：进行网页可信度之间的排序
template<class T>
class Heap
{
public:
    Heap();
    bool empty(){return v.empty();}
    T& top(){
        if(!v.empty())
        return v[0];
    }
    void pop();
    void insert(T value);
    void clear(){v.clear();}
    size_t size(){return v.size();}
    ~Heap()
    {
        clear();
    }
private:
    vector<T>v;
};

template<class T>
Heap<T>::Heap()
{
    clear();
}
//*******弹出首元素*****
template<class T>
void Heap<T>::pop()
{
    if(v.size())
    {
        T end=v[v.size()-1];//取出最后一个元素
        v.pop_back();
        int cur=0,child=1;
        while(child<v.size())
        {
            if(child<v.size()-1 && v[child]<v[child+1])//比较左右孩子哪个更大
                child++;
            if(end<v[child])//如果最后一个元素小于最大的孩子节点，则将最大的孩子节点上移
            {
                v[cur]=v[child];
                cur=child;
                child=child*2+1;
            }
            else//否则跳出，说明找到了最后一个元素适合的位置
                break;
        }
        if(!v.empty())
            v[cur]=end;
        else
            v.push_back(end);
    }
}
//********插入*****************
template<class T>
void Heap<T>::insert(T value)
{
    v.push_back(value);//将待插入元素放在数组末端
    int cur=v.size();
    while(cur!=1 && v[cur/2-1]<v[cur-1])//从最后一个元素开始沿着父亲节点向上查找，找到适合的位置
    {
        T tmp=v[cur/2-1];
        v[cur/2-1]=v[cur-1];
        v[cur-1]=tmp;
        cur=cur/2;
    }
}

#endif // HEAP_H
