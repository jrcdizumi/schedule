// MainWindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "ui_MainWindow.h"
#include "searchwindow.h"
#include "QSpinBox"
#include "add_class.h"
#include "searchwindow2.h"
#include "Qguide.h"

class QTableWidget; // 前向声明

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void resizeEvent(QResizeEvent *event) override
    {
        QWidget::resizeEvent(event);
        m_tableWidget->horizontalHeader()->setDefaultSectionSize(this->m_tableWidget->width()/9);
        m_tableWidget->verticalHeader()->setDefaultSectionSize(this->m_tableWidget->height()/16.4);
        pushButton->setGeometry(width()-width()/8, height()/40, width()/10, height()/30);
        pushButton_9->setGeometry(width()-width()/8, height()/17, width()/10, height()/30);
        pushButton_2->setGeometry(width()-width()/8, height()/10, width()/10, height()/30);
        pushButton_3->setGeometry(width()-width()/8, height()/7, width()/10, height()/30);
        pushButton_4->setGeometry(width()-width()/8, height()/4, width()/10, height()/30);
        pushButton_5->setGeometry(width()-width()/8, height()/3, width()/10, height()/30);
        pushButton_6->setGeometry(width()-width()/8, height()/2, width()/10, height()/30);
        pushButton_7->setGeometry(width()-width()/8, height()/1.3, width()/10, height()/30);
        pushButton_8->setGeometry(width()-width()/8, height()/2.2, width()/10, height()/30);
        spinbox_1->setGeometry(width()-width()/8, height()/1.5, width()/10, height()/30);
    }
    int week_on_screen;

signals:
    void ExitWin();//新建一个信号槽

private slots:
    void on_m_tableWidget_cellClicked(int row, int column);
    void reloadTable();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void closeEvent(QCloseEvent *event);
    void on_spinbox_value_changed(int value);
    void week_changed();

private:
    Ui::MainWindow *ui;
    QTableWidget *m_tableWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QSpinBox *spinbox_1;
    course_info *ci=new course_info();
    SearchWindow *sw=new SearchWindow();
    add_class *ac=new add_class();
    SearchWindow2 *sw2=new SearchWindow2();
    Qguide *qg=new Qguide();
};

#endif // MAINWINDOW_H
