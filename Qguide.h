#ifndef QGUIDE_H
#define QGUIDE_H

#include <QPalette>
#include "func/vector.h"
#include "guide/map.h"
#include <QBrush>
#include "guide/guide.h"
#include "func/hashmap.h"
#include <QWidget>
#include <QApplication>
#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
#include <qpixmap.h>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QLine>
#include <QCompleter>
#include <QTextCursor>
#include <QMessageBox>
#include <QRect>
#include "ui_qguide.h"
#include <QAbstractItemView>
#include <QGraphicsOpacityEffect>

QT_BEGIN_NAMESPACE
namespace Ui { class Qguide; }
QT_END_NAMESPACE

class Qguide : public QWidget{
    Q_OBJECT
private:
    Ui::Qguide *ui;
    const int R = 4;
    const int tot_node=115;
    const int tot_edge=147;
    struct node{
        QPointF point;
        int id;
        bool f;
        node(){};
        node(QPointF a,int i,bool f):point(a),id(i),f(f){};
        void operator = (const node &b){
            point=b.point;
            id=b.id;
            return ;
        }
    };
    class MyCompleter : public QCompleter
    {
        public:
            using QCompleter::QCompleter; // Inherit constructors from base class

        protected:
            virtual bool eventFilter(QObject* obj, QEvent* evt) override
            {
                /*if (evt->type() == QEvent::KeyPress)
                {
                    auto keyEvent = static_cast<QKeyEvent*>(evt);
                    if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
                    {
                        return false; // Do not handle Enter/Return key
                    }
                }*/
                // Handle all other events normally
                return QCompleter::eventFilter(obj, evt);
            }
    };


    QPixmap pixma;
    QStringList location;
    QVector<node> ps;
    QVector<int> pss;
    QImage img;
    QPalette pal;
    MyCompleter *filter;
    //QGraphicsOpacityEffect *tt;

    int pathid;
    Vector<Vector<edge>> schoolmap;
    Vector<edge> path;
    bool choice;
    bool mindis;
    int start;
    Vector<int> endpoint;
    Vector<string> IdtoName;

    QPointF mapTo(const QPixmap &pixmap, const QPoint &pos) const;

    void drawpath(edge &a);

    void init();

    void clear();

    void add_endediter();

    bool changestartpoint(int &tmp);

    void drawstartpoint(QPointF &p);

    void drawendpoint(QPointF &p);

public:
    HashMap<int> idcheck;
    explicit Qguide(QWidget *parent = nullptr);
    ~Qguide();
    void clear_endpoint();
    bool add_endpoint(int &tid);
    bool add_endpoint(Vector<int> &tid);
protected:
    //void mousePressEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *obj,QEvent *event ) override;



private slots:
    void on_start_edit_textEdited(const QString &arg1);
    void on_start_edit_editingFinished();
    void on_startbutton_toggled(bool checked);
    void on_endbutton_toggled(bool checked);
    void on_accuary_toggled(bool checked);
    void on_SA_toggled(bool checked);
    void on_nextButton_clicked();
    void on_callButton_clicked();
    void on_clearButton_clicked();
    void on_end_edit_editingFinished();
    void on_SetofEnd_textChanged();
    void getactivited();
    void on_end_edit_textChanged(const QString &arg1);
    void on_end_edit_returnPressed();
};
#endif // QGUIDE_H
