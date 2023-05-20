#ifndef COURSE_INFO_H
#define COURSE_INFO_H
#include <QRadioButton>
#include <QDialog>
#include "reminder.h"
#include <QCloseEvent>
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
    bool isChecked;
    QRadioButton* getButton();
    void closeEvent(QCloseEvent *);

private slots:
    void on_ok_button_clicked();
    void on_cancel_button_clicked();
    void on_radioButton_clicked();

private:
    Ui::course_info *ui;

protected:

};

#endif // COURSE_INFO_H
