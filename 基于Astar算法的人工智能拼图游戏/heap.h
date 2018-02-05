#ifndef HEAP_H
#define HEAP_H
#include<QVector>
#include"a_Node.h"
using namespace std;
//***********用于进行代价的排序
class Heap
{
public:
    Heap() {  v.push_back(NULL); }
    ~Heap(){v.clear();}
    bool insert(A_node *tmp);
    A_node* top() { if(v.size()>1)return v[1]; }
    int size() { return v.size()-1; }
    void pop();
    bool empty() {
        if (v.size() > 1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
private:
    QVector<A_node *>v;

};
void Heap::pop()
{
    A_node *tmp = v[v.size()-1];
    v.pop_back();
    int cur = 1;
    int child = 2;
    while (child<v.size())
    {
        if (child<v.size()-1 && v[child]->f>v[child + 1]->f)
        {
            child++;
        }

        if (tmp->f <= v[child]->f)
        {
            break;
        }
        v[cur] = v[child];
        cur = child;
        child = child * 2;
    }
    if(v.size()>1)
    v[cur] = tmp;
}
bool Heap::insert(A_node *tmp)
{

    v.push_back(tmp);

    int cur = v.size()-1;
    while(cur!=1 && v[cur/2]->f>v[cur]->f)
    {
        A_node *tmp = v[cur / 2];
        v[cur / 2] = v[cur];
        v[cur] = tmp;
        cur = cur / 2;
    }
    return true;
}

#endif // HEAP_H
