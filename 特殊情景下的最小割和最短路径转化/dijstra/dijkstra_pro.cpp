#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN = 2500000;
const int MAXM = 7000000;
const int inf = 100000000;
queue <int> dl;
int n,m,nm,tx,cnt = 1,s,t,n1,m1,nm1;
int head[MAXN],nxt[MAXM],to[MAXM],we[MAXM],dis[MAXN];
bool vis[MAXN];
void add(int x,int y,int w)
{
    nxt[++cnt] = head[x];
    to[cnt] = y;
    head[x] = cnt;
    we[cnt] = w;

    nxt[++cnt] = head[y];
    to[cnt] = x;
    head[y] = cnt;
    we[cnt] = w;
}


struct pot
{
    int x,dis;
    pot (int _x = 0,int _dis = 0) : x(_x),dis(_dis) {}
    friend bool operator < (pot a,pot b)
    {
        return a.dis > b.dis;
    }
};
priority_queue <pot> que;
void solve1(int x,int y)
{
    if (x == 1)
    add(s,(x - 1) * m1 + nm1 + y,tx);else
    if (x == n)
    add(t,(x - 2) * m1 + y,tx);else
    add((x - 2) * m1 + y,(x - 1) * m1 + nm1 + y,tx);
}
void solve2(int x,int y)
{
    if (y == 1)
    add(t,(x - 1) * m1 + y,tx);else
    if (y == m)
    add(s,(x - 1) * m1 + y - 1 + nm1,tx);else
    add((x - 1) * m1 + y - 1 + nm1,(x - 1) * m1 + y,tx);
}
void solve3(int x,int y)
{
    add((x - 1) * m1 + y + nm1,(x - 1) * m1 + y,tx);
}
int dijkstra()
{
    for (int i = 0;i <= t;i++)
	{
		dis[i] = inf;
	}
    que.push(pot(s,0));
    dis[s] = 0;
    while (!que.empty())
    {
        pot now = que.top();
        que.pop();
        if(vis[now.x]) 
		{
			continue;
		}
        vis[now.x] = true;
        for (int i = head[now.x];i;i = nxt[i])
        {
            if(dis[to[i]] > dis[now.x] + we[i])
            {
                dis[to[i]] = dis[now.x] + we[i];
                que.push(pot(to[i],dis[to[i]]));
            }
        }
    }
    return dis[t];
}
int main()
{
    scanf("%d%d",&n,&m);
    nm = n * m;
    n1 = n - 1,m1 = m - 1;
    nm1 = n1 * m1;
    s = 2 * nm1 + 1;
    t = s + 1;
    for (int i = 1;i <= n;i++)
    {
        for (int j = 1;j < m;j++)
        {
            scanf("%d",&tx);
            solve1(i,j);
        }
    }
    for (int i = 1;i < n;i++)
    {
        for (int j = 1;j <= m;j++)
        {
            scanf("%d",&tx);
            solve2(i,j);
        }
    }
    for (int i = 1;i < n;i++)
    {
        for (int j = 1;j < m;j++)
        {
            scanf("%d",&tx);
            solve3(i,j);
        }
    }
    printf("%d\n",dijkstra());
    return 0;
}