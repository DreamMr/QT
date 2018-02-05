#include"search_engine.h"
#include<QTime>
#include<QCoreApplication>
#include<QDebug>
#include<iterator>
#include"getline.h"
Search_engine::Search_engine(QObject *parent):QObject(parent)
{

}
//*********让机器延时********
void Search_engine::sleep(unsigned int mesc)
{
    QTime timer=QTime::currentTime().addMSecs(mesc);
    while(QTime::currentTime()<timer)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}
//*********第一次运行时的初始化，创建索引********
void Search_engine::CreateFile()
{
    QFile file("PAGEDATA.txt");
    vector<vector<int>>matrix;
    bool first = false;
    if (file.open(QIODevice::ReadOnly))
    {
        bool writeinfomation=true;//记录当前网页记录是否已经写过url内容
        GETLINE get;//创建读文件缓存类
        int index = 0;//记录当前已经创建多少url索引
        int bug=0;
        string tmp;//读文件处理的数据
        unordered_map<string,int>m;//用于在建立pagerank需要的数组时查询url的索引
        unordered_map<string,int>::iterator it;
        vector<int>page;int current_index=0;
        URL_INDEX *current_url=new URL_INDEX;
        while (get.getLine(file,tmp))//将一组数据分为三种格式P T Q L
        {
            tmp=tmp.substr(0,tmp.size()-1);
            if (tmp[0] == 'P')//p格式
            {
                 tmp = tmp.substr(2, tmp.size() - 2);
                if (first){
                    url_index[current_index]=*current_url;
                    delete current_url;
                    current_url=new URL_INDEX;
                    //qDebug()<<bug++;
                    matrix.push_back(page);
                    page.clear();
                    writeinfomation=true;
                }
                else{
                    first = true;
                }
                it=m.find(tmp);
                if(it==m.end())//如果当前url并没出现过，添加索引
                {
                    m[tmp]=index;
                    current_index=index++;
                }
                else//否则通过hash找到url对应的索引
                {
                    pair<string,int>p;
                    p=*it;
                    current_index=p.second;
                }
                current_url->url=tmp;
            }
            if (tmp[0] == 'Q')//如果是Q格式
            {
                tmp = tmp.substr(2, tmp.size() - 2);
                 if(writeinfomation)//添加部分信息
                 {
                     string info="   Infomation: "+tmp;
                     current_url->infomation+=info+"......";
                     writeinfomation=false;
                 }
                stringstream ss;
                KEYWORLD t;
                string key;
                ss << tmp;
                while (ss >>key)//建立关键字索引
                {
                    QString tmp_key=QString::fromStdString(key);
                    QHash<QString,KEYWORLD>::iterator it;
                    it=key_index.find(tmp_key);
                    if (it!=key_index.end())
                    {
                        it.value().v.push_back(current_index);
                    }
                    else
                    {
                        t.v.push_back(current_index);
                        key_index[tmp_key]=t;
                    }
                }
            }
            if (tmp[0] == 'L')//L格式
            {
                tmp = tmp.substr(2, tmp.size() - 2);
                it=m.find(tmp);
                if(it==m.end())
                {
                    m[tmp]=index;
                    page.push_back(index++);//添加当前url的出链
                }
                else
                {
                    pair<string,int>p;
                    p=*it;
                    page.push_back(p.second);//添加当前url的出链
                }
            }
            if (tmp[0] == 'T')//T
            {
                tmp = tmp.substr(2, tmp.size() - 2);
                string time="create time: "+tmp;
                current_url->infomation+=time;//记录时间
            }
        }
        url_index[current_index]=*current_url;
        delete current_url;
        current_url=new URL_INDEX;
        qDebug()<<bug++;
        matrix.push_back(page);
        page.clear();
        file.close();
        MAXPAGE = matrix.size();
        emit sendProgress(20);
        //*******create pagerank
        pagerank_new(matrix,index);//pagerank算法
        emit sendProgress(40);
    }
}

