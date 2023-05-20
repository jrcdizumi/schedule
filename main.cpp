#include "login.h"
#include "src/affairslist.h"
#include "src/schedule.h"
#include "func/vector.h"
#include <iostream>
#include <QApplication>
using namespace std;
extern affairslist Affairslist;
extern Schedule schedule;
int now_user=1;
int now_week=1;
int main(int argc, char *argv[])
{
    QApplication b(argc, argv);
    int week[17]={0};
    week[1]=week[2]=1;
    Vector<int> student;
    student.push_back(1);
    student.push_back(2);
    Affairslist.add_affairs(2,"高等数学",1,1,2,"教三-319","6月21日","教三-519",week,student);
    Affairslist.add_affairs(2,"高等数学",2,1,2,"教三-319","6月21日","教三-519",week,student);
    Affairslist.add_affairs(1,"英语",4,4,5,"教三-319","6月21日","教三-519",week,student);
    Affairslist.add_affairs(1,"英语",5,1,2,"教三-319","6月21日","教三-519",week,student);
    Affairslist.add_affairs(0, "Math", 1, 8, 10, "Room 101", "2022-06-15 14:00", "Auditorium", new int[17]{0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, student);
    Affairslist.add_affairs(1, "English", 3, 9, 11, "Room 202", "2022-06-16 14:00", "Gymnasium", new int[17]{0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, student);
    Affairslist.add_affairs(2, "Physics", 5, 13, 15, "Room 303", "2022-06-17 14:00", "Library", new int[17]{0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, student);
    Affairslist.add_affairs(0, "Math", 2, 8, 10, "Room 102", "2022-06-15 14:00", "Auditorium", new int[17]{0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, student);
    Affairslist.add_affairs(1, "English", 4, 9, 11, "Room 203", "2022-06-16 14:00", "Gymnasium", new int[17]{0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, student);
    Affairslist.add_affairs(2, "Physics", 6, 13, 15, "Room 304", "2022-06-17 14:00", "Library", new int[17]{0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, student);
    Affairslist.add_affairs(0, "Math", 3, 8, 10, "Room 101", "2022-06-15 14:00", "Auditorium", new int[17]{0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, student);
    Affairslist.add_affairs(0, "Math", 4, 8, 10, "Room 101", "2022-06-15 14:00", "Auditorium", new int[17]{0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, student);
    Affairslist.add_affairs(0, "Math", 5, 8, 10, "Room 101", "2022-06-15 14:00", "Auditorium", new int[17]{0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, student);
    Affairslist.add_affairs(0, "Math", 6, 8, 10, "Room 101", "2022-06-15 14:00", "Auditorium", new int[17]{0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, student);
    Affairslist.add_affairs(0, "Math", 7, 8, 10, "Room 101", "2022-06-15 14:00", "Auditorium", new int[17]{0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, student);
    Affairslist.add_affairs(0, "Math", 1, 9, 10, "Room 101", "2022-06-15 14:00", "Auditorium", new int[17]{0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, student);
    Affairslist.add_affairs(0, "Math", 2, 9, 10, "Room 101", "2022-06-15 14:00", "Auditorium", new int[17]{0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, student);
    for(int i=0;i<Affairslist.list.getSize();i++)
    schedule.add_affairs(i);
    login w;
    w.show();
    return b.exec();
}
