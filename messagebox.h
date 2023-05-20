#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QDialog>

namespace Ui {
class messagebox;
}

class messagebox : public QDialog
{
    Q_OBJECT

public:
    explicit messagebox(QWidget *parent = nullptr);
    ~messagebox();

    void setMessage(const QString& message);
    void closeEvent(QCloseEvent *);

private slots:
    void on_okButton_clicked();

private:
    Ui::messagebox *ui;
signals:
    void windowClosed();
};

#endif // MESSAGEBOX_H
