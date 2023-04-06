#ifndef TIMETABLE_H
#define TIMETABLE_H

#include<vector>
#include "func/vector.h"
using namespace std;

class Timetable {
public:
    static const int WEEKS = 16;
    static const int DAYS = 7;
    static const int HOURS = 24;
    Timetable();
    //最后一维[0]表示课程id，[1]表示课程类型
    vector<int> timetable[WEEKS+1][DAYS][HOURS]; 
    //将课表中某个时间段改为某个事务
    void add_to_timetable(int week, int day, int start_time, int end_time, int id);
    //将课表中某个时间段清空
    void remove_from_timetable(int week, int day, int start_time, int end_time);
    //获取某个时间段的课表
    Vector<int> get_time_timetable(int week,int day,int start_time,int end_time);
};
#endif // TIMETABLE_H
