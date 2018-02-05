#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QStringList>
#include<treewidget.h>
#include<QFileDialog>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QRegExp>
#include<QTextCursor>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    search=new Search;
    index=0;
    count=0;
    setWindowIcon(QIcon("tubiao.ico"));
    connect(search,SIGNAL(Find(int,QString)),this,SLOT(Find_re(int,QString)));
    connect(ui->treeWidget,SIGNAL(itemClicked(TreeWidgetItem*,int)),this,SLOT(on_treeWidget_itemClicked(TreeWidgetItem*,int)));
    connect(ui->textEdit_name,SIGNAL(textChanged()),this,SLOT(change_name()));
    connect(ui->textEdit_value,SIGNAL(textChanged()),this,SLOT(change_value()));
    connect(ui->comboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(change_type(QString)));
   //*******************处理树形视图的界面
    ui->treeWidget->setColumnCount(2);
    QStringList list;
    list<<"key"<<"value";
    ui->treeWidget->setHeaderLabels(list);
    ui->treeWidget->setColumnWidth(0,ui->treeWidget->width()/2);
      ui->treeWidget->setColumnWidth(1,ui->treeWidget->width()/2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/***************************主要算法思想********************************
 * 我观察JSON的文本格式，发现里面常见的就是大括号和中括号，大括号代表对象里的内容
 * 中括号代表数组，所以我将文本分为两类处理。一类是大括号的处理，另一类是中括号的
 * 处理。大括号处理对象和值，中括号则处理数组
************************************************************************/

//************处理中括号
int MainWindow::solve_middle(QString s, TreeWidgetItem *parent,int &i)
{
     TreeWidgetItem *pre=NULL;
     int count=0;
    while(i<s.size())
    {
        if(s[i]==']'){//遇到右中括号取消
            check_stack.pop();
            return 0;
        }
       // qDebug()<<s[i];
        if(s[i]=='{')//遇到左大括号则进行左大括号的处理
        {
            pre=new TreeWidgetItem(parent,pre);
            QString tmp="["+QString::number(count++)+"]";
            pre->setIcon(0,QIcon("object.png"));
            pre->set_type("object");

            pre->setText(0,tmp);

            check_stack.push(s[i]);

          int check= solve_Big(s,pre,i);
          if(check){return check;}
            i++;
        }
        if(s[i]==']'){//遇到右中括号取消
            check_stack.pop();
            return 0;
        }
        i++;
    }
    return 1;
}
//************解决大括号
int MainWindow::solve_Big(QString s, TreeWidgetItem *parent,int &i)
{
     TreeWidgetItem *pre=NULL;
     QString tmp[2];
    while(i<s.size())
    {
       // qDebug()<<s[i];
        if(s[i]=='}')//如果遇到右大括号就退出
        {
            check_stack.pop();

            return 0;
        }

        if(s[i]=='\"')//遇到双引号则记录字符串，作为对象名
        {
               int start=++i;
               //qDebug()<<s[i];
                while( i<s.size() &&  s[i] !='\"'){i++;}

                if(i>=s.size()){return 1;}

                tmp[0]=s.mid(start,i-start);

                pre=new TreeWidgetItem(parent,pre);
                pre->setText(0,tmp[0]);


        }

        if(s[i]==':')//遇到冒号存值
        {
            i++;
            while(s[i]==' ')i++;

            if(s[i]=='[')//遇到数组，进入数组的处理
            {
                //solve_middle();
                pre->set_type("array");
                pre->setIcon(0,QIcon("array.png"));
                check_stack.push(s[i]);
               int check= solve_middle(s,pre,i);
               if(check){return check;}
                i++;
            }
            else if(s[i]=='\"')//遇到双引号处理字符串
            {
                int start=++i;
                while(i<s.size() && s[i] !='\"')i++;
                i++;

                if(i>=s.size()){return 1;}

                tmp[1]=s.mid(start,i-start-1);
                pre->setText(1,tmp[1]);
                pre->setIcon(0,QIcon("string.png"));
                pre->set_type("string");
            }
            else if(s[i]=='{')//遇到大括号处理对象
            {
                pre->set_type("object");
                pre->setIcon(0,QIcon("object.png"));

                check_stack.push(s[i]);

               int check= solve_Big(s,pre,i);i++;
               if(check){return check;}
            }
            else if(s[i]>='0' && s[i]<='9')//处理数字 int double
            {
               int start=i;
               bool point=false;
                while((s[i]>='0' && s[i]<='9') || s[i]=='.'){
                    if(s[i]=='.'){point =true;}//包括double
                    i++;
                }
                tmp[1]=s.mid(start,i-start);
                pre->setText(1,tmp[1]);
                pre->setIcon(0,QIcon("integer.png"));

                if(point){pre->set_type("float point"); pre->setIcon(0,QIcon("float point.png"));}
                else{ pre->set_type("integer"); pre->setIcon(0,QIcon("integer.png"));}
            }
            else if(s[i]=='t')//bool类型的true
            {
                QString tmp_true=s.mid(i,4);
                pre->setIcon(0,QIcon("boolean.png"));
                if(tmp_true=="true")
                {
                    tmp[1]=tmp_true;
                    pre->setText(1,tmp[1]);
                }

                pre->set_type("boolean");
            }
            else if(s[i]=='f')//bool类型的false
            {
                QString tmp_false=s.mid(i,5);
                pre->setIcon(0,QIcon("boolean.png"));
                if(tmp_false=="false")
                {
                    tmp[1]=tmp_false;
                    pre->setText(1,tmp[1]);
                }

                pre->set_type("boolean");
            }
        }
        if(s[i]=='}')//右大括号退出
        {
            check_stack.pop();

            return 0;
        }
                i++;
    }
    return 1;
}
//***************创建树形结构
int MainWindow::CreateTree(QString s)
{
    ui->treeWidget->clear();
   TreeWidgetItem *parent=new TreeWidgetItem(ui->treeWidget);
   parent->setText(0,"root");
   parent->setIcon(0,QIcon("object.png"));
   parent->set_type("object");
   int j=0;
   while(s[j]==' ' || s[j]=='\xa' || s[j]==32 || s[j]=='\n' || s[j]=='\t')j++;
   if(s[j]!='{'){QMessageBox::warning(this,"error","miss {before the text");return 1;}
   else{check_stack.push(s[j]);}
   int i=j+1;
   int check=solve_Big(s.mid(j,s.size()-j-1),parent,i);
   //**********check********
   ui->treeWidget->show();
   return 0;
}
//****************跳转界面
void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if(index==1)
    {
       QString s=ui->textEdit->toPlainText();
       qDebug()<<s<<endl;
       CreateTree(s);
    }
}
//***********退出
void MainWindow::on_actionExit_triggered()
{
    if(fileName.size()==0)
    {
       int ret=unsave();
        switch (ret) {
        case QMessageBox::Save:{//询问是否保存
            on_actionSave_triggered();
            close();
            break;
        }
        case QMessageBox::Discard:{//询问是否直接不保存
            close();
        break;
        }
        case QMessageBox::Cancel:{//取消
            break;
        }
        default:
            break;
        }
    }
    else
    {
        save_wirte(fileName);
    }

}
//***********另存为
void MainWindow::on_actionSave_as_triggered()//save as
{
    QFileDialog filedialog;
    fileName=filedialog.getSaveFileName(this,"save","/","JSON file(*.json)");
    qDebug()<<fileName;
     save_wirte(fileName);
}
//**********保存到磁盘
bool MainWindow::save_wirte(QString filename)
{
    QFile file(filename);
    if(file.open(QFile::WriteOnly| QFile::Truncate))
    {
        QTextStream out(&file);
        out<<ui->textEdit->toPlainText();
        file.close();
        return true;
    }
    else
        return false;
}
//**********保存文件
void MainWindow::on_actionSave_triggered()//save
{
    if(fileName.size()==0)
    {
        on_actionSave_as_triggered();
    }
    else
    {
        save_wirte(fileName);
    }
}
//**********新建
void MainWindow::reset()
{
    ui->treeWidget->clear();
    fileName="";
    ui->textEdit->clear();
    ui->textEdit_name->clear();
    ui->textEdit_value->clear();
}
//*********不保存提示
int MainWindow::unsave()
{
    QMessageBox msgbox;
    msgbox.setText("The document has been modified.");
    msgbox.setInformativeText("Do you want to save your changes?");
    msgbox.setStandardButtons(QMessageBox::Save| QMessageBox::Discard | QMessageBox::Cancel);
    msgbox.setDefaultButton(QMessageBox::Save);
    int ret=msgbox.exec();
    return ret;
}
//*************新建文件
void MainWindow::on_actionNew_triggered()
{
    if(fileName.size()==0)
    {
       int ret=unsave();
        switch (ret) {
        case QMessageBox::Save:{//保存后新建
            on_actionSave_triggered();
            //reset;
            reset();
            break;
        }
        case QMessageBox::Discard:{//不保存新建
           //reset
            reset();
        break;
        }
        case QMessageBox::Cancel:{//取消
            break;
        }
        default:
            break;
        }
    }
    else
    {
        save_wirte(fileName);
        //reset
        reset();
    }
}
//*********获取打开文件的内容
void MainWindow::open_data()
{
    QFileDialog filedialog;
     reset();
    fileName=filedialog.getOpenFileName(this,"open","/","JSON file(*.json)");
    qDebug()<<fileName;
     QFile file(fileName);
     if(file.open(QIODevice::ReadOnly| QIODevice::Text))
     {
         QTextStream in(&file);
         ui->textEdit->setPlainText(in.readAll());
         file.close();
     }
}
//**********打开文件按钮，确认是否保存当前或不保存，取消
void MainWindow::on_actionOpen_triggered()
{
    if(fileName.size()==0)
    {
        int ret=unsave();
        switch (ret) {
        case QMessageBox::Save:{//保存
            on_actionSave_triggered();
            open_data();//读入数据
            break;
        }
        case QMessageBox::Discard:{//不保存
            open_data();//读入数据
        break;
        }
        case QMessageBox::Cancel:{//取消
            break;
        }
        default:
            break;
        }
    }
    else
    {
        save_wirte(fileName);
        open_data();
    }
}
//***************改变item的类型
void MainWindow::change_type(QString change)
{
    TreeWidgetItem *cur=(TreeWidgetItem *)ui->treeWidget->currentItem();
    cur->set_type(change);
    QString picture=change+".png";
    cur->setIcon(0,QIcon(picture));//相对应的改变图片类型
}
//************修改item的名字
void MainWindow::change_name()
{
    emit Change_Item(0,ui->textEdit_name->toPlainText());
}
//***********修改item的值
void MainWindow::change_value()
{
    emit Change_Item(1,ui->textEdit_value->toPlainText());
}

