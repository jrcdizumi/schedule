#ifndef AFFAIRSLIST_H
#define AFFAIRSLIST_H

#include <string>
#include <iostream>
#include "../func/vector.h"
#include "../func/hashmap.h"
#include "../func/json/json.h"
#include <fstream>
#include "trie.h"
class affairs
{
    public:
        affairs();
        //拥有该事务的学生名单
        Vector<int> student;
        //事务类型，0为课程，1为活动，2为临时事务,3为已删除。
        int kind; 
        //事务名称
        std::string name;
        //事务周，二进制表示，共16位。
        bool week[17];
        //事务日，0为周日，1为周一，2为周二，3为周三，4为周四，5为周五，6为周六,7为每天。
        int day;
        //事务开始时间，0-23。
        int start_time;
        //事务结束时间，0-23。
        int end_time;
        //事务地点,如果是线上则为网址（www开头）。
        std::string location;
        //考试时间
        std::string exam_time;
        //考试地点
        std::string exam_location;
        //构造函数
        affairs(int kind, std::string name, int day,int start_time, int end_time, std::string location, std::string exam_time, std::string exam_location);
};

class affairslist
{
    public:
        Vector<affairs> list;
        Trie serach_trie;
        affairslist();
        ~affairslist();
        Vector<affairs> search_affairs(std::string name,int student_id);
        void add_affairs(int kind, std::string name, int day,int start_time, int end_time, std::string location, std::string exam_time, std::string exam_location,int week[17],Vector<int> student);
};
#endif // AFFAIRSLIST_H
