#ifndef LOGIN_H
#define LOGIN_H
#include "registered.h"
#include <QDialog>
#include "func/hashmap.h"
#include "func/usertrie.h"
#include <QTimerEvent>
#include <QTimer>
#include "mainwindow.h"
#include "admin.h"
extern UserTrie Strie;

struct node
{
    int num;
    int hour=10;
};
struct User{
    bool exist;
    string password;
};

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    bool initialize(void);
    int time_id;
    UserTrie Atrie;
protected:
    //拖拽窗口
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void sendData(HashMap<string>* data);//发送数据的信号，不需要实体函数，在头文件定义就可以
    void sendData2(UserTrie*);//发数据给注册页面，以免重复注册

private slots:
    void on_pushButton_clicked();
    void on_toolButton_clicked();   //关闭窗口
    void on_toolButton_2_clicked(); //最小化

    void on_pushButton_2_clicked();

private:
    Ui::login *ui;
    MainWindow *newwindow;
    admin *newadmin;
    registered* signup=NULL;//=new registered();
    bool        m_bDrag;
    QPoint      mouseStartPoint;
    QPoint      windowTopLeftPoint;
    int tot_id;

};

#endif // LOGIN_H
