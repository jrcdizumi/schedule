#include "timetable.h"
mylist::mylist(){
    for(int i=1;i<=16;i++){
        for(int j=0;j<=6;j++){
            for(int k=0;k<=23;k++){
                timetable[i][j][k]=4;
            }
        }
    }
}
void mylist::add_affairs(affairs* a){
    //判断是否冲突
    for(int i=1;i<=16;i++){
        for(int j=(*a).start_time;j<(*a).end_time;i++){
            if((*a).week[i]&&(timetable[i][(*a).day][j]<=(*a).kind||((*a).kind==3&&timetable[i][(*a).day][j]<(*a).kind))){
                return;
            }
        }
    }
    //添加事务
    list.push_back(a);
    for(int i=list.getSize()-1;i>0;i--){
        if((*list[i]).start_time<(*list[i-1]).start_time){
            affairs* temp=list[i];
            list[i]=list[i-1];
            list[i-1]=temp;
        }
        else break;
    }
    //更新时间表
    for(int i=1;i<=16;i++){
        for(int j=(*a).start_time;j<(*a).end_time;i++){
            if((*a).week[i]){
                timetable[i][(*a).day][j]=(*a).kind;
            }
        }
    }
    return;
}
bool Timetable::add_affairs(affairs* a,Vector<int> student_id){
    for(int i=0;i<student_id.getSize();i++){
        all_list[student_id[i]].add_affairs(a);
    }
    return true;
}