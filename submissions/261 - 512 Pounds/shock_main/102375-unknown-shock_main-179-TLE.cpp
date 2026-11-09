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

vector<long long> f[1001];
int r[20001];
int c[20001];
int e[20001];

void init(int x,int y) {
    f[x].resize(4*y+10);
    fill(f[x].begin(), f[x].end(), 0);
}

long long sp(int x) {
    return x*(long long)x;
}

void add(int x,int y,int l,int r,int ll,int rr,int xx,int yy,int zz) {
    if (f[x][y]>0) return;
    if (l==ll&&r==rr&&ll==rr) {
        f[x][y]=sp(zz)-sp(x-xx)-sp(rr-yy)+1;
        if (f[x][y]<=0) f[x][y]=0;
    } else {
        int m=(l+r)/2;
        if (rr<=m) add(x,2*y,l,m,ll,rr,xx,yy,zz);
        else {
            if (ll<=m) {
                add(x,2*y,l,m,ll,m,xx,yy,zz);
                add(x,2*y+1,m+1,r,m+1,rr,xx,yy,zz);
            } else add(x,2*y+1,m+1,r,ll,rr,xx,yy,zz); 
        }
        if (f[x][2*y]>0&&f[x][2*y+1]>0) f[x][y]=1;
    }
}

long long query(int x,int y,int l,int r,int p) {
    if (l==r) return f[x][y];
    else {
        int m=(l+r)/2;
        if (p<=m) return query(x,2*y,l,m,p);
        else return query(x,2*y+1,m+1,r,p);
    }
}

int gao(int dr,int drr,int de,int m) {
    int low=0;
    int high=m;
    while (low<high) {
        int mid=(low+high+1)/2;
        // printf("%d %d %d %lld\n",low,high,mid,sp(de)-sp(drr-dr)-sp(mid)+1);
        if (sp(de)-sp(drr-dr)-sp(mid)+1<=0) high=mid-1;
        else low=mid;
    }
    return low;
}

int main()
{
    int t,p;
    ios::sync_with_stdio(false),cin.tie(0);
    cin>>t;
    // scanf("%d",&t);
    for (p=1;p<=t;p++) {
        int n,m;
        int i,j,k;
        int tt,pp;
        // scanf("%d%d%d",&n,&m,&tt);
        cin>>n>>m>>tt;
        bool flag=true;
        if (n>m) {
            flag=false;
            k=n;
            n=m;
            m=k;
        }
        for (pp=1;pp<=tt;pp++) {
            // scanf("%d%d%d",&r[pp],&c[pp],&e[pp]);
            cin>>r[pp]>>c[pp]>>e[pp];
            r[pp]++;
            c[pp]++;
            if (!flag) {
                k=r[pp];
                r[pp]=c[pp];
                c[pp]=k;
            }
        }
        for (i=1;i<=n;i++)
            init(i,m);
        for (pp=tt;pp>=1;pp--) {
            for (i=r[pp];i>=r[pp]-e[pp]&&i>=1;i--) {
                //int cur=(int)sqrt((double)(sp(e[pp])+1-sp(r[pp]-i))+0.5);
                int cur=gao(i,r[pp],e[pp],m);
                //printf("%d %d %d %d\n",i,cur,max(1,c[pp]-cur),min(m,c[pp]+cur));
                add(i,1,1,m,max(1,c[pp]-cur),min(m,c[pp]+cur),r[pp],c[pp],e[pp]);
            }
            for (i=r[pp]+1;i<=r[pp]+e[pp]&&i<=n;i++) {
                //int cur=(int)sqrt((double)(sp(e[pp])+1-sp(i-r[pp]))+0.5);
                int cur=gao(i,r[pp],e[pp],m);
                add(i,1,1,m,max(1,c[pp]-cur),min(m,c[pp]+cur),r[pp],c[pp],e[pp]);
            }
        }
        if (flag) {
            for (i=1;i<=n;i++) {
                for (j=1;j<=m;j++)
                    cout<<query(i,1,1,m,j)<<" ";
                    // printf("%lld ",query(i,1,1,m,j));
                cout<<endl;
                // printf("\n");
            }
        } else {
            for (j=1;j<=m;j++) {
                for (i=1;i<=n;i++)
                    cout<<query(i,1,1,m,j)<<" ";
                    // printf("%lld ",query(i,1,1,m,j));
                cout<<endl;
                // printf("\n");
            }
        }
    }
    return 0;
}