//********打开时初始化程序
void Search_engine::Start()
{
    fstream in_keyword("KeyWord.txt", ios::in);
    fstream in_url("url_index.txt", ios::in);
    fstream info("Information.txt", ios::in);
    if (in_keyword && in_url && info)//如果索引文件存在
    {
        in_keyword.close();
        in_url.close();
        info.close();
        QFile infomation("Information.txt");
        infomation.open(QIODevice::ReadOnly);
        ReadInfomationFile(infomation);//将该数据的top以及url个数，关键字个数读入
        info.close();
         emit sendProgress(25);
        Create_URLIndex();//创建url索引
        emit sendProgress(50);
        Creatr_IndexFromFiletoMemory();//将倒排索引从文件读入到内存
        emit sendProgress(100);
    }
    else//如果不存在索引文件
    {
        emit sendProgress(15);
        CreateFile();//创造索引和计算网页的可信度
       emit sendProgress(50);
        Create_URLFile("url_index.txt");//创建url索引文件
        emit sendProgress(75);
        Create_KeywordIndexFile("KeyWord.txt");//创建倒排索引文件
        emit sendProgress(100);
    }
}
//***********读全局信息*****************
void Search_engine::ReadInfomationFile(QFile &file)
{
    GETLINE get;
    string tmp;
    get.getLine(file,tmp);
    QString info;
    //***************读url的总个数，以及关键字的总个数
        info=QString::fromStdString(tmp);
        info=info.mid(0,info.size()-1);
        QStringList list=info.split('\t');
        QString tt;
        //*******MAXPAGE
         tt=list.front();list.pop_front();
         MAXPAGE=tt.toInt();
         //******KEYWORD
         tt=list.front();list.pop_front();
         keywordNUm=tt.toInt();
 //*************读 top 10***********
         int size=0;
         tt=list.front();list.pop_front();
         size=tt.toInt();
         for(int i=0;i<size;i++)
         {
             get.getLine(file,tmp);
             info=QString::fromStdString(tmp);
             info.mid(0,info.size()-1);
             list=info.split('\t');
             tt=list.front();list.pop_front();
             SORT_STRUCT url;url.url.url=tt.toStdString();
             tt=list.front();list.pop_front();
             url.url.infomation=tt.toStdString();
              tt=list.front();list.pop_front();
              url.score=tt.toDouble();
             top.push_back(url);
         }
}
//**************将url索引写入文件
void Search_engine::Create_URLFile(string path)
{
    fstream out(path,ios::out|ios::app);
    if(out)
    {
        QHash<int,URL_INDEX>::iterator it;it=url_index.begin();
        while(it!=url_index.end())
        {
            out<<it.key()<<'\t';
            it.value().output(out);
            it++;
        }
        out.close();
        out.open("Information.txt",ios::out|ios::app);
        out<<url_index.size()<<'\t';
        out.close();
    }
}
//**************搜索算法********************
//大体思路：
//通过关键字索引查找该关键字在哪个url中出现，开一个score数组大小为最大索引号减最小索引号+1
//每当关键字在对应的url出现就在对应的score+1;
//最后加上每一个url的pagerank值得出最后总分
//然后用堆进行排序
//**************************************
int Search_engine::Search(string keyword, int showpage, vector<SORT_STRUCT> &v_sort)
{
    if (keyword.size() && showpage)
    {
        stringstream ss;
        ss << keyword;
        string key_tmp;
        int min_i = 0xffffff, max_i = 0;
        vector<int>index_v;
        //********cha zhao suo yin
        while (ss >> key_tmp)
        {
            while (key_tmp.size())
            {
                QHash<QString,KEYWORLD>::iterator it;
                QString key=QString::fromStdString(key_tmp);
                it=key_index.find(key);
                if (it!=key_index.end())//如果在关键字得索引中找到
                {
                    KEYWORLD k;k=it.value();
                    int tt = 0;
                    int i=0;
                    while (i<k.v.size())//将该关键字在哪个url中出现记录
                    {
                        tt=k.v[i++];
                        index_v.push_back(tt);
                        min_i = min(tt, min_i);
                        max_i = max(tt, max_i);
                    }
                    break;
                }
                key_tmp = key_tmp.substr(0, key_tmp.size() - 1);//如果该关键字不存在则查找该关键字的子集
            }
        }
        //****** 计算得分*******************
        SORT_STRUCT *sort_array=new SORT_STRUCT[max_i - min_i + 1];
        bool *pai = new bool[max_i - min_i + 1];
        for(int i=0;i<max_i - min_i + 1;i++)
            pai[i]=1;
        for (int i = 0; i<index_v.size(); i++)
        {
            sort_array[index_v[i] - min_i].score+=1;//如果关键字在某个url中出现，则对应的url得分+1
            if (pai[index_v[i] - min_i])//避免重复加pagerank值
            {
                pai[index_v[i] - min_i] = 0;
                URL_INDEX url_tmp;
                url_tmp=url_index[index_v[i]];
                sort_array[index_v[i] - min_i].score+=url_tmp.paiming;
                qDebug()<<url_tmp.paiming<<sort_array[index_v[i] - min_i].score;
                sort_array[index_v[i] - min_i].url.url=url_tmp.url;
                sort_array[index_v[i] - min_i].url.infomation=url_tmp.infomation;
            }
        }
        //***********************得分排序*************
       Heap<SORT_STRUCT>heap;
       for(int i=0;i<max_i - min_i + 1;i++)
           heap.insert(sort_array[i]);
       for(int i=0;i<max_i - min_i + 1;i++)
       {
           sort_array[0]=heap.top();heap.pop();
           if(sort_array[0].score!=0){
               v_sort.push_back(sort_array[0]);
               //qDebug()<<QString::fromStdString(sort_array[0].url.url);
           }
       }
     //***************************
        return v_sort.size();
    }
    return 0;
}
//***********将关键字的索引在内存中建立
void Search_engine::Creatr_IndexFromFiletoMemory()
{
    QFile in("KeyWord.txt");

    if (in.open(QIODevice::ReadOnly) && keywordNUm)
    {
        GETLINE get;//读文件缓冲
        for(int i=0;i<keywordNUm;i++)
        {
            string tmp;QString info;QStringList list;int size=0;QString key;
            get.getLine(in,tmp);
            tmp=tmp.substr(0,tmp.size()-1);
            info=QString::fromStdString(tmp);
            list=info.split('\t');
            key=list.front();list.pop_front();QString size_str=list.front();list.pop_front();
            size=size_str.toInt();
            KEYWORLD k;
            for(int i=0;i<size;i++)
            {
                QString num=list.front();list.pop_front();
                int number=num.toInt();
                k.v.push_back(number);
            }
            key_index[key]=k;
        }
        in.close();
    }
}

