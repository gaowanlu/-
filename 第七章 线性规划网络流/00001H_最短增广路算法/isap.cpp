/*
最短可增广路:重贴标签算法Isap
算法设计:
1、确定合适数据结构，采用邻接表存储网络。
2、对网络结点贴标签，即标高操作。
3、对源点的高度>=结点数，则转向第(6)步，否则从源点开始，沿着高度h(u)=h(v)+1且有可行邻接边(cap>flow)
的方向前进，如果到达汇点，则转向第(4)步；如果无法行进，则转向第(5)步。
4、增流操作：沿着找到的可增广路同向边增流，反向边剑流。注意：在原网络上操作。
5、重贴标签：如果拥有当前结点高度的结点只有一个，则转向第(6)步；令当前结点的高度=所有邻接点高度的最小值+1，如果没有可行邻接边，
则令当前结点的高度=结点数；退回一步；转向第（3）步。
6、算法结束：已找到最大流。
*/
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int INF=0x3fffffff;
const int N=100;//最大结点数
const int M=10000;//最大边数
int top;
int h[N],pre[N],g[N];
//h[]记录各结点的高度
//g[]记录距离h[]的结点的个数,g[3]记录h为3的结点个数        E[i]
//pre[]记录结点的前驱边，根据pre可以倒推可增广路径pre[v]=i ----->v
//邻接表头结点
struct Vertex{
    int first;//first记录E[M]的M 为N->v的边
}V[N];
struct Edge{
    int v,next;
    int cap,flow;
}E[M];
void init(){
    memset(V,-1,sizeof(V));//初始化V[all].first=-1
    top=0;//记录E[]使用到了那里了
}
//-->
void add_edge(int u,int v,int c){//添加单条边
    //参数 u v及u-->v边的容量c
    E[top].v=v;
    E[top].cap=c;
    E[top].flow=0;
    //头插法
    E[top].next=V[u].first;
    V[u].first=top;
    top++;
}
void add(int u,int v,int c){//添加正负两边
    add_edge(u,v,c);
    add_edge(v,u,0);
}
//-->
void set_h(int t,int n){//标高函数,t源点 n汇点
    queue<int>Q;//广度优先搜索
    memset(h,-1,sizeof(h));//初始化各结点的高为-1
    memset(g,0,sizeof(g));//全部高度的结点数量为0
    h[t]=0;//汇点高度为0
    Q.push(t);//汇点入队列
    while(!Q.empty()){
        int v=Q.front();Q.pop();//对头出队列
        ++g[h[v]];//高度为h[v]的数量+1
        for(int i=V[v].first;i!=-1;i=E[i].next){//遍历结点v的临界点及v-->some
            int u=E[i].v;
            if(h[u]==-1){//还没有标记过
                h[u]=h[v]+1;
                Q.push(u);//入队列
            }
        }
    }
    cout<<"Init hight Value\n";
    cout<<"h[ ]=";
    for(int i=1;i<=n;i++){
        cout<<" "<<h[i];
    }
    cout<<endl;
}

//参数  s:源点 t:汇点 n:总结点个数
//返回值  网络最大流
int Isap(int s,int t,int n){//isap增广算法
    //初始化标高
    set_h(t,n);//从t-->n
    int ans=0,u=s;//ans最大流量,u当前探索到的结点
    int d;
    while(h[s]<n){
        int i=V[u].first;
        if(u==s){//当前在源点时
            d=INF;
        }
        //搜索当前结点的邻接边
        for(;i!=-1;i=E[i].next){
            int v=E[i].v;//u-->v
            //判断是否满足探索条件：有可增量 且 h[u]-1=h[v]
            if(E[i].cap>E[i].flow&&h[u]-1==h[v]){
                u=v;//满足条件则当前位置移到v           E[i]
                pre[v]=i;//设置v结点的前驱为i 即记录边u------->v
                //迭代最小增量
                d=min(d,E[i].cap-E[i].flow);
                if(u==t){//探索到了汇点
                    printf("增广路径:%d",t);
                    while(u!=s){
                        int j=pre[u];//即增广路汇点的前驱边E[j]
                        E[j].flow+=d;//E[j]流量增d
                        E[j^1].flow-=d;//j的反向边流量-d
                        /*
                        ^1:创建边时是成对创建的0^1=1 1^1=0 2^1=3 3^1=2
                        */
                        u=E[j^1].v;
                        cout<<"---"<<u;
                    }
                    printf("增流: %d\n",d);
                    ans+=d;
                    d=INF;
                }
                break;
            }
        }
        if(-1==i){//所有邻接边搜索完毕,无法前行
            if(--g[h[u]]==0){//该高度结点只有1个，算法结束
                break;
            }
            int hmin=n-1;
            for(int j=V[u].first;j!=-1;j=E[j].next){//搜索u的邻接边
                if(E[j].cap>E[j].flow){//有可增量
                    hmin=min(hmin,h[E[j].v]);
                }
            }
            h[u]=hmin+1;
            printf("重贴标签后的高度\n");
            printf("h[ ]=");
            for(int i=1;i<=n;i++){
                printf(" %d",h[i]);
            }
            printf("\n");
            ++g[h[u]];//重新贴标签后该高度的结点数+1
            if(u!=s){//当前结点不是源点
                u=E[pre[u]^1].v;//退回一步
            }
        }
    }
    return ans;
}


