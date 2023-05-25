#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include "add_class.h"
#include <QCloseEvent>

namespace Ui {
class admin;
}

class admin : public QWidget
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();

private slots:
    void on_pushButton_2_clicked();
    void closeEvent(QCloseEvent *event);
    void on_pushButton_clicked();

signals:
    void ExitWin();

private:
    Ui::admin *ui;
    add_class *ac=new add_class();

};

#endif // ADMIN_H
