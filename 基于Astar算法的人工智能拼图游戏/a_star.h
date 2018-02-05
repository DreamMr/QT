#ifndef A_STAR_H
#define A_STAR_H
#include<QString>
#include"heap.h"
#include<QSet>
#include<QStack>
struct Node
{
    int x_start;
    int y_start;
};
class A_star
{
public:
    A_star(int r){
        row=r;
        BeGin();
        //*********初始化四个方向
        dir[0][0] = 0; dir[0][1] = 1;//front
        dir[1][0] = 0; dir[1][1] = -1;//back
        dir[2][0] = 1; dir[2][1] = 0;//down
        dir[3][0] = -1; dir[3][1] = 0;//up
            }
    int row;//记录当前矩阵的规模
    Node *_normal;
    QSet<int>closeList;//用于存放以走过的状态
     int dir[4][2];//记录四个方向
     //***********将矩阵压缩为字符串
    QString makeInt(int **a)
     {
         QString sum ;
         for (int i = 0; i < row; i++)
             for (int j = 0; j < row; j++) {
                 if (a[i][j] >= 0) {
                     sum += QString::number(a[i][j]);
                 }
             }
         return sum;
     }
    void BeGin()
    {
        _normal=new Node[row*row];
        int k = 0;
        for (int i = 0; i<row; i++)
        {
            for (int j = 0; j<row; j++)
            {
                _normal[k].x_start = i;
                _normal[k++].y_start = j;
            }
        }

    }
    //*******根据x方向找出相反的方向
    int reduce_x(int dir_x)
    {
        switch (dir_x)
        {
        case 0:
        {
            return 0;
        }
        case 1:
        {
            return -1;
        }
        case -1:
        {
            return 1;
        }
        }
    }
//******根据y方向确定y的逆方向
    int reduce_y(int dir_y)
    {
        switch (dir_y)
        {
        case 0:
        {
            return 0;
        }
        case 1:
        {
            return -1;
        }
        case -1:
        {
            return 1;
        }
        }
    }
    //**********更具mode修改矩阵，0则返回逆方向，1则根据dir的方向进行变化
    void change(int _x, int _y, int mode, int dir_x, int dir_y,int **location)
    {
        if (!mode)//fanhui
        {
            dir_x = reduce_x(dir_x);
            dir_y = reduce_y(dir_y);
        }

        int tmp = location[_x][_y];
        location[_x][_y] = location[_x + dir_x][_y + dir_y];
        location[_x + dir_x][_y + dir_y] = tmp;
    }
//********计算h(x)
    double h_cost(int **location)
    {
        double h = 0;
        for (int i = 0; i < row; i++)
            for (int j = 0; j < row; j++)
            {
                int tmp = location[i][j];
                double h_tmp = pow(i - _normal[tmp].x_start, 2 * 1.0) + pow(j - _normal[tmp].y_start, 2 * 1.0);
                h += sqrt(h_tmp);
            }
        return h;
    }
//*********将矩阵字符串还原回矩阵
    int ** makeMatrix(QString sum)
    {
        int **a = new int *[row];
        int k = 0;
        for (int i = 0; i <row; i++)
        {
            a[i] = new int[row];
            for (int j = 0; j <row; j++)
            {
                a[i][j] = sum[k++].toLatin1()-48;
            }
        }
        return a;
    }
    //************A*算法主体
    QStack<A_node> A_search(A_node *a)
    {
        Heap queue;
        queue.insert(a);

        while (!queue.empty())
        {
            A_node *tmp = queue.top();//从优先队列中取出代价最小的

            queue.pop();
            int **map = makeMatrix(tmp->sum);//还原实矩阵

            for (int i = 0; i < 4; i++)//进行四个方向的遍历
            {
                //****判断方向是否合法
                if (tmp->x + dir[i][0] >= row || tmp->y + dir[i][1] >= row || tmp->x + dir[i][0] < 0 || tmp->y + dir[i][1] < 0|| (tmp->x+dir[i][0]==tmp->pre_x && tmp->y+dir[i][1]==tmp->pre_y)) { continue; }

                A_node *_tmp = new A_node(tmp->sum,tmp->f,tmp->x,tmp->y,tmp->pre_x,tmp->pre_y,tmp->step,tmp->pre);
                change(_tmp->x, _tmp->y, 1, dir[i][0], dir[i][1], map);//将矩阵朝着方向进行更改
                _tmp->x = tmp->x + dir[i][0]; _tmp->y = tmp->y + dir[i][1];
                 _tmp->sum = makeInt(map);//矩阵压缩

                 if (closeList.find(_tmp->sum.toInt()) != closeList.end()) { change(_tmp->x, _tmp->y, 0, dir[i][0], dir[i][1], map); continue; }
                closeList.insert(_tmp->sum.toInt());//将当前状态加入closelist
                  _tmp->pre = tmp;
                double h = h_cost(map);
                if (h == 0) {//如果达到目标状态则记录路径到栈中
                    QStack<A_node> stack;
                    A_node *b = _tmp->pre;
                    A_node *a = _tmp;
                    while(b)
                    {
                       stack.push(*a);
                        a = b;
                         b = b->pre;
                    }
                    queue.~Heap();
                    return stack;
                }
                //********计算所花代价
                double g = _tmp->step + 1;
                _tmp->f = h + g;
                _tmp->step++;
                _tmp->pre_x = tmp->x;
                _tmp->pre_y = tmp->y;
                //_tmp.l.push_back(tmp.sum);
             //*********还原状态
                change(_tmp->x, _tmp->y, 0, dir[i][0], dir[i][1], map);
                queue.insert(_tmp);
            }

        }
    }
};

#endif // A_STAR_H
