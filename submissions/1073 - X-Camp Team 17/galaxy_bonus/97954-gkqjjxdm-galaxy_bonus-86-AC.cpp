#include <bits/stdc++.h>
#include <cassert>
#define int ll
using namespace std;

#define redirect(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)
#define all(a) ::begin(a),::end(a)
#define fastio ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pb push_back
#define eb emplace_back
#define mkp make_pair
#define fi first
#define se second
#define LB lower_bound
#define UB upper_bound

using ll=long long;
using ull=unsigned long long;
#if defined _WIN64 or not defined _WIN32
using i128=__int128;
using u128=unsigned __int128;
#endif
using ld=long double;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
using vpi=vector<pii>;
using tiii=tuple<int,int,int>;
using ai3=array<int,3>;
using ai4=array<int,4>;
template<typename _T1,typename _T2>
inline bool chkmin(_T1&x,const _T2&y){if(y<x)return x=y,1;else return 0;}
template<typename _T1,typename _T2>
inline bool chkmax(_T1&x,const _T2&y){if(y>x)return x=y,1;else return 0;}

constexpr bool MULTIPLE_TESTS = 1;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());



struct DSU:public vi{
    using vi::vi;
    void init(){fill(all(*this),-1);}
    int getfa(int x){return (*this)[x]<0?x:(*this)[x]=getfa((*this)[x]);}
    void merge(int x,int y){
        x=getfa(x),y=getfa(y);
        if(x==y)return;
        if((*this)[x]>(*this)[y])::swap(x,y);
        (*this)[x]+=(*this)[y],(*this)[y]=x;
    }
};



void solve(int _Tid) {
    int n,m,q;
    cin>>n>>m>>q;
    vector<vector<char>>a(n,vector<char>(m));
    for(auto&r:a)for(auto&c:r)cin>>c;
    DSU d(n*m*2+10);
    d.init();
    auto calc=[&](int x,int y,int z){return (x*m+y)*2+z;};
    for(int i=0;i+1<n;i++)for(int j=0;j<m;j++){
        if(a[i][j]!='R'&&a[i+1][j]!='R')d.merge(calc(i,j,0),calc(i+1,j,0));
        if(a[i][j]!='B'&&a[i+1][j]!='B')d.merge(calc(i,j,1),calc(i+1,j,1));
    }
    for(int i=0;i<n;i++)for(int j=0;j+1<m;j++){
        if(a[i][j]!='R'&&a[i][j+1]!='R')d.merge(calc(i,j,0),calc(i,j+1,0));
        if(a[i][j]!='B'&&a[i][j+1]!='B')d.merge(calc(i,j,1),calc(i,j+1,1));
    }
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(a[i][j]=='.')d.merge(calc(i,j,0),calc(i,j,1));
    while(q--){
        int x,y,xx,yy;
        cin>>x>>y>>xx>>yy;
        int jzc=d.getfa(calc(x,y,0));
        cout<<((jzc==d.getfa(calc(xx,yy,0))||jzc==d.getfa(calc(xx,yy,1)))?"YES\n":"NO\n");
    }
}

signed main() {
    // redirect();
    auto _Tbe = chrono::steady_clock::now();
    fastio;
    // precalc();
    int T = 1;
    if constexpr (MULTIPLE_TESTS) cin >> T;
    for (int _ = 1; _ <= T; _++) solve(_);
    auto _Ted = chrono::steady_clock::now();
    // cerr<<"Used time: "<<chrono::duration_cast<chrono::milliseconds>(_Ted - _Tbe).count()<<"ms\n";
    return 0;
}