/*
K3RO
*/

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <complex>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <optional>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

#define int long long
using ull=unsigned long long;
using ld=long double;
using pii=pair<int,int>;
using vi=vector<int>;
using vvi=vector<vi>;

#define pb push_back
#define fi first
#define se second
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0;i<(n);++i)
#define rng(i,a,b) for(int i=(a);i<(b);++i)
#define per(i,n) for(int i=(n)-1;i>=0;--i)

const bool MULTI=true;
const int MOD=1e9+7;
const int INF=1e18;
mt19937_64 rnd(0xC0FFEEULL);

template<class A,class B> istream& operator>>(istream& i,pair<A,B>& p){ return i>>p.fi>>p.se; }
template<class T> istream& operator>>(istream& i,vector<T>& v){ for(auto& x:v) i>>x; return i; }
template<class T> ostream& operator<<(ostream& o,const vector<T>& v){
    rep(i,sz(v)){ o<<(i?" ":"")<<v[i]; } return o;
}
template<class... T> void input(T&... a){ (cin>>...>>a); }
template<class T,class... Ts> void print(const T& a,const Ts&... b){ cout<<a; ((cout<<' '<<b),...); cout<<'\n'; }
void print(){ cout<<'\n'; }

template<class... T> auto min(T... a){ return std::min({common_type_t<T...>(a)...}); }
template<class... T> auto max(T... a){ return std::max({common_type_t<T...>(a)...}); }
template<class T,class U> bool chmin(T& a,const U& b){ if(b<a){a=b; return true;} return false; }
template<class T,class U> bool chmax(T& a,const U& b){ if(a<b){a=b; return true;} return false; }
int cdiv(int a,int b){ return a/b+((a^b)>0&&a%b); }
int fdiv(int a,int b){ return a/b-((a^b)<0&&a%b); }

int pw(int a,int b,int m=MOD){
    int r=1%m; a%=m; if(a<0) a+=m;
    for(;b>0;b>>=1,a=a*a%m) if(b&1) r=r*a%m;
    return r;
}
int inv(int a,int m=MOD){ return pw(a,m-2,m); }
vi spf;
void sieve(int n){ spf.assign(n+1,0); rng(i,2,n+1) if(!spf[i]) for(int j=i;j<=n;j+=i) if(!spf[j]) spf[j]=i; }

struct chash{
    static ull sm(ull x){ x+=0x9e3779b97f4a7c15; x=(x^(x>>30))*0xbf58476d1ce4e5b9; x=(x^(x>>27))*0x94d049bb133111eb; return x^(x>>31); }
    size_t operator()(ull x) const { static constexpr ull R=0x9e3779b97f4a7c15ULL; return sm(x+R); }
};

struct DSU{
    vi p; DSU(int n=0):p(n,-1){}
    int find(int x){ return p[x]<0?x:p[x]=find(p[x]); }
    bool unite(int a,int b){ a=find(a); b=find(b); if(a==b) return false; if(p[a]>p[b]) swap(a,b); p[a]+=p[b]; p[b]=a; return true; }
    int size(int x){ return -p[find(x)]; }
};
template<class T> struct Compressor{
    vector<T> v;
    void add(const T& x){ v.pb(x); }
    void build(){ sort(all(v)); v.erase(unique(all(v)),v.end()); }
    int get(const T& x) const { return lower_bound(all(v),x)-v.begin(); }
    int size() const { return sz(v); }
};

void solve(){
    int n,r;
    cin>>n>>r;
    deque<int> q;
    bool ok=true;
    rep(i,n){
        int a;
        cin>>a;
        if(!ok) continue;
        while(!q.empty()&&q.front()<=a) q.pop_front();
        if(sz(q)==2){
            ok=false;
            continue;
        }
        q.pb((q.empty()?a:q.back())+r);
    }
    print(ok?"YES":"NO");
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T=1;
    if(MULTI) cin>>T;
    while(T--) solve();
    return 0;
}