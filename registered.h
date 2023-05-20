#ifndef REGISTERED_H
#define REGISTERED_H
#include "func/usertrie.h"
#include <QWidget>
#include <QCloseEvent>
#include <string>
namespace Ui {
class registered;
}

class registered : public QWidget
{
    Q_OBJECT

public:
      int test=111;
    explicit registered(QWidget *parent = nullptr);
    ~registered();

signals:
    void ExitWin();//新建一个信号槽
private slots:
    void getData(UserTrie* student);//得到数据的槽函数
    void on_signup_clicked();

private:
    Ui::registered *ui;
     void closeEvent(QCloseEvent *event);
};

#endif // REGISTERED_H
