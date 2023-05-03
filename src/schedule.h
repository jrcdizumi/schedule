#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "../func/vector.h"
#include "affairslist.h"
#include <vector>
using namespace std;
extern affairslist Affairslist;
class mylist{
public:
    //初始化mylist
    mylist();
    //时间表。
    vector<int> timetable[17][7][24];
    //给该学生添加事务
    bool add_affairs(int a);
    //删除事务
    bool delete_affairs(int a);
};
class Schedule{
public:
    //每个学生的时间表
    Vector<mylist> all_list;
    //添加事务
    bool add_affairs(int a);
    //删除事务
    bool delete_affairs(int a);
};
#endif // SCHEDULE_H
