#ifndef BTNODE_H
#define BTNODE_H
#define MAXKEY 500//记录一个b树节点能存的元素大小
template<class T>
struct BTnode
{
    BTnode *parent;//记录父亲节点
    BTnode *pchild[MAXKEY+1];//记录孩子节点
    T key[MAXKEY];//关键字
    bool isleaf;//是否为叶子节点默认为否
    int keyNum;//记录当前节点关键字的个数
    BTnode()
    {
        for (int i = 0; i < MAXKEY + 1; i++)
        {
            pchild[i] = nullptr;
        }
        isleaf = false;
        keyNum = 0;
        parent = nullptr;
    }
};
#endif // BTNODE_H
