#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 1100000,MAXM = 6100000,inf = 100000000;
int n,m,s,t,cnt = 1,head[MAXN],dis[MAXN],inq[MAXN],to[MAXM],flow[MAXM],nxt[MAXM];
void add(int a,int b,int fl)
{ 
	//printf("a = %d b = %d fl = %d\n",a,b,fl);
	nxt[++cnt] = head[a];
	to[cnt] = b;
	head[a] = cnt;
	flow[cnt] = fl;
	
	nxt[++cnt] = head[b];
	to[cnt] = a;
	head[b] = cnt;
	flow[cnt] = fl;
}
bool bfs()
{
	queue <int> que;
	memset(inq,0,sizeof(inq));//清出 每条边仅搜寻一次
	que.push(t);
	inq[t] = 1;
	while (!que.empty())
	{
		int x = que.front();
		que.pop();
		for (int i = head[x];i;i = nxt[i])
		{
			int v = to[i];
			if (!inq[v] && flow[i ^ 1] != 0)	//反向边流非空
			{
				dis[v] = dis[x] + 1;
				que.push(v);
				inq[v] = 1;
			}
		}
	}
	return inq[s];
}
int dfs(int cur,int lmt)
{
	if (cur == t)
		return lmt;
	int fl = 0;
	for (int i = head[cur];i && fl < lmt;i = nxt[i])
	{
		if (dis[to[i]] + 1 == dis[cur] && flow[i] != 0)	//保证增广的流是满足最短路的（bfs搜出的）
		{
			int tt = dfs(to[i],min(lmt - fl,flow[i]));
			flow[i] -= tt;
			flow[i ^ 1] += tt;
			fl += tt;
		}
	}
	return fl;
}
int maxflow()
{
	int res = 0;
	while (bfs())
	{
		int fl = 0;
		res += dfs(s,inf);
	}
	return res;
}
int main()
{
	/*
	scanf("%d%d%d%d",&n,&m,&s,&t);
	int tu,tv,tw;
	for (int i = 1;i <= m;i++)
	{
		scanf("%d%d%d",&tu,&tv,&tw);
		add(tu,tv,tw);
	}
	printf("%d\n",maxflow());
	*/
	
	scanf("%d%d",&n,&m);
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < m - 1;j++)
		{
			int tmp;
			scanf("%d",&tmp);
			add(i * m + j,i * m + j + 1,tmp);
		}
	}
	for (int i = 0;i < n - 1;i++)
	{
		for (int j = 0;j < m;j++)
		{
			int tmp;
			scanf("%d",&tmp);
			add(i * m + j,(i + 1) * m + j,tmp);
		}
	}
	for (int i = 0;i < n - 1;i++)
	{
		for (int j = 0;j < m - 1;j++)
		{
			int tmp;
			scanf("%d",&tmp);
			add(i * m + j,(i + 1) * m + j + 1,tmp);
		}
	}
	s = 0;
	t = n * m - 1;
	printf("%d\n",maxflow());
	return 0;
}