//**********创建倒排索引文件***********************
void Search_engine::Create_KeywordIndexFile(string filename)
{
    fstream out(filename,ios::out|ios::app);
    QHash<QString,KEYWORLD>::iterator it;it=key_index.begin();
    while(it!=key_index.end())
    {
        string key=it.key().toStdString();
        out<<key<<'\t';
        it.value().output(out);
        it++;
    }
    out.close();
    out.open("Information.txt",ios::out|ios::app);
    out<<key_index.size()<<'\t'<<top.size()<<endl;
    for(int i=0;i<top.size();i++)
        out<<top[i].url.url<<'\t'<<top[i].url.infomation<<'\t'<<top[i].score<<endl;
    out.close();
}
//************从url索引文件创建url索引
void Search_engine::Create_URLIndex()
{
    QFile in("url_index.txt");
    if ( in.open(QIODevice::ReadOnly) && MAXPAGE)
    {
        int key=0;
        GETLINE getLINE;
        string t;
        while(getLINE.getLine(in,t))
        {
            t.substr(0,t.size()-1);
            QString tmp=QString::fromStdString(t);
            QStringList list=tmp.split('\t');
            if(list.size()==4)
            {
                URL_INDEX u;
                QString url;url=list.front();list.pop_front();
                key=url.toInt();

                url=list.front();list.pop_front();
                u.url=url.toStdString();

                url=list.front();list.pop_front();
                u.infomation=url.toStdString();

                url=list.front();list.pop_front();
                u.paiming=url.toDouble();
                url_index[key]=u;
            }
            else
            {
                qDebug()<<"create url_index error";
            }
        }
         in.close();
    }
}

//************pagerank算法************************
//大体思路：
//v_matrix是记录各url的出链的索引，之前开的是一个n*n的矩阵，但是数据量太大，
//于是想到有些是0的值加上还是0，可以不记录，只需记录出链的索引号，就可以映射到
//对应的索引号，进行计算。但是要创建两个一维数组存储pr值
void Search_engine::pagerank_new(vector<vector<int> > &v_matrix, int v_max)
{
    if (v_matrix.size())
    {
        double *v[2]; v[0] = new double[v_max]; v[1] = new double[v_max];
        bool v_count = 0;

        for(int j=0;j<v_max;j++){
            v[v_count][j]=(double)1/MAXPAGE;
        }
        //*******************pagerank算法主体
        double re = 0;
        do
        {
            re = 0;
            double t=(double)1/MAXPAGE;
            for(int j=0;j<v_max;j++)
                v[!v_count][j]=0;
            for (int i = 0; i < MAXPAGE; i++)
            {
               vector<int> tmp;tmp=v_matrix[i];
               double weight=1.0/tmp.size();
               for(int j=0;j<tmp.size();j++)
               {
                   v[!v_count][tmp[j]]+=0.85*weight*v[v_count][i]+(1-0.85)*t;
               }
            }
            for(int i=0;i<v_max;i++)
                 re += abs(v[!v_count][i] - v[v_count][i]);
            v_count = !v_count;
        } while (re >= 0.0000007);
        //**********************将pr值存入排序结构体
        QHash<int,URL_INDEX>::iterator it;it=url_index.begin();
        SORT_STRUCT *sort=new SORT_STRUCT[url_index.count()];
        int sort_num=0;
        while(it!=url_index.end())
        {
            it.value().paiming=v[v_count][it.key()];
            sort[sort_num].score=v[v_count][it.key()];
            sort[sort_num].url.url=it.value().url;
             sort[sort_num++].url.infomation=it.value().infomation;
            it++;
        }
        //***********计算top 10
        for(int i=0;i<10;i++)
        {
            int max_tmp=0;
            for(int j=0;j<url_index.count();j++)
            {
                if(sort[j]<sort[max_tmp])
                {
                    max_tmp=j;
                }
            }
            if(sort[max_tmp].score!=0)
            {
                top.push_back(sort[max_tmp]);
                sort[max_tmp].score=0;
            }
            else
            {
                break;
            }
        }
        //**************
        delete[]sort;
        delete[]v[0];
        delete[]v[1];
    }
}

