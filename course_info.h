#ifndef COURSE_INFO_H
#define COURSE_INFO_H
#include <QRadioButton>
#include <QDialog>
#include "reminder.h"
#include <QCloseEvent>
#include "src/affairslist.h"
#include "add_class.h"
#include "Qguide.h"
#include "func/vector.h"
extern affairslist Affairslist;
extern int now_user;
extern bool is_admin;
namespace Ui {
class course_info;
}

class course_info : public QDialog
{
    Q_OBJECT

public:
    explicit course_info(QWidget *parent = nullptr);
    ~course_info();

    void setName(const QString &name);
    void setTeacher(const QString &teacher);
    void setClassTime(const QString &classTime);
    void setExamTime(const QString &examTime);
    void setLocation(const QString &location);
    void setExamLocation(const QString &location);
    void set_affair(int a);
    bool isChecked;
    QRadioButton* getButton();
    void closeEvent(QCloseEvent *);

private slots:
    void on_ok_button_clicked();
    void on_cancel_button_clicked();
    void on_radioButton_clicked();

    void on_ok_button_2_clicked();

private:
    Ui::course_info *ui;
    int thisaffair=0;
    add_class *ac=new add_class();
    Qguide *qg=new Qguide();

protected:

};

#endif // COURSE_INFO_H
