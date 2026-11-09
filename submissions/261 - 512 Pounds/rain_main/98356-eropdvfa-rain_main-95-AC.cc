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

char s[100];

int main()
{
	int i,j,k,n,l,t,m,x,y,z,o,b1,ind1,ind2,ind,indc,ss,kk,py;
	vector<pair<int,pair<int,int> > > a1,a2;
	vector<int> aa;
	_int64 ans;
	ios::sync_with_stdio(false),cin.tie(0);
	scanf("%d",&t);
	for (l=0;l<t;l++)
	{
		scanf("%d%d",&n,&kk);
		a1.clear();
		a2.clear();
		for (i=0;i<n;i++)
		{
			scanf("%d%d%d%s",&x,&y,&z,s);
			if (s[0]=='E') a1.push_back(make_pair(x+y,make_pair(x,y)));
			else a2.push_back(make_pair(x+y,make_pair(x,y)));
		}
		ans=(_int64)n*kk;
		sort(a1.begin(),a1.end());
		sort(a2.begin(),a2.end());
		ind1=0;ind2=0;
		for (ss=0;ss<=200000;ss++)
		{
			aa.clear();
			while ((ind1<a1.size())&&(a1[ind1].first==ss))
			{
				y=a1[ind1].second.second;
				ind1++;
				if ((aa.size()>0)&&(y==aa.back())) ans-=n;
				else aa.push_back(y);
			}
			sort(aa.begin(),aa.end());
			ind=aa.size();indc=aa.size();
			py=(1<<30);
			while ((ind2<a2.size())&&(a2[ind2].first==ss))
			{
				y=a2[ind2].second.second;
				ind2++;
				if (y==py)
				{
					ans-=n;
					continue;
				}
				// cerr<<"y:"<<aa[indc-1]<<" "<<y<<endl;
				while ((ind-1>=0)&&(aa[ind-1]>=y)) ind--;
				while ((indc-1>=0)&&(aa[indc-1]>=y+kk)) indc--;
				// cerr<<"ss,ind:"<<ss<<" "<<indc<<" "<<ind<<endl;
				ans-=(indc-ind);
				py=y;
			}
		}
		printf("%lld\n",ans);

	}
}