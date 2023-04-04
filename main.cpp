#include "mainwindow.h"
#include "src/affairslist.h"
#include "src/func/vector.h"
#include <iostream>
#include <QApplication>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication b(argc, argv);
    MainWindow w;
    w.show();
    affairslist a;
    int week[17]={0};
    Vector<string> student;
    student.push_back("2018010101");
    student.push_back("2018010102");
    a.add_affairs(1,"test",1,1,2,"test","test","test",week,student);
    Vector<affairs> result=a.search_affairs(1,"test","2018010101");
    for(int i=0;i<result.getSize();i++){
        cout<<result[i].kind<<endl;
        cout<<result[i].name<<endl;
        cout<<result[i].day<<endl;
        cout<<result[i].start_time<<endl;
        cout<<result[i].end_time<<endl;
        cout<<result[i].location<<endl;
        cout<<result[i].exam_time<<endl;
        cout<<result[i].exam_location<<endl;
        for(int j=0;j<17;j++)cout<<result[i].week[j]<<" ";
        cout<<endl;
        for(int j=0;j<result[i].student.getSize();j++)cout<<result[i].student[j]<<" ";
        cout<<endl;
    }
    return b.exec();
}
