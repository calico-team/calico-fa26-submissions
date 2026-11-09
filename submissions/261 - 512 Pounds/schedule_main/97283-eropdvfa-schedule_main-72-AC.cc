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

int isc[210000];
int p[210000];
vector<int> ch[210000];
int dep[210000];

int main()
{
	int i,j,k,n,l,t,m,x,y,o,b1,ind,ind1,ans,kk;
	vector<int> q;
	vector<int> q1,q2;
	priority_queue<pair<int,int> > pq;
	ios::sync_with_stdio(false),cin.tie(0);
	scanf("%d",&t);
	for (l=0;l<t;l++)
	{
		scanf("%d%d%d",&n,&m,&kk);
		for (i=0;i<n;i++)
			ch[i].clear();
		q.clear();
		for (i=0;i<n;i++)
		{
			scanf("%d",&p[i]);
			p[i]--;
			if (p[i]>=0)
				ch[p[i]].push_back(i);
			else q.push_back(i);
		}
		for (i=0;i<q.size();i++)
		{
			x=q[i];
			for (j=0;j<ch[x].size();j++)
			{
				y=ch[x][j];
				q.push_back(y);
			}
		}
		for (i=q.size()-1;i>=0;i--)
		{
			x=q[i];
			dep[x]=0;
			for (j=0;j<ch[x].size();j++)
			{
				y=ch[x][j];
				dep[x]=max(dep[x],dep[y]+1);
			}
		}
		while (!pq.empty()) pq.pop();
		for (i=0;i<n;i++)
		{
			if (p[i]!=-1) continue;
			pq.push(make_pair(dep[i],i));
		}
		q1.clear();
		ans=0;
		for (i=0;i<m;i++)
		{
			q2.clear();
			for (j=0;j<kk;j++)
			{
				if (pq.empty()) break;
				ans++;
				x=pq.top().second;
				pq.pop();
				for (k=0;k<ch[x].size();k++)
					q2.push_back(ch[x][k]);
			}
			for (j=0;j<q2.size();j++)
			{
				x=q2[j];
				pq.push(make_pair(dep[x],x));
			}
		}

		// q.clear();
		// qq.clear();
		// for (i=0;i<n;i++)
		// {
		// 	if (p[i]!=-1) continue;
		// 	if (isc[i]==1) qq.push_back(i);
		// 	else q.push_back(i);
		// }
		// ind=0;
		// ind1=0;
		// ans=0;
		// for (i=0;i<m;i++)
		// {
		// 	q1.clear();
		// 	qq1.clear();
		// 	for (j=0;j<kk;j++)
		// 	{
		// 		if ((ind==q.size())&&(ind1==qq.size())) break;
		// 		ans++;
		// 		if (ind<q.size())
		// 		{
		// 			x=q[ind];
		// 			ind++;
		// 			for (k=0;k<ch[x].size();k++)
		// 			{
		// 				y=ch[x][k];
		// 				if (isc[y]==1) qq1.push_back(y);
		// 				else q1.push_back(y);
		// 			}
		// 		}
		// 		else
		// 		{
		// 			ind1++;
		// 		}
		// 	}
		// 	for (j=0;j<q1.size();j++)
		// 		q.push_back(q1[j]);
		// 	for (j=0;j<qq1.size();j++)
		// 		qq.push_back(qq1[j]);
		// }
		printf("%d\n",ans);
	}
}