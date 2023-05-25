#include "admin.h"
#include "ui_admin.h"

admin::admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
}

admin::~admin()
{
    delete ui;
}

void admin::on_pushButton_2_clicked()
{
    if(ac==nullptr){
        ac=new add_class();
    }
    else{
        delete ac;
        ac=new add_class();
    }
    ac->show();
}

void admin::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit ExitWin();
    this->deleteLater();
}
void admin::on_pushButton_clicked()
{

}

