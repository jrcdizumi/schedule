#include "timetable.h"
Timetable::Timetable(){
    for(int i = 1; i <= WEEKS; i++){
        for(int j = 0; j < DAYS; j++){
            for(int k = 0; k < HOURS; k++){
                vector <int>().swap(timetable[i][j][k]);
            }
        }
    }
}
void Timetable::add_to_timetable(int week, int day, int start_time, int end_time, int id){
    for(int i = start_time; i < end_time; i++){
        timetable[week][day][i].push_back(id);
    }
}
void Timetable::remove_from_timetable(int week, int day, int start_time, int end_time){
    for(int i = start_time; i < end_time; i++){
        vector <int>().swap(timetable[week][day][i]);
    }
}
Vector<int> Timetable::get_time_timetable(int week,int day,int start_time,int end_time){
    Vector<int> res;
    for(int i = start_time; i < end_time; i++){
        for(int j = 0; j < timetable[week][day][i].size(); j++){
            res.push_back(timetable[week][day][i][j]);
        }
    }
    return res;
}