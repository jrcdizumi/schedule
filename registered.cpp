#include "registered.h"
#include "ui_registered.h"
#include <QCloseEvent>
#include <QMessageBox>
#include <QFile>
#include <QString>
#include <QTextStream>
UserTrie* userdata;
registered::registered(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registered)
{
    ui->setupUi(this);
    qDebug()<<"注册执行";


}

registered::~registered()
{
    delete ui;
}

void registered::closeEvent(QCloseEvent *)
{
    emit ExitWin();
}
void registered::getData(UserTrie* data)
{

    userdata=data;
}

void registered::on_signup_clicked()
{
    string userName=ui->username->text().toStdString();
    string passWord=ui->password->text().toStdString();
    string passWordCheck=ui->passwordcheck->text().toStdString();
    if(userName=="")
    {
         QMessageBox::warning(this,tr("注册失败"),tr("请输入用户名"),QMessageBox::Ok);
    }
    else
    {
         if(passWord=="")
         {
             QMessageBox::warning(this,tr("注册失败"),tr("请输入密码"),QMessageBox::Ok);
         }
         else
         {
             if(passWordCheck=="")
             {
                 QMessageBox::warning(this,tr("注册失败"),tr("请输入确认密码"),QMessageBox::Ok);
             }
             else
             {
                 if(passWord!=passWordCheck)
                 {
                     QMessageBox::warning(this,tr("注册失败"),tr("两次密码输入不一致"),QMessageBox::Ok);
                 }
                 else
                 {
                     int usernamelen=userName.length();
                     for(int i=0;i<usernamelen;i++)
                     {
                         if(userName.at(i)<='9'&&userName.at(i)>='0')
                             continue;
                         QMessageBox::warning(this,tr("注册失败"),tr("账号应只含数字"),QMessageBox::Ok);
                         return;
                     }
                     if(userdata->search(userName)=="")
                     {

                         QFile file("../schedule/data/user.bin");
                         if(!file.open(QIODevice::Append))
                         {
                             qDebug()<<"文件打开失败";
                              QMessageBox::warning(this,tr("注册失败"),tr("程序出现错误"),QMessageBox::Ok);
                         }
                         else
                         {

                             QTextStream out(&file);
                              out<<'\n'<<ui->username->text()<<" "<<ui->password->text();
                            userdata->insert(userName,passWord);
                            QMessageBox::warning(this,tr("注册成功"),tr("成功注册"),QMessageBox::Ok);
                            this->close();
                            ui->password->clear();
                            ui->passwordcheck->clear();
                            ui->username->clear();
                            ExitWin();
                         }
                     }
                    else
                     {
                        QMessageBox::warning(this,tr("注册失败"),tr("该用户已存在"),QMessageBox::Ok);
                     }
                 }
             }
         }
    }
}

