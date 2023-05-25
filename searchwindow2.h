#ifndef SEARCHWINDOW2_H
#define SEARCHWINDOW2_H
#include "ui_searchwindow2.h"
#include <QWidget>
#include <QtSql/QSqlQueryModel>
#include <QStandardItemModel>
#include "course_info.h"
#include <QHeaderView>
#include <QTableView>
#include <QResizeEvent>
#include <QComboBox>
#include "func/vector.h"
namespace Ui {
class SearchWindow2;
}

class SearchWindow2 : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWindow2(QWidget *parent = nullptr);
    void change(QString s,QString t);
    ~SearchWindow2();
    void resizeEvent(QResizeEvent *event) override
    {
        QWidget::resizeEvent(event);
        ui-> tableView->horizontalHeader()->setDefaultSectionSize(this->ui->tableView->width());
        ui->tableView->verticalHeader()->setDefaultSectionSize(this->ui->tableView->height()/5);
        // 在窗口放大时输出新的窗口大小
        qDebug() << "New size:" << event->size();

    }
    void closeEvent(QCloseEvent *);

private slots:
    void on_searchButton_clicked();


    void on_spinBox_3_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

private:
    Ui::SearchWindow2 *ui;
    QStandardItemModel *m_model;
    QStringList m_fruits;
    QComboBox* comboBox = new QComboBox();
    Vector<int> a;
};

#endif // SEARCHWINDOW2_H
