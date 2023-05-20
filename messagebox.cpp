#include "messagebox.h"
#include "ui_messagebox.h"
#include <QCloseEvent>
messagebox::messagebox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::messagebox)
{
    ui->setupUi(this);
    setWindowModality(Qt::NonModal);
    move(100, 100);
    setFixedSize(200, 200);
    setWindowTitle("闹钟");
    this->ui->messageLabel->setAlignment(Qt::AlignCenter);
}

messagebox::~messagebox()
{
    delete ui;
}

void messagebox::setMessage(const QString& message)
{
    ui->messageLabel->setText(message);
}

void messagebox::closeEvent(QCloseEvent *event)
{

    event->accept();
    emit windowClosed();
    this->deleteLater();
}

void messagebox::on_okButton_clicked()
{
    this->close();
}

