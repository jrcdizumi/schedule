#include "schedule.h"
mylist::mylist(){
    for(int i=1;i<=16;i++){
        for(int j=0;j<=6;j++){
            for(int k=0;k<=23;k++){
                timetable[i][j][k].clear();
            }
        }
    }
}
bool mylist::add_affairs(int a){
    //判断是否冲突
    affairs tmpaffairs=Affairslist.list[a];
    for(int i=1;i<=16;i++){
        for(int j=tmpaffairs.start_time;j<tmpaffairs.end_time;i++){
            if(timetable[i][tmpaffairs.day][j].size()!=0&&tmpaffairs.week[i]&&(Affairslist.list[timetable[i][tmpaffairs.day][j][0]].kind<=tmpaffairs.kind||(tmpaffairs.kind==2&&Affairslist.list[timetable[i][tmpaffairs.day][j][0]].kind<tmpaffairs.kind))){
                return false;
            }
        }
    }
    //更新时间表
    for(int i=1;i<=16;i++){
        for(int j=tmpaffairs.start_time;j<tmpaffairs.end_time;i++){
            if(tmpaffairs.week[i]){
                if(Affairslist.list[timetable[i][tmpaffairs.day][j][0]].kind==2)timetable[i][tmpaffairs.day][j].push_back(a);
                else {
                    timetable[i][tmpaffairs.day][j].clear();
                    timetable[i][tmpaffairs.day][j].push_back(a);
                }
            }
        }
    }
    return true;
}
bool Schedule::add_affairs(int a){
    bool flag=1;
    affairs tmpaffairs=Affairslist.list[a];
    for(int i=0;i<tmpaffairs.student.getSize();i++){
        for(int j=1;j<=16;j++){
            for(int k=tmpaffairs.start_time;k<tmpaffairs.end_time;k++){
                if(all_list[tmpaffairs.student[i]].timetable[j][tmpaffairs.day][k].size()!=0&&tmpaffairs.week[j]&&(tmpaffairs.kind>=Affairslist.list[all_list[tmpaffairs.student[i]].timetable[j][tmpaffairs.day][k][0]].kind||(tmpaffairs.kind==2&&Affairslist.list[all_list[tmpaffairs.student[i]].timetable[j][tmpaffairs.day][k][0]].kind<tmpaffairs.kind))){
                    flag=0;
                    break;
                }
            }
        }
    }
    if(!flag){
        if(tmpaffairs.kind==1){   
            int all_timetable[24];                 
            for(int j=0;j<=23;j++){
                all_timetable[j]=0;
            }
            for(int i=1;i<=16;i++){
                if(tmpaffairs.week[i]){
                    for(int j=0;j<=23;j++){
                        for(int k=0;k<tmpaffairs.student.getSize();k++){
                            if(all_list[tmpaffairs.student[k]].timetable[i][tmpaffairs.day][j].size()!=0&&all_list[tmpaffairs.student[k]].timetable[i][tmpaffairs.day][j][0]<1){
                                all_timetable[j]++;
                            }
                        }
                    }
                }
            }
            int minx=114514,x=0;
            for(int i=0;i<=23;i++){
                if(all_timetable[i]<minx){
                    minx=all_timetable[i];
                    x=i;
                }
            }
            tmpaffairs.start_time=x;
            tmpaffairs.end_time=x+1;
            Vector<int> new_student_id;
            for(int i=0;i<tmpaffairs.student.getSize();i++){
                if(all_list[tmpaffairs.student[i]].add_affairs(a)){
                    new_student_id.push_back(tmpaffairs.student[i]);
                }
            }
            tmpaffairs.student=new_student_id;
            if(new_student_id.getSize()==0){
                return false;
            }
        }
        else{
            return false;
        }
    }
    else {
        for(int i=0;i<tmpaffairs.student.getSize();i++){
            all_list[tmpaffairs.student[i]].add_affairs(a);
        }
        return true;
    }
    return true;
}
bool mylist::delete_affairs(int a){
    affairs tmpaffairs=Affairslist.list[a];
    //更新时间表
    for(int i=1;i<=16;i++){
        for(int j=tmpaffairs.start_time;j<tmpaffairs.end_time;i++){
            if(tmpaffairs.week[i]){
                timetable[i][tmpaffairs.day][j].clear();
            }
        }
    }
    return true;
}
bool Schedule::delete_affairs(int a){
    affairs tmpaffairs=Affairslist.list[a];
    for(int i=0;i<tmpaffairs.student.getSize();i++){
        all_list[tmpaffairs.student[i]].delete_affairs(a);
    }
    Affairslist.list[a].kind=3;
    return true;
}

