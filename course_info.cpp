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


void course_info::on_ok_button_clicked()
{
    this->close();
    reminder* AAA=new reminder();
    AAA->show();
}

void course_info::on_cancel_button_clicked()
{
    reject();
}

void course_info::on_radioButton_clicked()
{
    if(this->ui->radioButton->isChecked())
    {
        qDebug()<<"成功设置闹钟";
    }
    else
    {

    }
}
QRadioButton* course_info::getButton()
{
    return this->ui->radioButton;
}
void course_info::closeEvent(QCloseEvent *event){
    event->accept();
}
