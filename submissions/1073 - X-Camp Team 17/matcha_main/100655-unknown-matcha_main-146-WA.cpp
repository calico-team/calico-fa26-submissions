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


using ui=unsigned;

struct Lb{
    array<ull,65>a;
    ull add(ull x){
        for(int i=63,flg=1;~i;i--)if(x>>i&1)a[i]||!flg?x^=a[i]:(a[i]=x,flg=0);
        return x;
    }
    ull query(ull x)const{
        for(int i=63;~i;i--)if(~x>>i&1)x^=a[i];
        return x;
    }
    void clear(){a.fill(0);}
    void merge(const Lb&b){
        for(int i=0;i<64;i++)if(b.a[i])add(b.a[i]);
    }
};

void solve(int _Tid) {
    int n;
    cin>>n;
    vi l(n),r(n);
    for(int&i:l)cin>>i;
    for(int&i:r)cin>>i;
    vector<Lb>a(n);
    for(auto&i:a)i.clear();
    for(int i=0;i<n;i++){
        if(i)a[i]=a[i-1];
        a[i].add(r[i]^l[i]);
    }
    Lb b;
    b.clear();
    int ans=0;
    int sm=0;
    for(int i=0;i<n;i++)sm^=l[i];
    for(int i=n-1;~i;i--){
        Lb tmp;
        if(i)tmp=a[i-1];
        else tmp.clear();
        tmp.merge(b);
        for(int j=0;j<31;j++)if((l[i]>>j)!=(r[i]>>j)){
            if(r[i]>>j&1){
                int val=sm^l[i]^r[i]^(1<<j);
                val=tmp.query(val);
                chkmax(ans,(val>>j<<j)|((1<<j)-1));
            }
            if(~l[i]>>j&1){
                int val=sm^(1<<j);
                val=tmp.query(val);
                chkmax(ans,(val>>j<<j)|((1<<j)-1));
            }
        }
        b.add(r[i]^l[i]);
    }
    chkmax(ans,b.query(sm));
    cout<<ans<<'\n';
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