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

#define ll long long
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define vi vector<int>
#define pi pair<int, int>
#define vp vector<pair<int, int>>
#define um unordered_map<int, int>
#define us unordered_set<int>
#define mod 1000000007
#define SORT(x) sort(x.begin(), x.end())
#define SUM(x) accumulate(x.begin(), x.end(), 0LL)

int a[200001];
int f[200001];
vector<int> con[200001];

int main()
{
    int t,p;
    scanf("%d",&t);
    for (p=1;p<=t;p++) {
        int n,m;
        int i,j,k;
        scanf("%d%d",&n,&m);
        for (i=1;i<=n;i++)
            scanf("%d",&a[i]);
        int la=m;
        int lb=m;
        a[0]=0;
        for (i=1;i<=n;i++) {
            if (la<lb) {
                int tt=a[i]-a[i-1];
                if (lb+tt<=m) {
                    lb+=tt;
                    tt=0;
                } else {
                    tt-=(m-lb);
                    lb=m;
                    la+=tt;
                    if (la>m) la=m;
                }
            } else {
                int tt=a[i]-a[i-1];
                if (la+tt<=m) {
                    la+=tt;
                    tt=0;
                } else {
                    tt-=(m-la);
                    la=m;
                    lb+=tt;
                    if (lb>m) lb=m;
                }
            }
            if (la<m&&lb<m) break;
            if (la==m) la=0;
            else lb=0;
        }
        if (i<=n) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}
