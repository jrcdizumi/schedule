#ifndef ADD_CLASS_H
#define ADD_CLASS_H

#include <QWidget>
#include <QString>
#include <string>
#include <QGroupBox>
#include <QRadioButton>
#include <QButtonGroup>
#include "func/vector.h"
#include "src/affairslist.h"
#include "src/schedule.h"
#include <QPlainTextEdit>
#include <QTextStream>
#include "func/usertrie.h"
extern UserTrie Strie;
extern bool is_admin;
extern affairslist Affairslist;
extern Schedule schedule;
namespace Ui {
class add_class;
}

class add_class : public QWidget
{
    Q_OBJECT

public:
    explicit add_class(QWidget *parent = nullptr);
    ~add_class();
    void update_class(int a);

private slots:
    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

private:
    Ui::add_class *ui;
    QButtonGroup *button_kind;
};

#endif // ADD_CLASS_H
