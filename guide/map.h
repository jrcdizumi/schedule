#ifndef MAP_H
#define MAP_H

#include<cstdio>
#include<iostream>
#include<ctime>
#include<algorithm>
#include<cmath>


class edge{
    public:
    int from;;
    int to,val;
    int dis;
    bool flag;//0 bike 1 walk
    edge(){};
    edge(int id,int to,int val,bool flag){
        this->from=id;
        this->to=to;
        this->dis=val;
        this->val=val;
        this->flag=flag;
    }
    void operator = (const edge &b){
        from=b.from;
        to=b.to;
        dis=b.dis;
        val=b.val;
        flag=b.flag;
        return;
    }
};

#endif
