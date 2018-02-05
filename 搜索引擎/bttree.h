#ifndef BTTREE_H
#define BTTREE_H
#include<btnode.h>
#include"url_index.h"
#include<string>
//*******b树*********
/*个人感觉：b树这种数据结构的好处是可以快速的将大量数据存入磁盘，因为b树的每个节点都可以存放
 * 不止一个数据，在进行从内存到磁盘的写入数据时可以一次写入一页的大小，减少I/O的次数。但是
*当b树内的元素少于一个节点的容量时，查找的效率将不是对数级别，可能为线性O（n）
*/
template<class T>
class BTtree
{
public:
    BTtree();
    void insert(T value);
    BTnode<T>* Getroot() { return root; }
    T* find(T value) {//查找的接口
        T *re = isFind(root, value);
        if (re)
            return re;
        else
            return NULL;
    }
private:
    BTnode<T> *root;//根节点
    T* isFind(BTnode<T> *cur, T value);//查找元素
    void isInsert(BTnode<T> *cur, T value);//插入元素
    void spliter(BTnode<T> *cur);//当该节点满时将节点进行划分
};
//*********将满员了的节点进行划分
/*大体思路：新建一个节点，将旧节点划分为两部分，将右边的一半存入新节点，并将中间的元素上移，若该节点没有父亲节点，则新建根节点
 * 如果有父亲节点将中间元素插入到父亲节点的适合位置，新节点和当前的旧节点一起作为父亲节点的子节点
 */
template<class T>
void BTtree<T> ::spliter(BTnode<T> *cur)
{
    BTnode<T> *newNode = new BTnode<T>;//新建节点
    int i = 0;
    for (; i < cur->keyNum; i++)//将旧节点右边部分分给新节点
    {
        newNode->key[i] = cur->key[MAXKEY / 2 + i];//分配元素
        newNode->pchild[i] = cur->pchild[MAXKEY / 2 + i];//分配孩子节点
        if(newNode->pchild[i])
        newNode->pchild[i]->parent = newNode;//设置将孩子节点的父亲节点指向新建节点
        cur->pchild[MAXKEY / 2 + i] = NULL;
        newNode->keyNum++;//新建节点的元素个数+1
        cur->keyNum--;//旧节点的元素个数减一
    }
    cur->keyNum--;
    newNode->pchild[i] = cur->pchild[MAXKEY];//分配旧节点最右边的孩子指针
    if (newNode->pchild[i])
        newNode->pchild[i]->parent = newNode;
    cur->pchild[MAXKEY] = NULL;
    newNode->isleaf = cur->isleaf;
    T tmp = cur->key[MAXKEY / 2 - 1];
    if (cur->parent)//如果旧节点不是根节点，则将中间元素上移
    {
        int i = cur->parent->keyNum - 1;
        for (; i >= 0; i--)//查找适合中间元素的位置
        {
            if (tmp < cur->parent->key[i])
            {
                cur->parent->key[i + 1] = cur->parent->key[i];
                cur->parent->pchild[i + 2] = cur->parent->pchild[i + 1];
            }
            else
            {
                break;
            }
        }
        cur->parent->key[i + 1] = tmp;
        cur->parent->pchild[i + 2] = newNode;
        cur->parent->keyNum++;
        newNode->parent = cur->parent;
    }
    else//如果旧节点是根节点
    {
        cur->parent = new BTnode<T>;//新建根节点
        cur->parent->pchild[0] = cur;//放置新的根节点的孩子
        cur->parent->key[cur->parent->keyNum++] = tmp;
        cur->parent->pchild[cur->parent->keyNum] = newNode;
        newNode->parent = cur->parent;//放置新的根节点的孩子
        root = cur->parent;//将根节点指向新建的根节点
    }
}
//***********插入
template <class T>
void BTtree<T>::isInsert(BTnode<T> *cur, T value)
{
    if (cur)
    {
        if (cur->keyNum == MAXKEY)//如果该节点满员则将节点进行分割，保证每次上移都不会出现溢出的情况
        {
            //*******spliter(cur)
            spliter(cur);
            cur = cur->parent;
        }
        if (cur->isleaf)//如果当前查找到的节点是叶子节点，则在叶子节点中插入
        {
            int i = cur->keyNum - 1;
            for (; i >=0; i--)
            {
                if (value < cur->key[i])
                {
                    cur->key[i + 1] = cur->key[i];
                }
                else
                {
                    break;
                }
            }
            cur->key[i + 1] = value;
            cur->keyNum++;
        }
        else//如果不为叶子节点，则在当前节点中找到合适的位置进入孩子节点
        {
            for (int i = 0; i < cur->keyNum; i++)
            {
                if (value < cur->key[i])
                {
                    isInsert(cur->pchild[i], value);
                    return;
                }
            }
            isInsert(cur->pchild[cur->keyNum], value);//进入最后一个孩子节点
        }
    }
}
//****插入的接口
template<class T>
void BTtree<T>::insert(T value)
{
    T *flag = isFind(root, value);//判断b树中是否已经存在该元素，则不插入
    if (flag)
        return;
    else
    {
        if (root)
        {
            isInsert(root, value);
        }
        else
        {
            root = new BTnode<T>;
            root->isleaf = true;
            root->key[root->keyNum++] = value;
        }
    }
}
//**********查找元素
template<class T>
T* BTtree<T>::isFind(BTnode<T> *cur, T value)
{
    if (cur)
    {
        for (int i = 0; i < cur->keyNum; i++)
        {
            if (value < cur->key[i])
            {
                T* flag = isFind(cur->pchild[i], value);
                return flag;
            }
            else if (value == cur->key[i])
                return &cur->key[i];
        }
        T* flag=isFind(cur->pchild[cur->keyNum], value);
        return flag;
    }
    else
        return NULL;
}
template<class T>
BTtree<T>::BTtree()
{
    root = NULL;
}

#endif // BTTREE_H
