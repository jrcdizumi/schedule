#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "func/vector.h"
#include "affairslist.h"
using namespace std;

class mylist{
public:
    //初始化mylist
    mylist();
    //时间表。
    affairs* timetable[17][7][24];
    //给该学生添加事务
    void add_affairs(affairs* a);
};
class Schedule{
public:
    //每个学生的时间表
    Vector<mylist> all_list;
    bool add_affairs(affairs* a,Vector<int> student_id);
};
#endif // SCHEDULE_H
