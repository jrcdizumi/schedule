#include "mainwindow.h"
#include <QLayout>
#include <QMessageBox>
#include "src/affairslist.h"
#include "src/schedule.h"
#include "course_info.h"
#include "src/clock.h"
#include "messagebox.h"
extern affairslist Affairslist;
extern Schedule schedule;
extern int now_user;
extern int now_week;
extern Clock* userclock;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    now_week=userclock->week();
    week_on_screen=now_week;
    m_tableWidget = new QTableWidget(16, 7, this);
    setCentralWidget(m_tableWidget);
    QStringList horizontalLabels = {"Mon", "Tue", "Wed",  "Thu", "Fri", "Sat", "Sun"};
    // 设置垂直表头标签
    QStringList verticalLabels;
    for (int i = 0; i < 16; i++) {
        QString label = QString("%1\n%2:00-%2:59").arg(i+1).arg(i+6);
        verticalLabels.append(label);
    }
    m_tableWidget->setVerticalHeaderLabels(verticalLabels);
    m_tableWidget->setHorizontalHeaderLabels(horizontalLabels);
    reloadTable();
    m_tableWidget->resizeColumnsToContents();
    connect(m_tableWidget, &QTableWidget::cellClicked, this, &MainWindow::on_m_tableWidget_cellClicked);
    pushButton = new QPushButton("Search(name)", this);
    connect(pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    pushButton_9 = new QPushButton("Search(time)", this);
    connect(pushButton_9, &QPushButton::clicked, this, &MainWindow::on_pushButton_9_clicked);
    pushButton_2 = new QPushButton("NAV", this);
    connect(pushButton_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked);
    pushButton_3 = new QPushButton("Add", this);
    connect(pushButton_3, &QPushButton::clicked, this, &MainWindow::on_pushButton_3_clicked);
    pushButton_4 = new QPushButton("Time_go", this);
    connect(pushButton_4, &QPushButton::clicked, this, &MainWindow::on_pushButton_4_clicked);
    pushButton_5 = new QPushButton("Time_stop", this);
    connect(pushButton_5, &QPushButton::clicked, this, &MainWindow::on_pushButton_5_clicked);
    pushButton_6 = new QPushButton("Time_speedup", this);
    connect(pushButton_6, &QPushButton::clicked, this, &MainWindow::on_pushButton_6_clicked);
    pushButton_7 = new QPushButton("Upd_Week", this);
    connect(pushButton_7, &QPushButton::clicked, this, &MainWindow::on_pushButton_7_clicked);
    pushButton_8 = new QPushButton("Time_speeddown", this);
    connect(pushButton_8, &QPushButton::clicked, this, &MainWindow::on_pushButton_8_clicked);
    spinbox_1=new QSpinBox(this);
    spinbox_1->setRange(1, 16); // 设置最小值和最大值
    spinbox_1->setSingleStep(1);
    spinbox_1->setValue(now_week);
    connect(spinbox_1, SIGNAL(valueChanged(int)), this, SLOT(on_spinbox_value_changed(int)));
    connect(userclock,SIGNAL(weekChanged(int)),this,SLOT(week_changed()));
    userclock->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_m_tableWidget_cellClicked(int row, int column)
{
    QTableWidgetItem *item = m_tableWidget->item(row, column);
    if (item->text()!=" ") {
        if(ci==nullptr){
            ci=new course_info();
        }
        else{
            delete ci;
            ci=new course_info();
        }
        ci->set_affair(schedule.all_list[now_user].timetable[week_on_screen][column+1][row+6][0]);
        if(Affairslist.list[schedule.all_list[now_user].timetable[week_on_screen][column+1][row+6][0]].kind==2){
            QString qstr="",qstr2="";
            for(int i=0;i<schedule.all_list[now_user].timetable[week_on_screen][column+1][row+6].size();i++){
                qstr+=QString::fromStdString(Affairslist.list[schedule.all_list[now_user].timetable[week_on_screen][column+1][row+6][i]].name);
                qstr2+=QString::fromStdString(Affairslist.list[schedule.all_list[now_user].timetable[week_on_screen][column+1][row+6][i]].location);
                qstr+=" ";
                qstr2+=" ";
            }
            ci->setName(qstr);
            ci->setLocation(qstr2);
        }
        ci->show();
    }
}
void MainWindow::reloadTable()
{
    for (int row = 0; row < 16; ++row) {
        for (int column = 0; column < 7; ++column) {
            if(!schedule.all_list[now_user].timetable[week_on_screen][column+1][row+6].empty()&&Affairslist.list[schedule.all_list[now_user].timetable[week_on_screen][column+1][row+6][0]].kind!=3){
            QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(Affairslist.list[schedule.all_list[now_user].timetable[week_on_screen][column+1][row+6][0]].name));
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            m_tableWidget->setItem(row, column, item);
        }
        else{
            QTableWidgetItem *item = new QTableWidgetItem(QString(" "));
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            m_tableWidget->setItem(row, column, item);
        }
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(sw==nullptr){
        sw=new SearchWindow();
    }
    else{
        delete sw;
        sw=new SearchWindow();
    }
    sw->show();
}
void MainWindow::on_pushButton_9_clicked()
{
    if(sw2==nullptr){
        sw2=new SearchWindow2();
    }
    else{
        delete sw2;
        sw2=new SearchWindow2();
    }
    sw2->show();
}

void MainWindow::on_pushButton_2_clicked()
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
void MainWindow::on_pushButton_3_clicked()
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
void MainWindow::on_pushButton_4_clicked()
{
    userclock->start();
}
void MainWindow::on_pushButton_5_clicked()
{
    userclock->pause();
}
void MainWindow::on_pushButton_6_clicked()
{
    userclock->setSpeed(userclock->m_speed+1);
}
void MainWindow::on_pushButton_7_clicked()
{
    week_on_screen=spinbox_1->value();
    reloadTable();
}
void MainWindow::on_pushButton_8_clicked()
{
    userclock->setSpeed(userclock->m_speed-1);
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit ExitWin();
    if(userclock->isBoxshow)
    userclock->myclock->close();
    userclock->pause();
    userclock->saveTime();
    if(ci!=nullptr)delete ci;
    if(sw!=nullptr)delete sw;
    if(ac!=nullptr)delete ac;
    this->deleteLater();
}
void MainWindow::on_spinbox_value_changed(int value){
    week_on_screen=spinbox_1->value();
    reloadTable();
}
void MainWindow::week_changed(){
    now_week=userclock->week();
    week_on_screen=now_week;
    spinbox_1->setValue(now_week);
    reloadTable();
}

