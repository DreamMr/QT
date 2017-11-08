#include "compression_nuw.h"

Compression_nuw::Compression_nuw(QObject *parent) : QObject(parent)
{
    file_size=0;
}
int Compression_nuw::setvalue(char *a)
{
   int tmp = 0;
   int size = strlen(a);
   for (int i = size-1; i >= 0; i--)
   {
       if (a[i]!=48)
       {
           tmp = tmp + pow(2, size-1 - i);
       }
   }
   return tmp;
}
char* Compression_nuw::addch(char *a, char tmp)
{
   if (a != NULL)
   {
       int size = strlen(a);
       char *tmp1 = new char[size];
       for (int i = 0; i < size; i++)
       {
           tmp1[i] = a[i];
       }
       a = new char[size + 2];
       int i = 0;
       for (; i < size; i++)
           a[i] = tmp1[i];
       a[i++] = tmp;
       a[i] = '\0';
   }
   else
   {
       a = new char[2];
       a[0] = tmp;
       a[1] = '\0';
   }
   return a;
}
void Compression_nuw::PreOrder(BinaryTreeNode<long long> *current, char *a)
{
   if (current == NULL) { return; }
   if (current->LeftChild->LeftChild == NULL)
   {
       aInfo[current->LeftChild->data].len = strlen(a);
       aInfo[current->LeftChild->data].value = setvalue(a);
       aInfo[current->LeftChild->data].p = a;
   }
   else
   {
       PreOrder(current->LeftChild, addch(a,'0'));
   }
   PreOrder(current->RightChild, addch(a, '1'));
}
int Compression_nuw::Addtail(char *p, int start,int end)
{
   char *tmp = new char[end-start+2];
   int size = strlen(p);
   int i = start;
   for (; i < size && i<=end; i++)
       tmp[i-start] = p[i];
   tmp[i-start] = '\0';
   return setvalue(tmp);
}
QString Compression_nuw::Addfile(QString p)
{
   QString tmp;
   int k=0;
   for(int i=p.length()-1;i>=0;i--)
   {
       if(p[i].toLatin1()=='.')
       {
           k=i;
           break;
       }
   }
   tmp=p.mid(k,p.length()-k);

   return tmp;
}
double Compression_nuw::Coding()
{
   char *a = NULL;
   PreOrder(tree.GetRoot(), a);
   QFile in(openfile);
   QFileInfo qfinfo(in);
   file_size=qfinfo.size();
   in.open(QIODevice::ReadOnly);
   QFile out(savefile);
   out.open(QIODevice::WriteOnly);
    QString tmp_s=Addfile(openfile);
   QByteArray ba=tmp_s.toLatin1();
   char* filename=ba.data();
   filename[tmp_s.length()]='\0';
   int f_size=strlen(filename);
   out.write((char*)&f_size,sizeof(int));
   out.write((char*)filename,sizeof(char)*f_size);
   unsigned int *temp=new unsigned int[1024*1024];
   int tt=out.write((char*)&size, sizeof(size));//有几种字符
   long long pgn=0;
   for (int i = 0; i < 256; i++)
   {
       if (aInfo[i].count)
       {
           out.write((char*)&aInfo[i].ch, sizeof(aInfo[i].ch));//字符
           out.write((char*)&aInfo[i].count, sizeof(aInfo[i].count));//字符出现的次数
       }
   }
   int k = 32;
   unsigned char *tmp=new unsigned char [1024*1024*4];
   temp[0] = 0;
   int temp_num = 0;
   while (!in.atEnd())
   {
       int size1= in.read((char *)tmp, sizeof(unsigned char)*1024*1024*4);
       pgn+=size1;double per=pgn*1.0/file_size*1.0;int tlr=50+50*per;
       emit senddata(tlr);
       for (int i = 0; i < size1; i++)
       {
           if (k > aInfo[tmp[i]].len)
           {
               temp[temp_num] <<= aInfo[tmp[i]].len;
               temp[temp_num] |= aInfo[tmp[i]].value;
               k -= aInfo[tmp[i]].len;
           }
           else
           {
               temp[temp_num] <<= k;
               int sub = k - aInfo[tmp[i]].len;
               if (sub<0)
               {
                   temp[temp_num++] |= Addtail(aInfo[tmp[i]].p, 0,k-1);
                   if (temp_num >= 1024 * 1024) {
                       out.write((char*)temp, sizeof(unsigned int) * 1024 * 1024); temp_num = 0; temp[temp_num] = 0; }
                   temp[temp_num] = Addtail(aInfo[tmp[i]].p, k, aInfo[tmp[i]].len - 1);
                   k =32+sub ;
               }
               else if (sub == 0)
               {
                   temp[temp_num++] |= aInfo[tmp[i]].value;
                   if (temp_num >= 1024 * 1024) { out.write((char*)temp, sizeof(unsigned int) * 1024 * 1024); temp_num = 0; temp[temp_num] = 0; }
                   temp[temp_num] = 0;
                   k = 32;
               }
           }
       }
   }
   temp[temp_num] <<= k;
   out.write((char*)temp, sizeof(unsigned int)*(temp_num+1));
   double re_tmp=out.size()*1.0/in.size()*1.0;
   in.close();
   out.close();
   emit senddata(99);
   delete[]temp;
   delete[]tmp;
   return re_tmp;
}
void Compression_nuw::CreateInfo()
{
   HuffmanTree<long long> *t=new HuffmanTree<long long> [size];
   for (int i = 0; i < size; i++)
   {
       t[i].setRoot(bInfo[i].count, bInfo[i].ch);
   }
   MinHeap<HuffmanTree<long long>>h(t, size);
   HuffmanTree <long long>*tmp=new HuffmanTree<long long>[2];
   while (h.GetSize()!=1)
   {
       //HuffmanTree <long long>*tmp = new HuffmanTree<long long>[2];
       tmp[0] = h.top(); h.pop();
       tmp[1] = h.top(); h.pop();
       tmp[0]=setTree(tmp[1], tmp[0]);
       h.push(tmp[0]);
   }
   tree = h.top(); h.pop();
   emit senddata(50);
}
double Compression_nuw::Compression_start(QString openfile1,QString savefile1)
{
    size=0;
    QFile in(openfile1);
    in.open(QIODevice::ReadOnly);
   savefile = savefile1;
   openfile = openfile1;
   char tmp1[256];
   for (int i = 0; i < 256; i++)
   {
       tmp1[i] = 0;
       aInfo[i].count=0;
       aInfo[i].len=0;
   }
   unsigned char *tmp=new unsigned char[1024*1024*4];
   while (!in.atEnd())
   {
     int num=in.read((char*)tmp, sizeof(unsigned char) * 1024*1024*4);
     if(num==-1){return -1;}
       for (int i = 0; i < num; i++)
       {
           aInfo[tmp[i]].count++;
           if (!tmp1[tmp[i]]) {
               size++;
               aInfo[tmp[i]].ch = tmp[i];
               tmp1[tmp[i]] = 1;
           }
       }
   }
   in.close();
   bInfo = new Info[size];
   int k = 0;
   for (int i = 0; i <256 ;i++)
   {
       if (aInfo[i].count != 0)
       {
           bInfo[k++] = aInfo[i];
       }
   }
   size = k;
   emit senddata(30);
   if(size!=0)
   CreateInfo();
   double re_tmp=Coding();
   int re=re_tmp*1000;
   re_tmp=re*1.0/10;
   tree.Destory();
   emit senddata(100);
   delete[]tmp;
   if(re<=0)
   return 0;
   else
       return re_tmp;
}
char* Compression_nuw::AddCHAR(char *p1, char *p2)
{
   if (p1 == NULL) { return p2; }
   int size1 = strlen(p1); int size2 = strlen(p2);
   int t =  size1+size2 ;
   char *tmp = new char[t+1];
   int k = 0;
   for (int i = 0; i < size1; i++)
   {
       tmp[k++] = p1[i];
   }
   for (int i = 0; i < size2; i++)
       tmp[k++] = p2[i];
   tmp[k] = '\0';
   return tmp;
}
void Compression_nuw::Decoding(QFile &in,QString save)
{

   BinaryTreeNode<long long> *cur = tree.GetRoot();
   QFile out(save);
   QFileInfo finfo(in);
   file_size=finfo.size();
   out.open(QIODevice::WriteOnly);
   unsigned int *temp =new unsigned int[1024*1024];
   int ch_num = 0;
   unsigned char *ch=new unsigned char [1024*1024*4];
   int k = 0;
   long long allCount=0;
   if(size!=0)
   allCount = cur->data;
   long long c = 0;
   long long pgn=0;
   if (c >= allCount) { out.close(); return; }
   while (!in.atEnd())
   {
       int num=in.read((char*)temp, sizeof(unsigned int)*1024*1024);
       pgn+=num;double per=pgn*1.0/file_size*1.0;int tlr=50+50*per;
       emit senddata(tlr);
       for (int i = 0; i < num/4; i++)
       {
           unsigned int a = temp[i];
            for (int j = 0; j < 32; j++)
            {
               temp[i] >>= 31;
               if (temp[i] == 0)
               {
                  cur = cur->LeftChild;
               }
               else
               {
                   cur = cur->RightChild;
               }
               if (cur->LeftChild->LeftChild == NULL)
               {
                   ch[ch_num++] = cur->LeftChild->data;
                   c++;
                   if (c >= allCount) {
                       out.write((char*)ch,sizeof(unsigned char)*ch_num); out.close(); delete[]temp; delete[]ch; return; }
                   if (ch_num >= 1024 * 1024 * 4) { out.write((char*)ch, sizeof(unsigned char) * 1024 * 1024 * 4); ch_num = 0; }
                   cur = tree.GetRoot();
               }
               a <<= 1;
               temp[i] = a;
             }
       }
   }
}
void Compression_nuw::Compression_start(/*char *saveposition,char *openposition,*/QString saveposition,QString openposition,int i)
{
   size=0;
   int temp1 = 0;
   QFile in(openposition);
   if(!in.open(QIODevice::ReadOnly)){return;}
   int f_size=0;
   in.read((char*)&f_size,sizeof(int));
   char* tmp1=new char[256];
   in.read((char*)tmp1,sizeof(char)*f_size);
   tmp1[f_size]='\0';
   QString tl(tmp1);
   saveposition = saveposition+tl;
   in.read((char*)&temp1, sizeof(int));
   size = temp1;
   bInfo = new Info[temp1];
   for (int i = 0; i < temp1; i++)
   {
       in.read((char*)&bInfo[i].ch, sizeof(unsigned char));
       in.read((char*)&bInfo[i].count, sizeof(long long));
   }
   emit senddata(30);
   if(temp1!=0)
   CreateInfo();
   Decoding(in,saveposition);
   emit senddata(100);
   tree.Destory();
   in.close();
}
