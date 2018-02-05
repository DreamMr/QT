#ifndef A_NODE_H
#define A_NODE_H
#include<QString>
class A_node
{
public:
    A_node(QString s, double f_t, int x1, int y1, int prex, int prey, int st, A_node *p)
    {
        sum = s; f = f_t; x = x1; y = y1; pre_x = prex; pre_y = prey; step = st; pre = p;
    }
    A_node()
    {
        f = 0;
        x = -1; y = -1; pre_x = -1; pre_y = -1; step = 0; pre = NULL;
    }
    QString sum;//矩阵压缩
    double f;//记录当前所花的代价
    int x;//当前所在的行
    int y;//当前所在的列
    int pre_x;//上一个状态的行
    int pre_y;//上一个状态的列
    int step;//记录已走的步数
    A_node *pre;//记录上一个状态
    A_node operator=(const A_node &a)
    {
        sum = a.sum;
        f = a.f;
        x = a.x;
        y = a.y;
        step = a.step;
        pre_x = a.pre_x;
        pre_y = a.pre_y;
        pre = a.pre;
        return *this;
    }
    bool operator <(const A_node *b)
    {
        return f > b->f;
    }
};

#endif // A_NODE_H
