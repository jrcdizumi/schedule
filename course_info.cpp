#include "course_info.h"
#include "ui_course_info.h"

course_info::course_info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::course_info)
{
    ui->setupUi(this);
}

course_info::~course_info()
{
    delete ui;
}

void course_info::setName(const QString &name)
{
    ui->name->setText(name);
}

void course_info::setTeacher(const QString &teacher)
{
    ui->teacher->setText(teacher);
}

void course_info::setClassTime(const QString &classTime)
{
    ui->class_time->setText(classTime);
}

void course_info::setExamTime(const QString &examTime)
{
    ui->exam_time->setText(examTime);
}

void course_info::setLocation(const QString &location)
{
    ui->location->setText(location);
}
void course_info::setExamLocation(const QString &location)
{
    ui->Exam_Location->setText(location);
}

void course_info::set_affair(int a){
    affairs b=Affairslist.list[a];
    thisaffair=a;
    //qDebug()<<QString::fromStdString(b.name)<<" "<<QString::number(b.day);
    setName(QString::fromStdString(b.name));
    if(b.kind==0)setTeacher("课程");
    else if(b.kind==1)setTeacher("活动");
    else if(b.kind==2)setTeacher("临时事务");
    setClassTime("周"+QString::number(b.day)+"第"+QString::number(b.start_time)+"节到"+QString::number(b.end_time)+"节");
    setExamTime(QString::fromStdString(b.exam_time));
    setLocation(QString::fromStdString(b.exam_location));
    setExamLocation(QString::fromStdString(b.exam_location));
    if(b.exam_time!=""){
        getButton()->setCheckable(true);
        getButton()->setChecked(true);
    }
    else{
        getButton()->setCheckable(true);
        getButton()->setChecked(false);
    }
    if(b.kind==0){
        getButton()->setCheckable(true);
        getButton()->setChecked(true);
        getButton()->setEnabled(false);
    }
}

void course_info::on_ok_button_clicked()
{

    if(qg==nullptr){
        qg=new Qguide();
    }
    else{
        delete qg;
        qg=new Qguide();
    }
    qg->show();
}

void course_info::on_cancel_button_clicked()
{
    reject();
}

void course_info::on_radioButton_clicked()
{
    if(this->ui->radioButton->isChecked()){
        if(Affairslist.list[thisaffair].exam_time=="")Affairslist.list[thisaffair].exam_time=" ";
    }
    else{
        Affairslist.list[thisaffair].exam_time="";
    }
}
QRadioButton* course_info::getButton()
{
    return this->ui->radioButton;
}
void course_info::closeEvent(QCloseEvent *event){
    event->accept();
}

void course_info::on_ok_button_2_clicked()
{

}

