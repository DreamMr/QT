#ifndef BINARYTREE_H
#define BINARYTREE_H
#include"binarytreenode.h"
#include"queue.h"
#include<fstream>
#include<Windows.h>
#include<QMessageBox>
using namespace std;


template<class T>
class BinaryTree
{
    BinaryTreeNode<T> *root;
    void BuildTree(BinaryTreeNode<T> *&current,T *p,int &i);
    void (*visit) (BinaryTreeNode<T> *current);
    void preorder(BinaryTreeNode<T> *current);
    void postorder(BinaryTreeNode<T> *current);
    char *substr(char *p, int pos, int size_t);
    int find(char p, char *s);
    bool find(BinaryTreeNode<T> *current, T val,ofstream &out);
    int size;
    void bfs(T *p);
    void Build(char *p_pre, char *p_in, int &i_pre, BinaryTreeNode<T> *&current);
    void inorder(BinaryTreeNode<T> *current);
    void del(BinaryTreeNode<T> *current);
    int GetLevel(BinaryTreeNode<T> *&current);
    int Level;
    void CreatePoint(BinaryTreeNode<T> *current, double word_len, double deep_high,double bro_tmp);
    bool Check(int size_t,int i){
        if(size_t<=i)
        {
            QMessageBox::warning(NULL,"error","overflow",QMessageBox::Ok);
            return false;
        }
        else
        {
            return true;
        }
    }

