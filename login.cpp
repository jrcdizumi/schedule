#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <iostream>
#include <QFile>
#include "func/hashmap.h"
#include <QDebug>
#include <QTextStream>
#include <qdir.h>
#include <qstandardpaths.h>
#include <QMouseEvent>
#include <QTimer>
#include <QTextStream>
#include <QStringList>
#include "src/clock.h"
#define number 100
Clock *userclock;
node A;
int i=0;
using namespace std;
HashMap<string>* student=new HashMap<string>(number);
HashMap<string>* administrator=new HashMap<string>(number);
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());    //去窗口边框
    setAttribute(Qt::WA_TranslucentBackground);//把窗口背景设置为透明;
    this->setSizeGripEnabled(true);
    A.hour=10;
    A.num=10086;
    ui->password->setEchoMode(QLineEdit::Password);
    userclock=new Clock();
    if(!initialize())
    {
         qDebug()<<"初始化错误";
    }
    else
    {
          qDebug()<<"初始化成功";
    }
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{




       string s1=ui->username->text().toStdString();
       string s2=ui->password->text().toStdString();
       if(ui->radioButton_2->isChecked())
       {
           if(s1==""||s2=="")
           {
              QMessageBox::warning(this,tr("登录失败"),tr("请输入账号密码"),QMessageBox::Ok);
               if(s1=="")
              ui->username->setFocus();
               else
                ui->password->setFocus();
           }
           else
           {
               /*
               if(student->get(s1)==s2)
               {
                  emit sendData(student);
                   newwindow->show();
                  newwindow->flag=1;
                   this->hide();
               }
*/
               if(Strie.search(s1)==s2)
               {
                newwindow=new MainWindow();
                 connect(newwindow,SIGNAL(ExitWin()),this,SLOT(show()));
                connect(this,SIGNAL(sendData(HashMap<string>*)),newwindow,SLOT(getData(HashMap<string>*)));
                emit sendData(student);
                newwindow->show();
                this->hide();
               }
               else
               {
                   QMessageBox::warning(this,tr("登录失败"),tr("用户名或密码输入错误！"),QMessageBox::Ok);
                   ui->password->clear();
                   ui->password->setFocus();

               }
            }
       }
       else if(ui->radioButton->isChecked())
       {
           if(s1==""||s2=="")
           {
               QMessageBox::warning(this,tr("登录失败"),tr("请输入账号密码"),QMessageBox::Ok);
           }
           else
           {
               if(Atrie.search(s1)==s2)
               {
                   newwindow=new MainWindow();
                   connect(newwindow,SIGNAL(ExitWin()),this,SLOT(show()));
                   connect(this,SIGNAL(sendData(HashMap<string>*)),newwindow,SLOT(getData(HashMap<string>*)));
                   emit sendData(administrator);
                   newwindow->show();
                   this->hide();
               }
               else
               {
                   QMessageBox::warning(this,tr("登录失败"),tr("用户名或密码输入错误！"),QMessageBox::Ok);
                   ui->password->clear();
                   ui->username->setFocus();

               }
           }
        }
       else
       {
           QMessageBox::warning(this,tr("wrong"),tr("请选择身份"),QMessageBox::Ok);
       }
}

void login::timerEvent(QTimerEvent *event)
{
       if(event->timerId()==time_id)
      qDebug() << i++;
}
bool login::initialize(void)
{
       QFile newfile("../schedule/data/user.bin");
       //处理学生账号密码
       if (newfile.open(QIODevice::ReadOnly)) {
           QTextStream stream(&newfile);
           while (!stream.atEnd()) {
            QString line = stream.readLine();
            QStringList parts = line.split(" "); // 以空格分隔账号和密码
            QString account = parts[0];
            QString password = parts[1];
            // 处理账号和密码
            qDebug()<<account<<" "<<password;
            Strie.insert(account.toStdString(),password.toStdString());
           }
           newfile.close();
        }
       else{qDebug()<<"文件打开失败";}
       newfile.close();
        //处理管理员账号密码
        newfile.setFileName("../schedule/data/admin.bin");
        if (newfile.open(QIODevice::ReadOnly)) {
           QTextStream stream(&newfile);
           while (!stream.atEnd()) {
            QString line = stream.readLine();
            QStringList parts = line.split(" "); // 以空格分隔账号和密码
            QString account = parts[0];
            QString password = parts[1];
            // 处理账号和密码
            qDebug()<<account<<" "<<password;
            Atrie.insert(account.toStdString(),password.toStdString());
           }
           newfile.close();
        }
        else{qDebug()<<"文件打开失败";}
        newfile.close();
       return 1;
}

void login::on_toolButton_clicked()
{
       close();
}


void login::on_toolButton_2_clicked()
{
    showMinimized();
}

//拖拽操作
void login::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
           m_bDrag = true;
           //获得鼠标的初始位置
           mouseStartPoint = event->globalPos();
           //mouseStartPoint = event->pos();
           //获得窗口的初始位置
           windowTopLeftPoint = this->frameGeometry().topLeft();
    }
}

void login::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bDrag)
    {
           //获得鼠标移动的距离
           QPoint distance = event->globalPos() - mouseStartPoint;
           //QPoint distance = event->pos() - mouseStartPoint;
           //改变窗口的位置
           this->move(windowTopLeftPoint + distance);
    }
}

void login::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
           m_bDrag = false;
    }
}

void login::on_pushButton_2_clicked()
{
    if(signup!=NULL)
    {
           delete signup;
           qDebug()<<"删除signup成功";
    }
    signup=new registered();
    connect(signup,SIGNAL(ExitWin()),this,SLOT(show()));
    connect(this,SIGNAL(sendData2(UserTrie*)),signup,SLOT(getData(UserTrie*)));
    emit sendData2(&this->Strie);
    this->hide();
    signup->show();
}

