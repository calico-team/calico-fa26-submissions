#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <cstring>
#include <map>
#include <bitset>
#include <set>
#include <queue>
#include <cmath>
#include <tuple>
#include <stack>
#include <numeric>
#include <climits>
#include <deque> 
#include <chrono>
#include <unordered_map>
#include <cstring>
#include <random>
using namespace std;
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#define systemwait system("read -p \"Press Enter to continue...\"");
#define debugbreak exit(0)
#else
#define debug(x...) 
#define systemwait
#define debugbreak
#endif

#define LL long long
#define endl '\n'
#define all(x) (x).begin(),(x).end()
#define sqsq(x) (x)*(x)
#define pii pair<int,int>
#define vi vector<int>
#define vii vector<pii>
#define tiii tuple<int,int,int>
#define vstto vector<Edge>
#define fi first
#define se second
#define pb push_back

const int INF=1e9+7;
const int MOD=1e9+7;
//const int MOD=998244353;
const int dx[4]={0,(-1),0,1};
const int dy[4]={(-1),0,1,0};
const int maxch=26;
const int maxn=2e5+10;

vi mp[maxn];
int a[maxn],sum;

void DFS(int u) {
    for(auto v:mp[u]) {
        if(v==a[u]) {
            continue;
        } else {
            a[v]=u;
            DFS(v);
            sum^=u;
        }
    }
}

void solve() {
//--------Initiallize--------
//--------Input--------
    string phase;
    cin>>phase;
    if(phase=="FIRST") {
        int N;
        sum=0;
        cin>>N;
        for(int i=1;i<=N;i++) {
            mp[i].clear();
            a[i]=0;
        }
        for(int i=1;i<N;i++) {
            int u,v;
            cin>>u>>v;
            mp[u].pb(v);
            mp[v].pb(u);
        }
        DFS(1);
        a[1]=sum;
        for(int i=1;i<=N;i++) {
            cout<<a[i]<<" ";
        }
        cout<<endl;
        cout.flush();
    } else {
        int N;
        cin>>N;
        for(int i=1;i<=N;i++) {
            cin>>a[i];
        }
        for(int i=2;i<=N;i++) {
            if(a[i]==-1) {
                int tmp=a[1];
                for(int j=2;j<=N;j++) {
                    if(j!=i) {
                        tmp^=a[j];
                    }
                }
                a[i]=tmp;
            }
        }
        for(int i=2;i<=N;i++) {
            cout<<i<<" "<<a[i]<<endl;
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int TT=1;
    //cin>>TT;
    for(int i=1;i<=TT;++i) {
        solve();
    }
    return 0;
}