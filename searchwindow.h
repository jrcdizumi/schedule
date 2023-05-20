#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H
#include "ui_searchwindow.h"
#include <QWidget>
#include <QtSql/QSqlQueryModel>
#include <QStandardItemModel>
#include "course_info.h"
#include <QHeaderView>
#include <QTableView>
#include <QResizeEvent>
#include <QComboBox>
namespace Ui {
class SearchWindow;
}

class SearchWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = nullptr);
    void change(QString s,QString t);
    ~SearchWindow();
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



    void on_lineEdit_returnPressed();

private:
    Ui::SearchWindow *ui;
    QStandardItemModel *m_model;
    QStringList m_fruits;
    QComboBox* comboBox = new QComboBox();
};

#endif // SEARCHWINDOW_H
