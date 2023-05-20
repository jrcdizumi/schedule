#ifndef REMINDER_H
#define REMINDER_H

#include <QDialog>

namespace Ui {
class reminder;
}

class reminder : public QDialog
{
    Q_OBJECT

public:
    explicit reminder(QWidget *parent = nullptr);
    ~reminder();

private slots:
    void on_okButton_clicked();

private:
    Ui::reminder *ui;
};

#endif // REMINDER_H