void printg(int n){//输出邻接表
    for(int i=1;i<=n;i++){
        cout<<"v"<<i<<" ["<<V[i].first;
        for(int j=V[i].first;j!=-1;j=E[j].next){
            cout<<"]--["<<E[j].v<<" "<<E[j].cap<<" "<<E[j].flow<<" "<<E[j].next;
        }
        cout<<"]\n";
    }
}

void printflow(int n){//输出实流边,有流量的边
    printf("Real Stream Network Value:\n");
    for(int i=1;i<=n;i++){
        for(int j=V[i].first;j!=-1;j=E[j].next){
            if(E[j].flow>0){
                cout<<"v"<<i<<"--"<<"v"<<E[j].v<<" "<<E[j].flow<<endl;;
            }
        }
    }
}

int main(void){
    int n,m;//记录节点数与边数
    int u,v,w;//u->v cap=w
    cin>>n>>m;
    init();
    for(int i=1;i<=m;i++){
        cin>>u>>v>>w;
        add(u,v,w);//添加两条反向边
    }
    printg(n);//输出网络邻接表
    //Isap算法求网络最大流
    cout<<"network max stream value is:"<<Isap(1,n,n)<<endl;
    printg(n);//输出邻接表
    printflow(n);//输出实流边
    return 0;
}
/*
test example
6 9
1 3 10
1 2 12
2 4 8
3 5 13
3 2 2
4 6 18
4 3 5
5 6 4
5 4 6


out:
v1 [2]--[2 12 0 0]--[3 10 0 -1]
v2 [9]--[3 0 0 4]--[4 8 0 3]--[1 0 0 -1]
v3 [13]--[4 0 0 8]--[2 2 0 6]--[5 13 0 1]--[1 0 0 -1]
v4 [17]--[5 0 0 12]--[3 5 0 10]--[6 18 0 5]--[2 0 0 -1]
v5 [16]--[4 6 0 14]--[6 4 0 7]--[3 0 0 -1]
v6 [15]--[5 0 0 11]--[4 0 0 -1]
Init hight Value
h[ ]= 3 2 2 1 1 0
澧炲箍璺緞:6---4---2---1澧炴祦: 8
閲嶈创鏍囩鍚庣殑楂樺害
h[ ]= 3 4 2 1 1 0
澧炲箍璺緞:6---5---3---1澧炴祦: 4
閲嶈创鏍囩鍚庣殑楂樺害
h[ ]= 3 4 2 1 2 0
閲嶈创鏍囩鍚庣殑楂樺害
h[ ]= 3 4 3 1 2 0
閲嶈创鏍囩鍚庣殑楂樺害
h[ ]= 4 4 3 1 2 0
澧炲箍璺緞:6---4---5---3---1澧炴祦: 6
閲嶈创鏍囩鍚庣殑楂樺害
h[ ]= 5 4 3 1 2 0
network max stream value is:18
v1 [2]--[2 12 8 0]--[3 10 10 -1]
v2 [9]--[3 0 0 4]--[4 8 8 3]--[1 0 -8 -1]
v3 [13]--[4 0 0 8]--[2 2 0 6]--[5 13 10 1]--[1 0 -10 -1]
v4 [17]--[5 0 -6 12]--[3 5 0 10]--[6 18 14 5]--[2 0 -8 -1]
v5 [16]--[4 6 6 14]--[6 4 4 7]--[3 0 -10 -1]
v6 [15]--[5 0 -4 11]--[4 0 -14 -1]
Real Stream Network Value:
v1--v2 8
v1--v3 10
v2--v4 8
v3--v5 10
v4--v6 14
v5--v4 6
v5--v6 4
*/



