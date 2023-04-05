#include "timetable.h"
Timetable::Timetable() {
    for (int i = 1; i <= WEEKS; i++) {
        for (int j = 0; j < DAYS; j++) {
            for (int k = 0; k < HOURS; k++) {
                timetable[i][j][k][0] = timetable[i][j][k][0] = -1; 
            }
        }
    }
}
bool Timetable::add_to_timetable(bool week[17], int day, int start_time, int end_time, int id,int kind){
    if(kind==4)return false;
    if(kind!=3)
    for (int i = 1; i <= WEEKS; i++) {
        if (week[i]) {
            for (int j = start_time; j < end_time; j++) {
                if (timetable[i][day][j][1]<=kind) {
                    return false;
                }
            }
        }
    }
    for (int i = 1; i <= WEEKS; i++) {
        if (week[i]) {
            for (int j = start_time; j < end_time; j++) {
                timetable[i][day][j][0] = id;
                timetable[i][day][j][1] = kind;
            }
        }
    }
    return true;
}