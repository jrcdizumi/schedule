#include "reminder.h"
#include "ui_reminder.h"
#include <QMessageBox>

reminder::reminder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reminder)
{
    ui->setupUi(this);
    setWindowModality(Qt::NonModal);
}

reminder::~reminder()
{
    delete ui;
}

void reminder::on_okButton_clicked()
{
    QString reminderText = ui->reminderLineEdit->text();
    QMessageBox::information(this, "reminder", "Reminder set for: " + reminderText);
    close();
}
