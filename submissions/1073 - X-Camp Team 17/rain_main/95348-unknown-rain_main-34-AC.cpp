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

void solve(int _Tid) {
    int n,m;
    cin>>n>>m;
    map<int,vector<pair<int,bool>>>mp;
    for(int i=0;i<n;i++){
        int x,y,z;
        char c;
        cin>>x>>y>>z>>c;
        mp[x+y].pb(mkp(x,c=='E'));
    }
    int ans=n*m;
    for(auto&&[P,v]:mp){
        sort(all(v));
        set<int>st;
        for(auto[x,d]:v){
            if(d==0){
                while(st.size()&&*st.begin()<=x-m)st.erase(st.begin());
                ans-=st.size();
            }else{
                st.insert(x);
            }
        }
    }
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