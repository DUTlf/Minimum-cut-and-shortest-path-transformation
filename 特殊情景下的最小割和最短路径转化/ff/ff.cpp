#include <queue>
#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;
stack <int> sta;
const int MAXN = 1100000,MAXM = 6100000,inf = 100000000;
int n,m,s,t,cnt = 1,head[MAXN],dis[MAXN],inq[MAXN],to[MAXM],flow[MAXM],nxt[MAXM],res[MAXN],pre[MAXN],rec[MAXN];
void add(int a,int b,int fl)
{ 
	nxt[++cnt] = head[a];
	to[cnt] = b;
	head[a] = cnt;
	flow[cnt] = fl;
	
	nxt[++cnt] = head[b];
	to[cnt] = a;
	head[b] = cnt;
	flow[cnt] = fl;
}


int dfs(int s,int t)
{
    memset(pre,-1,sizeof(pre));
    while(!sta.empty()) 
    {
		sta.pop();
	}
    pre[s] = s;
	res[s] = inf;
    sta.push(s);
    while(!sta.empty())
    {
        int top = sta.top();
        sta.pop();
        int k = head[top];
        while(k != 0)
        {
            if(pre[to[k]] == -1 && flow[k] > 0)
            {
                res[to[k]] = min(res[top],flow[k]);
                pre[to[k]] = top;
                rec[to[k]] = k;
                sta.push(to[k]);
            }
            k = nxt[k];
        }
        if(pre[t] != -1) 
		{
			return res[t];
		}
    }
    return -1;
}
int maxflow()
{
    int add,ans = 0;
	//dfs寻找增广路径、返回当前寻找到的增光路径，当前增广流的大小...
    while((add=dfs(s,t))!=-1)
    {
        ans+=add;
        int k=t;
        while(k!=s)
        {
            flow[rec[k]] -= add; 	//走的那条边到当前k的点 异或
            flow[rec[k]^1] += add;
            k = pre[k];	//prek经过reck到达的k。
        }
    }
    return ans;
}

int main()
{
	
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