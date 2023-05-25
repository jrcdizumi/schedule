#include "add_class.h"
#include "ui_add_class.h"
#include <QMessageBox>


add_class::add_class(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_class)
{
    ui->setupUi(this);
    this->setFixedSize(673,424);
    if(!is_admin){
        ui->radioButton_17->setEnabled(0);
        ui->radioButton_18->setEnabled(1);
        ui->radioButton_19->setEnabled(1);
    }
    else{
        ui->radioButton_17->setEnabled(1);
        ui->radioButton_18->setEnabled(0);
        ui->radioButton_19->setEnabled(0);
    }
    button_kind=new QButtonGroup();
    button_kind->addButton(ui->radioButton_17);
    button_kind->addButton(ui->radioButton_18);
    button_kind->addButton(ui->radioButton_19);
}

add_class::~add_class()
{
    delete ui;
}

void add_class::on_pushButton_clicked()
{
    QString qstr = ui->lineEdit->text();
    std::string name=qstr.toStdString();
    qstr=ui->lineEdit_2->text();
    std::string location=qstr.toStdString();
    qstr=ui->lineEdit_3->text();
    std::string exam_time=qstr.toStdString();
    qstr=ui->lineEdit_4->text();
    std::string exam_location=qstr.toStdString();
    int day=ui->spinBox_3->value();
    int start_time=ui->spinBox->value();
    int end_time=ui->spinBox_2->value();
    int kind=0;
    if(ui->radioButton_17->isChecked())kind=0;
    else if(ui->radioButton_18->isChecked())kind=1;
    else if(ui->radioButton_19->isChecked())kind=2;
    Vector<int> student;
    QString text = ui->plainTextEdit->toPlainText();
    QTextStream in(&text);
    while (!in.atEnd()) {
        QString line = in.readLine();
        int tmp_id=Strie.search_id(line.toStdString());
        if(tmp_id!=0)student.push_back(tmp_id);
    }
    bool week[17];
    for(int i=0;i<=16;i++)week[i]=0;
    if(ui->checkBox->isChecked())week[1]=1;
    if(ui->checkBox_2->isChecked())week[2]=1;
    if(ui->checkBox_3->isChecked())week[3]=1;
    if(ui->checkBox_4->isChecked())week[4]=1;
    if(ui->checkBox_5->isChecked())week[5]=1;
    if(ui->checkBox_6->isChecked())week[6]=1;
    if(ui->checkBox_7->isChecked())week[7]=1;
    if(ui->checkBox_8->isChecked())week[8]=1;
    if(ui->checkBox_9->isChecked())week[9]=1;
    if(ui->checkBox_10->isChecked())week[10]=1;
    if(ui->checkBox_11->isChecked())week[11]=1;
    if(ui->checkBox_12->isChecked())week[12]=1;
    if(ui->checkBox_13->isChecked())week[13]=1;
    if(ui->checkBox_14->isChecked())week[14]=1;
    if(ui->checkBox_15->isChecked())week[15]=1;
    if(ui->checkBox_16->isChecked())week[16]=1;
    if(!schedule.add_affairs(Affairslist.add_affairs(kind,name,day,start_time,end_time,location,exam_time,exam_location,week,student))){
        Affairslist.list[Affairslist.list.getSize()-1].kind=3;
        QMessageBox::warning(this, "警告", "有冲突，添加/修改失败");
    }
    else{
        QMessageBox::information(this, "success", "添加成功");
    }
}


void add_class::on_spinBox_valueChanged(int arg1)
{
    if(ui->spinBox_2->value()<=arg1)ui->spinBox_2->setValue(arg1+1);
    if(ui->radioButton_17->isChecked()&&ui->spinBox_2->value()-arg1>3)ui->spinBox_2->setValue(arg1+3);
    else if(!ui->radioButton_17->isChecked()&&ui->spinBox_2->value()-arg1>1)ui->spinBox_2->setValue(arg1+1);
}


void add_class::on_spinBox_2_valueChanged(int arg1)
{
    if(ui->spinBox->value()>=arg1)ui->spinBox->setValue(arg1-1);
    if(ui->radioButton_17->isChecked()&&arg1-ui->spinBox->value()>3)ui->spinBox->setValue(arg1-3);
    else if(!ui->radioButton_17->isChecked()&&arg1-ui->spinBox->value()>1)ui->spinBox->setValue(arg1-1);
}

