#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H
#include<bttree.h>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<direct.h>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<QObject>
#include<QFile>
#include<unordered_map>
#include<QHash>
#include<heap.h>
using namespace std;
//****************
//注意：在运行前，因为没有用户的文件选择操作，请自行将测试数据的文件名改为：“PAGEDATA.txt”
//并将测试数据放在与程序同一级的目录下
//建立索引的数据结构：哈希表+倒排索引（原本是想用b树+倒排的，但是后来发现我存储索引的方式会使b树有大量的数据冗余，且效率较低，所以改用了哈希）
//计算网页间的可信度算法：pagerank算法
//****************
class Search_engine:public QObject
{
     Q_OBJECT
public:
    explicit Search_engine(QObject *parent=NULL);
    void pagerank_new(vector<vector<int>> &v_matrix,int v_max);
    void Create_URLIndex();
    void Create_KEYIndex();
    void Start();
    void CreateFile();
    void sleep(unsigned int mesc);
    void Create_KeywordIndexFile(string filename );
    void Creatr_IndexFromFiletoMemory();
    void ReadInfomationFile(QFile &file);
    int Search(string keyword, int showpage,vector<SORT_STRUCT>& v_sort);
    vector<SORT_STRUCT>top;//记录top 10
private:
    QHash<int,URL_INDEX> url_index;//url的哈希索引
    QHash<QString,KEYWORLD> key_index;//单词的哈希索引
    int MAXPAGE;//记录网页的数量
    int keywordNUm;//记录所有出现过的单词的个数
    void Create_URLFile(string path);
    signals:
    void sendProgress(int value);
};

#endif // SEARCH_ENGINE_H
