#ifndef ADD_CLASS_H
#define ADD_CLASS_H

#include <QWidget>

namespace Ui {
class add_class;
}

class add_class : public QWidget
{
    Q_OBJECT

public:
    explicit add_class(QWidget *parent = nullptr);
    ~add_class();

private:
    Ui::add_class *ui;
};

#endif // ADD_CLASS_H
