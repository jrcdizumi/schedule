#include "mainwindow.h"
#include "src/affairslist.h"
#include "src/schedule.h"
#include "func/vector.h"
#include <iostream>
#include <QApplication>
using namespace std;
extern affairslist Affairslist;
extern Schedule schedule;
int main(int argc, char *argv[])
{
    QApplication b(argc, argv);
    MainWindow w;
    w.show();
    int week[17]={0};
    week[1]=week[2]=1;
    Vector<int> student;
    student.push_back(1);
    student.push_back(2);
    Affairslist.add_affairs(1,"我日",1,1,2,"test","test","test",week,student);
    Vector<affairs> result=Affairslist.search_affairs("我日",1,1);
    printf("1\n");
    for(int i=0;i<result.getSize();i++){
        cout<<result[i].kind<<endl;
        cout<<result[i].name<<endl;
        cout<<result[i].day<<endl;
        cout<<result[i].start_time<<endl;
        cout<<result[i].end_time<<endl;
        cout<<result[i].location<<endl;
        cout<<result[i].exam_time<<endl;
        cout<<result[i].exam_location<<endl;
        for(int j=1;j<17;j++)cout<<result[i].week[j]<<" ";
        cout<<endl;
        for(int j=0;j<result[i].student.getSize();j++)cout<<result[i].student[j]<<" ";
        cout<<endl;
    }
    schedule.add_affairs(0);
    for(int i=1;i<=2;i++){
        for(int j=0;j<=6;j++){
            for(int k=0;k<=23;k++){
                cout<<schedule.all_list[1].timetable[i][j][k].size()<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    printf("\nwwww\n");

    return b.exec();
}