   static void SwapTree(BinaryTreeNode<T> *current);
   Point p_map;
public:
   bool flag;
    BinaryTree(int value,T *p);
    BinaryTree(char *p_pre, char *in) { int i_pre = 0; Build(p_pre, in, i_pre, root); }
    void PreOrder(void (*thevisit)(BinaryTreeNode<T> *current));
    void PostOrder(void(*thevisit)(BinaryTreeNode<T> *current)) { visit = thevisit; postorder(root); }
    void InOrder(void(*thevisit)(BinaryTreeNode<T> *current)) { visit = thevisit; inorder(root); }
    void Find( T val);
    void Swap(){visit=SwapTree;preorder(root);}
    Point Graph(double word_len,double bro,double deep_high);
    void curreset(){current=root;}
    BinaryTreeNode<T> *current;
    ~BinaryTree() {  del(root); }
};
template<class T>
void BinaryTree<T>::SwapTree(BinaryTreeNode<T> *current)
{
    BinaryTreeNode<T> *tmpNode = current->RightChild;
    current->RightChild = current->LeftChild;
    current->LeftChild = tmpNode;
}
template<class T>
void BinaryTree<T>::CreatePoint(BinaryTreeNode<T> *current,double word_len,double deep_high,double bro_tmp)
{
    if (current->LeftChild != NULL)
    {
        int tmp = pow(2, Level+1 - current->LeftChild->level - 2);
        tmp = tmp * 2 - 1;
        current->LeftChild->point.x = current->point.x - tmp*bro_tmp;
        current->LeftChild->point.y = current->point.y + deep_high + word_len;
        if(current->LeftChild->point.x>p_map.x){p_map.x=current->LeftChild->point.x;}
        if(current->LeftChild->point.y>p_map.y){p_map.y=current->LeftChild->point.y;}
        CreatePoint(current->LeftChild,word_len,deep_high,bro_tmp);
    }
    if (current->RightChild != NULL)
    {
        int tmp = pow(2, Level + 1 - current->RightChild->level - 2);
        tmp = tmp * 2;
        current->RightChild->point.x = current->point.x + tmp*bro_tmp;
        current->RightChild->point.y = current->LeftChild->point.y;
        if(current->RightChild->point.x>p_map.x){p_map.x=current->RightChild->point.x;}
        if(current->RightChild->point.y>p_map.y){p_map.y=current->RightChild->point.y;}
        CreatePoint(current->RightChild,word_len,deep_high,bro_tmp);
    }
}
template<class T>
Point BinaryTree<T>::Graph(double word_len, double bro,double deep_high)//字长 兄弟之间长度 高度
{
   // Point p_map;
    Level = GetLevel(root);
    int temp = pow(2, Level);
   // p_map.x = temp*bro;
   // p_map.y = (deep_high + word_len)*(Level - 1) + word_len * 2;
    root->point.x = (temp - 1)*bro / 2;
    root->point.y = word_len;
    CreatePoint(root, word_len, deep_high, bro/2);
    return p_map;
}
template<class T>
int BinaryTree<T>::GetLevel(BinaryTreeNode<T> *&current)
{
    if (current == NULL) { return 0; }
    if (current->LeftChild != NULL) { current->LeftChild->level = current->level + 1; }
    int i = GetLevel(current->LeftChild) + 1;
    if (current->RightChild != NULL) { current->RightChild->level = current->level + 1; }
    int j = GetLevel(current->RightChild) + 1;
    return (i < j) ? j : i;
}
template<class T>
void BinaryTree<T>::inorder(BinaryTreeNode<T> *current)
{
    if (current->data=='#') { return; }
    inorder(current->LeftChild);
    visit(current);
    inorder(current->RightChild);
}
template<class T>
void BinaryTree<T>::del(BinaryTreeNode<T> *current)
{
    if (current == NULL) { return; }
    del(current->LeftChild);
    del(current->RightChild);
    delete current;
}
template<class T>
int BinaryTree<T>::find(char p, char *s)
{
    for(int i=0;i<strlen(s);i++)
        if (s[i] == p) { return i; }
    return -1;
}
template<class T>
void BinaryTree<T>::Build(char *p_pre, char *p_in, int &i_pre, BinaryTreeNode<T> *&current)
{
    current = new BinaryTreeNode<T>(p_pre[i_pre]);
    int i_in = find(p_pre[i_pre], p_in);
    int i_tmp = i_pre++;
    if (i_in != -1)
    {
        char *tmp_in = substr(p_in, 0, i_in);
        if (tmp_in[0] != '\0')
        {
            Build(p_pre, tmp_in, i_pre, current->LeftChild);
        }
        else
        {
            current->LeftChild = new BinaryTreeNode<T>('#');
        }
    }
    i_in = find(p_pre[i_tmp], p_in);
    if (i_in != -1)
    {
        char *tmp_in = substr(p_in, i_in+1, strlen(p_in) - i_in-1);
        if (tmp_in[0] != '\0')
        {
            Build(p_pre, tmp_in, i_pre, current->RightChild);
        }
        else
        {
            current->RightChild = new BinaryTreeNode<T>('#');
        }
    }
    return;
}
template<class T>
char *BinaryTree<T>::substr(char *p, int pos, int s)
{
    char *tmp = new char[s + 1];
    int i = 0;
    for (; i < s; i++)
    {
        tmp[i] = p[pos++];
    }
    tmp[i] = '\0';
    return tmp;
}
template<class T>
void BinaryTree<T>::bfs(T *p)
{
    int i=0;
    T tmp;
    //in >> tmp;
    tmp=p[i++];
    root = new BinaryTreeNode<T>(tmp);
    if (tmp == '#') {  return; }
    Queue<BinaryTreeNode<T> *>q;
    BinaryTreeNode<T> *current = root;
    q.push(current);
    do
    {
        current = q.front();
        q.pop();
       // in >> tmp;
        tmp=p[i++];
        if(!Check(strlen(p),i)){flag=false;break;}
        current->LeftChild = new BinaryTreeNode<T>(tmp);
        if (tmp != '#')
        {
            q.push(current->LeftChild);
        }
        //in >> tmp;
        tmp=p[i++];
         if(!Check(strlen(p),i-1)){flag=false;break;}
        current->RightChild = new BinaryTreeNode<T>(tmp);
        if (tmp != '#' && tmp !='\0')
        {
            q.push(current->RightChild);
        }
    } while (!q.isEmpty());
}
template<class T>
bool BinaryTree<T>::find(BinaryTreeNode<T> *current, T val,ofstream &out)
{
    //**********递归算法
    if (current == NULL) { return false; }
    if (current->data == val) { return true; }
    else if (find(current->LeftChild, val,out)) { out << current->data << endl; return true; }
    else if (find(current->RightChild, val,out)) { out << current->data << endl; return true; }
    else { return false; }
}
template<class T>
void BinaryTree<T>::Find(T val)
{
    ofstream out("out.txt");
    find(root, val,out);
    out.close();
    ShellExecute(NULL, L"open", L"out.txt", NULL, NULL, SW_SHOWNORMAL);
}
template<class T>
void BinaryTree<T>::postorder(BinaryTreeNode<T> *current)
{
    if (current->data=='#') { return; }
    postorder(current->LeftChild);
    postorder(current->RightChild);
    visit(current);
    return;
}
template<class T>
void BinaryTree<T>::preorder(BinaryTreeNode<T> *current)
{
    if (current->data=='#') { return; }
    visit(current);
    preorder(current->LeftChild);
    preorder(current->RightChild);
}
template<class T>
void BinaryTree<T>::PreOrder(void(*thevisit)(BinaryTreeNode<T> *current))
{
    visit = thevisit;
    //visit = SwapTree;
    preorder(root);
}
template<class T>
BinaryTree<T>::BinaryTree(int value,T *p)
{
    int i=0;
    flag=true;
    //ifstream in("in.txt");
    if (value)
    {
        BuildTree(root, p,i);
    }
    else
    {
        bfs(p);
    }
    //in.close();
}
template<class T>
void BinaryTree<T>::BuildTree(BinaryTreeNode<T> *&current,T *p,int &i)
{
    if(!Check(strlen(p),i)){flag=false;
        return;}
    T tmp;
    tmp=p[i++];
    current = new BinaryTreeNode<T>(tmp);
     if (tmp == '#' || tmp=='\0') { return; }
    size++;
    if(flag)
    BuildTree(current->LeftChild,p,i);
    if(flag)
    BuildTree(current->RightChild,p,i);
}


//template<class T>
//void output(BinaryTreeNode<T> *current)
//{
//	cout << current->data;
//}


#endif // BINARYTREE_H
