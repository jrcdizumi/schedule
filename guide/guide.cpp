#include"guide.h"
//-1 代表无法到达 , return dis[end] 代表最短距离 
namespace mymap{
int dijstra(int start,int end,Vector<Vector<edge>> &map,Vector<edge> &path){
    using namespace wh;

    int n=map.getSize();
    Vector<edge> tpath;
    Vector<int> dis(n,maxn);
    Vector<bool> vis(n,0);
    tpath.resize(n);

    struct node{
        int val;
        int id;
        node(){};
        node(int val,int id){
            this->val=val;
            this->id=id;
        }
        bool operator < (const node &a)const{
            return val>a.val;
        }
    };
    priority_queue<node> q;
    dis[start]=0;
    q.push(node(0,start));
    while(!q.empty()){
        node tmp=q.top();
        q.pop();
        int u=tmp.id;
        if(vis[u]) 
            continue;
        vis[u]=1;
        int to;
        for(int i=0;i<map[u].getSize();i++){
            to=map[u][i].to;
            if(!vis[to]&&dis[u]+map[u][i].val<dis[to]){
                dis[to]=dis[u]+map[u][i].val;
                tpath[to]=edge(u,i,0,1);
                q.push(node(dis[to],to));
            }
        }
    }
    path.clear();
    int now=end;
    int tmp=0;
    while(now!=start){
        now=tpath[now].from;
        tmp++;
    }
    path.resize(tmp);
    now=end;
    while(now!=start){
        path[tmp-1]=map[tpath[now].from][tpath[now].to];
        tmp--;
        now=tpath[now].from;
    }
    return dis[end];
}

void mutiinit(int start,Vector<int> &end,Vector<Vector<edge>> &map,Vector<Vector<Vector<edge>>> &tpath,Vector<Vector<int>> &dis,Vector<int> &tot,int &n,int &m){
    n=map.getSize();
    m=end.getSize()+1;
    tot.resize(m);
    tot[0]=start;
    for(int i=0;i<end.getSize();i++){
        tot[i+1]=end[i];
    }
    tpath.resize(m);
    dis.resize(m);
    for(int i=0;i<m;i++){
        dis[i].resize(m);
        tpath[i].resize(m);
        for(int j=0;j<m;j++){
            if(i==j)
                dis[i][j]=0;
            else
                dis[i][j]=dijstra(tot[i],tot[j],map,tpath[i][j]);
        }
    }
    return;
}

int cal_length(Vector<int> &lis , Vector<Vector<int>> &dis){
    int rt=0;
    for(int i=0;i<lis.getSize()-1;i++){
        rt+=dis[lis[i]][lis[i+1]];
    }
    return rt;
}
void new_arr(Vector<int> &lis){
    srand(time(NULL));
    int n=lis.getSize()-1;
    int a=rand()%n+1;
    int b=rand()%n+1;
    while(a==b){
        b=rand()%n+1;
    }
    int tmp=lis[a];
    lis[a]=lis[b];
    lis[b]=tmp;
    return;
}
//模拟退火算法
int sa_mutidis(int start,Vector<int> &end,Vector<Vector<edge>> &map,Vector<edge> &path){
    int n,m;
    Vector<int> tot;
    Vector<Vector<int>> dis;
    Vector<Vector<Vector<edge>>> tpath;
    mutiinit(start,end,map,tpath,dis,tot,n,m);
    Vector<int> lis;
    Vector<int> ans;
    lis.resize(m);
    ans.resize(m);
    for(int i=0;i<m;i++)
        lis[i]=i;
    ans=lis;
    const double t0 = 50000.0;
    const double tend = 1e-10;
    const double delta = 0.94;
    const int len = 5000;
    double t = t0;
    double dE;
    double randnum;
    while(t>tend){
        for(int i=0;i<len;i++){
            new_arr(lis);
            dE=cal_length(lis,dis)-cal_length(ans,dis);
            if(dE<0){
                ans=lis;
            }
            else{
                randnum=(double)rand()/(double)(RAND_MAX);
                if(exp(-dE/t)>randnum){
                    ans=lis;
                }
            }
        }
        t*=delta;
    }
    path.clear();
    for(int i=0;i<ans.getSize()-1;i++){
        for(int j=0;j<tpath[ans[i]][ans[i+1]].getSize();j++){
            path.push_back(tpath[ans[i]][ans[i+1]][j]);
        }
    }
    return cal_length(ans,dis);
}


void reverse(Vector<int> &lis, int a,int b){
    while(a<b){
        int tmp=lis[a];
        lis[a]=lis[b];
        lis[b]=tmp;
        a++;
        b--;
    }
    return;
}
//返回多点最短路径的最短距离
int accuratr_mutidis(int start,Vector<int> &end,Vector<Vector<edge>> &map,Vector<edge> &path){
    using namespace wh;
    int n,m;
    Vector<int> tot;
    Vector<Vector<int>> dis;
    Vector<Vector<Vector<edge>>> tpath;
    mutiinit(start,end,map,tpath,dis,tot,n,m);
    Vector<Vector<int>> dp(1<<m);
    Vector<Vector<int>> pre(1<<m);
    for(int i=0;i<(1<<m);i++){
        dp[i].resize(m);
        pre[i].resize(m);
        for(int j=0;j<m;j++)
            dp[i][j]=maxn;
    }
    Vector<int> vis(1<<m,0);
    dp[1][0]=0;
    vis[1]=1;
    queue<int> q;
    q.push(1);
    int next;
    while(!q.empty()){
        int now=q.front();
        q.pop();
        if(now==(1<<m)-1)
            continue;
        for(int i=0;i<m;i++){
            if(now&(1<<i)){
                for(int j=0;j<m;j++){
                    if(!(now&(1<<j))){
                        if(dp[now|(1<<j)][j]>dp[now][i]+dis[i][j]){
                            dp[now|(1<<j)][j]=dp[now][i]+dis[i][j];
                            pre[now|(1<<j)][j]=i;
                            if(!vis[now|(1<<j)]){
                                vis[now|(1<<j)]=1;
                                q.push(now|(1<<j));
                            }
                        }
                    }
                }
            }
        }
    }
    path.clear();
    int now=(1<<m)-1;
    int ed=1,tmp=dp[now][1];
    for(int i=1;i<m;i++){
        if(dp[now][i]<tmp){
            tmp=dp[now][i];
            ed=i;
        }
    }
    int ans=dp[now][ed];
    int prenow=pre[now][ed];
    Vector<int> tmpath;
    while(now!=1){
        tmpath.push_back(ed);
        now=now^(1<<ed);
        ed=prenow;
        prenow=pre[now][ed];
    }
    tmpath.push_back(0);
    reverse(tmpath,0,tmpath.getSize()-1);
    for(int i=0;i<tmpath.getSize()-1;i++){
        for(int j=0;j<tpath[tmpath[i]][tmpath[i+1]].getSize();j++){
            path.push_back(tpath[tmpath[i]][tmpath[i+1]][j]);
        }
    }
    return ans;
}

void map_init(Vector<Vector<edge>> &map,int n){
    map.clear();
    map.resize(n);
    return;
}
void add_edge(Vector<Vector<edge>> &map,int from,int to,int val,bool flag){
    map[from].push_back(edge(from,to,val,flag));
    return;
}

void add_edge(Vector<Vector<edge>> &map,edge &e){
    map[e.from].push_back(e);
    return ;
}
}
