#ifndef GUIDE_H
#define GUIDE_H

#include"map.h"
#include"..\func\vector.h"
#include"..\func\queue.h"

namespace mymap{

const int maxn = 0x3f3f3f3f;

int dijstra(int start,int end,Vector<Vector<edge>> &map,Vector<edge> &path);

int accuratr_mutidis(int start,Vector<int> &end,Vector<Vector<edge>> &map,Vector<edge> &path);

int sa_mutidis(int start,Vector<int> &end,Vector<Vector<edge>> &map,Vector<edge> &path);

void map_init(Vector<Vector<edge>> &map,int n);

void add_edge(Vector<Vector<edge>> &map,int from,int to,int val,bool flag);

void add_edge(Vector<Vector<edge>> &map,edge &e);

void reverse(Vector<int> &lis, int a,int b);

void new_arr(Vector<int> &lis);

int cal_length(Vector<int> &lis , Vector<Vector<int>> &dis);

void mutiinit(int start,Vector<int> &end,Vector<Vector<edge>> &map,Vector<Vector<Vector<edge>>> &tpath,Vector<Vector<int>> &dis,Vector<int> &tot,int &n,int &m);

}
#endif
