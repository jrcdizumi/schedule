#ifndef TIMETABLE_H
#define TIMETABLE_H

#include "func/vector.h"

//记录
class tmplist{

};
class Timetable {
public:
    static const int WEEKS = 16;
    static const int DAYS = 7;
    static const int HOURS = 24;
    Timetable();
    //最后一维[0]表示课程id，[1]表示课程类型
    int timetable[WEEKS+1][DAYS][HOURS][2]; 
    bool add_to_timetable(bool week[17], int day, int start_time, int end_time, int id,int kind);
};
#endif // TIMETABLE_H
