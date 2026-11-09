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
        // if((*this)[x]>(*this)[y])::swap(x,y);
        (*this)[x]+=(*this)[y],(*this)[y]=x;
    }
};



void solve(int _Tid) {
    int n,m,q;
    cin>>n>>m>>q;
    bool flg=0;
    if(n>m)flg=1,swap(n,m);
    vvi a(n,vi(m,0));
    vector<DSU>d(n,DSU(m+3,-1));
    vector<ai3>b(q);
    for(auto&t:b){
        cin>>t[0]>>t[1]>>t[2];
        if(flg==1)swap(t[0],t[1]);
    }
    reverse(all(b));
    for(auto[x,y,z]:b){
        for(int i=x-z;i<=x+z;i++){
            int tmp=(z*z-(i-x)*(i-x));
            int v=sqrtl((ld)tmp)-1;
            while(v<0||v*v<=tmp)v++;
            v--;
            int mn=y-v,mx=y+v;
            // cerr<<x<<' '<<y<<' '<<z<<' '<<i<<' '<<mn<<' '<<mx<<'\n';
            for(int j=d[i].getfa(mn);j<=mx;j=d[i].getfa(j)){
                a[i][j]=tmp-(j-y)*(j-y)+1;
                d[i].merge(j+1,j);
            }
        }
    }
    if(!flg){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++)cout<<a[i][j]<<' ';cout<<'\n';
        }
    }else{
        for(int j=0;j<m;j++){
            for(int i=0;i<n;i++)cout<<a[i][j]<<' ';cout<<'\n';
        }
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