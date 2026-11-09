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

char s[210000];

int main()
{
	int i,j,k,n,l,t,m,x,y,o,b1,kk;
	string ans;
	vector<char> a;
	ios::sync_with_stdio(false),cin.tie(0);
	scanf("%d",&t);
	for (l=0;l<t;l++)
	{
		scanf("%d%d",&n,&kk);
		a.clear();
		for (i=0;i<kk;i++)
		{
			scanf("%s",s);
			a.push_back(s[0]);
		}
		ans="";
		for (i=0;i<n;i++)
			ans.push_back('_');
		for (i=0;i<a.size();i++)
		{
			for (j=0;j<ans.length();j++)
			{
				if (ans[j]=='_') ans[j]=a[i];
			}
			printf("%s\n",ans.c_str());
			fflush(stdout);
			scanf("%s",s);
			ans=s;
			if (ans=="CORRECT") break;
		}
	}
}