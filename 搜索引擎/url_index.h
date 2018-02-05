#ifndef URL_INDEX_H
#define URL_INDEX_H
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
using namespace std;
struct URL
{
    string url;
    string infomation;
    URL()
    {
        url.clear();
        infomation.clear();
    }
    bool operator==(URL &a)
    {
        return url==a.url;
    }
    bool operator<(URL &a)
    {
        return url<a.url;
    }
    URL& operator=(URL &a)
    {
        url=a.url;
        infomation=a.infomation;
        return *this;
    }
};
struct SORT_STRUCT
{
    URL url;
    double score;
    SORT_STRUCT()
    {
        score=0;
    }
    SORT_STRUCT& operator=(SORT_STRUCT &a)
    {
        score=a.score;
        url=a.url;
        return *this;
    }
    bool operator <(SORT_STRUCT a)
    {
        return score>a.score;
    }
};

struct URL_INDEX
{
    string url;
    string infomation;
    double paiming;
    URL_INDEX()
    {
        paiming = -1;
        url.clear();
        infomation.clear();
    }
    void output(fstream &out)
    {
        out << url << '\t' << infomation << '\t' << paiming <<endl;
    }

    URL_INDEX& operator=(URL_INDEX &a)
    {
        url = a.url;
        infomation = a.infomation;
        paiming = a.paiming;
        return *this;
    }
};
struct KEYWORLD
{
    vector<int>v;
    void output(fstream &out)
    {
        out <<v.size()<<'\t';
        int i=0;
        for(;i<v.size()-1;i++)
            out<<v[i]<<'\t';
        out<<v[i]<<endl;
    }
    KEYWORLD& operator=(KEYWORLD &a)
    {
        v=a.v;
        return *this;
    }
};
#endif // URL_INDEX_H
