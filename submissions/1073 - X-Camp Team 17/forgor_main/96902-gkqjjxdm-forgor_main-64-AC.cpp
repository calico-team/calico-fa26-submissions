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

constexpr bool MULTIPLE_TESTS = 0;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


string S;


void solve1(){
    int n;
    cin>>n;
    vvi t(n);
    for(int i=1,u,v;i<n;i++)cin>>u>>v,u--,v--,t[u].pb(v),t[v].pb(u);
    vi fa(n,-1);
    auto dfs=[&](auto&&dfs,int u)->void{
        for(int v:t[u])if(!~fa[v])fa[v]=u,dfs(dfs,v);
    };
    dfs(dfs,0);
    vi b(n);
    for(int i=0;i<n;i++){
        if(i==0)b[i]=fa[1];
        else if(i==n-1)b[i]=fa[n-1];
        else b[i]=fa[i]+fa[i+1];
    }
    for(int i=0;i<n;i++)cout<<b[i]<<' ';
    cout<<'\n';
}


void solve2(){
    int n;
    cin>>n;
    vi b(n);
    for(int&i:b)cin>>i;
    vi a(n,0);
    for(int i=0;i<n;i++){
        if(b[i]==-1)break;
        a[i+1]=b[i]-a[i];
    }
    for(int i=n-1;~i;i--){
        if(b[i]==-1)break;
        if(i!=n-1)a[i]=b[i]-a[i+1];
        else a[i]=b[i];
    }
    for(int i=1;i<n;i++)cout<<a[i]+1<<' '<<i+1<<'\n';
}



void solve(int _Tid) {
    if(S=="FIRST"){
        solve1();
    }else{
        solve2();
    }
}

signed main() {
    // redirect();
    auto _Tbe = chrono::steady_clock::now();
    fastio;
    // precalc();
    int T = 1;
    cin>>S;
    if constexpr (MULTIPLE_TESTS) cin >> T;
    for (int _ = 1; _ <= T; _++) solve(_);
    auto _Ted = chrono::steady_clock::now();
    // cerr<<"Used time: "<<chrono::duration_cast<chrono::milliseconds>(_Ted - _Tbe).count()<<"ms\n";
    return 0;
}