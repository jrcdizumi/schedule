#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "../func/vector.h"
#include "affairslist.h"
#include <vector>
extern affairslist Affairslist;
class mylist{
public:
    //初始化mylist
    mylist();
    //时间表。
    std::vector<int> timetable[17][7][24];
    //给该学生添加事务
    bool add_affairs(int a);
    //删除事务
    bool delete_affairs(int a);
    //按时间搜索并按字典序排序
    Vector<int> search_affairs(int week,int day,int start_time,int end_time,int kind);
    void qSort(Vector<int>& arr, int left, int right);
};
class Schedule{
public:
    //每个学生的时间表
    Vector<mylist> all_list{128};
    Schedule();
    //添加事务
    bool add_affairs(int a);
    //删除事务
    bool delete_affairs(int a);
};
#endif // SCHEDULE_H
