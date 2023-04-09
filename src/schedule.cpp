#include "schedule.h"
mylist::mylist(){
    for(int i=1;i<=16;i++){
        for(int j=0;j<=6;j++){
            for(int k=0;k<=23;k++){
                timetable[i][j][k]=NULL;
            }
        }
    }
}
bool mylist::add_affairs(affairs* a){
    //判断是否冲突
    for(int i=1;i<=16;i++){
        for(int j=(*a).start_time;j<(*a).end_time;i++){
            if((*a).week[i]&&((*timetable[i][(*a).day][j]).kind<=(*a).kind||((*a).kind==2&&(*timetable[i][(*a).day][j]).kind<(*a).kind))){
                return false;
            }
        }
    }
    //更新时间表
    for(int i=1;i<=16;i++){
        for(int j=(*a).start_time;j<(*a).end_time;i++){
            if((*a).week[i]){
                timetable[i][(*a).day][j]=a;
            }
        }
    }
    return true;
}
bool Schedule::add_affairs(affairs* a,Vector<int> student_id){
    bool flag=1;
    for(int i=0;i<student_id.getSize();i++){
        for(int j=1;j<=16;j++){
            for(int k=(*a).start_time;k<(*a).end_time;k++){
                if((*a).week[j]&&((*all_list[student_id[i]].timetable[j][(*a).day][k]).kind<=(*a).kind||((*a).kind==2&&(*all_list[student_id[i]].timetable[j][(*a).day][k]).kind<(*a).kind))){
                    flag=0;
                    break;
                }
            }
        }
    }
    if(!flag){
        if((*a).kind==1){   
            int all_timetable[24];                 
            for(int j=0;j<=23;j++){
                all_timetable[j]=0;
            }
            for(int i=1;i<=16;i++){
                if((*a).week[i]){
                    for(int j=0;j<=23;j++){
                        for(int k=0;k<student_id.getSize();k++){
                            if(all_list[student_id[k]].timetable[i][(*a).day][j]!=NULL){
                                all_timetable[j]++;
                            }
                        }
                    }
                }
            }
            int minx=114514,x;
            for(int i=0;i<=23;i++){
                if(all_timetable[i]<minx){
                    minx=all_timetable[i];
                    x=i;
                }
            }
            (*a).start_time=x;
            (*a).end_time=x+1;

        }            
        Vector<int> new_student_id;
        for(int i=0;i<student_id.getSize();i++){
            if(all_list[student_id[i]].add_affairs(a)){
                new_student_id.push_back(student_id[i]);
            }
        }
        if(new_student_id.getSize()==0){
            return false;
        }
        (*a).student=new_student_id;
    }
    else {
        for(int i=0;i<student_id.getSize();i++){
            all_list[student_id[i]].add_affairs(a);
        }
        (*a).student=student_id;
    }
}