void MainWindow::Change_Item(int colum, QString change)
{
    TreeWidgetItem *cur=(TreeWidgetItem *)ui->treeWidget->currentItem();
    if(cur)
    cur->setText(colum,change);
}
//**************树状视图里的鼠标点击信息查看
void MainWindow::on_treeWidget_itemClicked(TreeWidgetItem *item, int column)
{
    if(item){//或取选中的item信息
    ui->textEdit_name->setPlainText(item->text(0));
    ui->textEdit_value->setPlainText(item->text(1));

    ui->comboBox->setCurrentText(item->Get_type());

    if(item->Get_type()=="object" || item->Get_type()=="array")//设置若为object or array 则不显示值
    {
        ui->textEdit_value->setVisible(false);
        ui->label_4->setVisible(false);
    }
    else
    {
        ui->textEdit_value->setVisible(true);
        ui->label_4->setVisible(true);
    }
    }
}
//*********通过正则表达式进行文本的查找，mode表示是向前还是向后查找
bool MainWindow::Find_re(int mode, QString _string)
{
    if(!mode)
    {
        if(_string !=search_string)
        {
            search_string=_string;
            index=0;
        }
        if(index<0){index=0;}
       QRegExp regexp;
       regexp.setPattern(".("+search_string+").");//构建正则表达式
       index=ui->textEdit->toPlainText().indexOf(regexp,index);
       qDebug()<<index<<ui->textEdit->toPlainText().mid(index+1,_string.size());
       if(index>=0){
       QTextCursor cur=ui->textEdit->textCursor();
       cur.setPosition(index+1,QTextCursor::MoveAnchor);
       cur.movePosition(QTextCursor::NoMove,QTextCursor::KeepAnchor,_string.size());
       cur.select(QTextCursor::WordUnderCursor);
       ui->textEdit->setTextCursor(cur);
       index=index+search_string.size();
       }
    }
    else{

       if(_string!=search_string)
       {
           search_string=_string;
           stack.clear();
           do
           {
               QRegExp regexp;
               regexp.setPattern(".("+search_string+").");//构建正则表达式
               index=ui->textEdit->toPlainText().indexOf(regexp,index);
               if(index>=0){stack.push(index);index+=search_string.size();}
           }while(index>=0);
       }
       if(!stack.empty())
       {
       index=stack.top();stack.pop();
       QTextCursor cur=ui->textEdit->textCursor();
       cur.setPosition(index+1,QTextCursor::MoveAnchor);
       cur.movePosition(QTextCursor::NoMove,QTextCursor::KeepAnchor,_string.size());
       cur.select(QTextCursor::WordUnderCursor);
        ui->textEdit->setTextCursor(cur);
       }
    }
    return true;
}
//***********工具栏里的查找界面
void MainWindow::on_actionFind_triggered()
{
   search->show();
}
//************工具栏里的压缩格式
void MainWindow::on_action_triggered()//yasuo
{
    QString compress=ui->textEdit->toPlainText();
    origen=compress;
    int i=0;
   // if(compress[i]=='\n' || compress[i]=='\t' || compress[i]==' ')
     //for(int j=0;j<compress.size();j++){qDebug()<<compress[j];}
    while(i<compress.size())
    {
        qDebug()<<compress[i];
      if(compress[i]=='\"')
      {
          i++;
          while(compress[i]!='\"' )
          {
                 i++;
                if(i>=compress.size())break;
          }
      }
        if(compress[i]=='\n' || compress[i]=='\t' || compress[i]==32 || compress[i]=='\xa ')
        {
            QString tmp=compress;
            compress=compress.mid(0,i);
            QString cut=tmp.mid(i+1,tmp.size()-i-1);
            compress+=cut;
             qDebug()<<compress.size()<<tmp.size();
             qDebug()<<compress[i];
        }
        else
        {
            i++;
        }
    }
     ui->textEdit->setPlainText(compress);
}
//**********压缩之后还原
void MainWindow::on_action_2_triggered()
{
    ui->textEdit->setPlainText(origen);
}
