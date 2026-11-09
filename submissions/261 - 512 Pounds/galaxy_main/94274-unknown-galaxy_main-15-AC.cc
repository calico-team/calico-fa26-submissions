#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <ctime>
#include <random>
#include <chrono>
 
using namespace std;
 
#define _int64 long long
#define mo 998244353

int neigh[4][2]={{0,1},{1,0},{0,-1},{-1,0}};

char a[210][210];
int g[210][210];

int main()
{
	int i,j,k,n,l,t,m,x,y,o,b1,qq,nn,xx,yy,x1,y1,x2,y2;
	vector<pair<int,int> > q;
	ios::sync_with_stdio(false),cin.tie(0);
	scanf("%d",&t);
	for (l=0;l<t;l++)
	{
		scanf("%d%d%d",&m,&n,&qq);
		for (i=0;i<m;i++)
			scanf("%s",a[i]);
		nn=0;
		for (i=0;i<m;i++)
			for (j=0;j<n;j++)
				g[i][j]=-1;
		for (i=0;i<m;i++)
			for (j=0;j<n;j++)
			{
				if ((a[i][j]!='.')||(g[i][j]!=-1)) continue;
				q.clear();
				q.push_back(make_pair(i,j));
				for (k=0;k<q.size();k++)
				{
					x=q[k].first;
					y=q[k].second;
					for (o=0;o<4;o++)
					{
						xx=x+neigh[o][0];
						yy=y+neigh[o][1];
						if ((xx>=0)&&(xx<m)&&(yy>=0)&&(yy<n)&&(g[xx][yy]==-1))
						{
							if ((a[xx][yy]==a[x][y])||(a[xx][yy]=='.')||(a[x][y]=='.'))
							{
								g[xx][yy]=nn;
								q.push_back(make_pair(xx,yy));
							}
						}
					}
				}
				nn++;
			}
		for (o=0;o<qq;o++)
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			if (g[x1][y1]==g[x2][y2]) printf("YES\n");
			else printf("NO\n");
		}
	}
}