#ifndef TIMETABLE_H
#define TIMETABLE_H

#include "func/vector.h"
#include "affairslist.h"
using namespace std;

class mylist{
public:
    //初始化mylist
    mylist();
    //该学生拥有的事务，按在每周内的时间排序
    Vector<affairs*> list;
    //时间表，仅用于判断冲突。
    int timetable[17][7][24];
    //给该学生添加事务
    void add_affairs(affairs* a);
};
class Timetable {
public:
    //每个学生拥有的事务，按在每周内的时间排序
    Vector<mylist> all_list;
    Timetable();
    bool add_affairs(affairs* a,Vector<int> student_id);
};
#endif // TIMETABLE_H
