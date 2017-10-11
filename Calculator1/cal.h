#ifndef CAL_H
#define CAL_H
#include<QString>
#include<QMessageBox>
#include<math.h>
#include"stack.h"
#define PI 3.1415926
class cal
{
    QString s;
public:
    bool err;
    cal(QString input);
    double findout();
    double jiao(double x);
};
double cal::jiao(double x)
{
    return x*PI/180;
}

double cal::findout()
{
    err=false;
    int length = s.length();
    bool flag=true;
    Stack<double> stack;
    for (int i = 0; i < length;)
    {
        if (s[i] == ',')
        {
            i++;
            int x = i;
            while (s[i] >= '0' && s[i] <= '9' || s[i]=='.')
            {
                i++;
            }
            //stack.push(change(substr(s,x,i-x)));
            QString tmp=s.mid(x,i-x);
            stack.push(tmp.toDouble());
        }
        else if (s[i] == '#')
        {
            break;
        }
        else
        {

            double x = 0, y = 0;
            y = stack.top();
            stack.pop();
            if(!stack.empty())//添加此处会导致单一负数无法输出
            {
                flag=false;
                QMessageBox::warning(NULL,"符号错误","重新输入",QMessageBox::Ok,QMessageBox::Ok);
            }
            x = stack.top();
            stack.pop();
            double sum = 0;
            if (s[i] == '+')
            {
                sum = x + y;
            }
            else if (s[i] == '-')
            {
                sum = x - y;
            }
            else if (s[i] == '*')
            {
                sum = x*y;
            }
            else if (s[i] == '/')
            {
                if(y==0)
                {
                    QMessageBox::warning(NULL,"运算错误","分母为零，请重新输入",QMessageBox::Ok,QMessageBox::Ok);
                    flag=false;
                }
                else
                {
                    sum = x / y;
                }
            }
            else if(s[i]=='%')
            {
                int x_tmp=x;
                int y_tmp=y;
                if(x==x_tmp && y==y_tmp && y!=0)
                {
                    sum=x_tmp%y_tmp;
                }
                else
                {
                    flag=false;
                    QMessageBox::warning(NULL,"运算错误","取余运算错误，请重新输入",QMessageBox::Ok,QMessageBox::Ok);
                }
            }
            i++;
            stack.push(sum);
        }
        if(!flag || err)
        {
            break;
        }
    }
    if(flag && !err)
    {
        return stack.top();
    }
    else
    {
        return -1;
    }
}

cal::cal(QString input)
{
    //err=false;
    QChar compare[48];
    compare['#'] = 0; compare[')'] = 1; compare['+'] = 2; compare['-'] = 2; compare['*'] = 3; compare['/'] = 3; compare['%'] = 3; compare['('] = 4;
    Stack<QChar> stack;
    stack.push('#');
    bool flag = true;
    bool jump=false;
    bool err=false;
    int length = input.length();
  int i=0;
  while(i<length)
  {
      if(input[i]>='0' && input[i]<='9'|| input[i]=='.')
      {
          if(flag)
          {
              s+=",";
              flag=false;
          }
          s+=input.mid(i,1);
          i++;
      }
      else if(input[i]>='a'&& input[i]<='z')
      {
          QChar tmp_ar=input[i];
          //QString tmp=input.mid(i+1,1);
          s+=",";
          i++;
          //int x=i;
          QString tmp=input.mid(i,1);
          i++;
          int x=i;
          while(input[i]>='0' && input[i]<='9'|| input[i]=='.')
          {
              i++;
          }
          tmp+=input.mid(x,i-x);
          double num=tmp.toDouble();
          if(tmp_ar=='c')
          {
              num=cos(jiao(num));
          }
          else if(tmp_ar=='s')
          {
              if(num>0)
              {
                  num=sqrt(num);
              }
              else if(num==0)
              {
                  if(input[i]=='-')
                  {
                    err=true;
                  }
                  else
                  {
                      num=0;
                  }
              }
          }
          else if(tmp_ar=='a')
          {
              if(num)
              {
                 num=1/num;
              }
              else
              {
                  err=true;
              }
          }
          else if(tmp_ar=='t')
          {
              int num_tmp=num;
              if((num_tmp%90!=0 || num_tmp%180==0))
              {
                  num=tan(jiao(num));
              }
              else
              {
                  err=true;
              }
              if(num<0.0000000000001)
              {
                  num=0;
              }
          }
          else if(tmp_ar=='z')
          {
              num=sin(jiao(num));
          }
          else if(tmp_ar=='y')
          {
              num=pow(2,num);
          }
          if(num<0)
          {
              tmp="0,";
              tmp+=QString::number(-num);
              tmp+="-";
          }
          else
          {
               tmp=QString::number(num);
          }
          s+=tmp;
      }
      else if(input[i]==')' && stack.top()=='(')
      {
          stack.pop();
          i++;
      }
      else if(input[i]=='#' && stack.top()=='#')
      {
          stack.pop();
          i++;
      }
      else if(compare[input[i].toLatin1()]>compare[stack.top().toLatin1()]|| stack.top()=='(')
      {
          flag=true;
          stack.push(input[i]);
          i++;
      }
      else if(compare[input[i].toLatin1()]<=compare[stack.top().toLatin1()] )
      {
              QString tmp(stack.top());
              stack.pop();
              s+=tmp;
      }
  }
  if(stack.empty())
  {
      err=true;

  }
}

#endif // CAL_H
