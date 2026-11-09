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
const int maxn=205;

int N,M,Q,cnt;
int vis[maxn][maxn][2];
char mp[maxn][maxn];

void BFS(int x, int y, int z) {
    queue<tuple<int,int,int>> q;
    q.push({x,y,z});
    vis[x][y][z]=cnt;
    while(!q.empty()) {
        auto [x,y,z]=q.front();
        q.pop();
        if(mp[x][y]=='.' && !vis[x][y][z^1]) {
            vis[x][y][z^1]=cnt;
            q.push({x,y,z^1});
        }
        for(int d=0;d<4;d++) {
            int nx=x+dx[d],ny=y+dy[d];
            if(nx<1 || nx>N || ny<1 || ny>M) {
                continue;
            }
            if(vis[nx][ny][z]){
                continue;
            }
            if(z==0 && mp[nx][ny]=='B'){
                continue;
            }
            if(z==1 && mp[nx][ny]=='R'){
                continue;
            }
            vis[nx][ny][z]=cnt;
            q.push({nx,ny,z});
        }
    }

}

void solve() {
//--------Initiallize--------
//--------Input--------
    cin>>N>>M>>Q;
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=M;j++) {
            cin>>mp[i][j];
            vis[i][j][0]=vis[i][j][1]=0;
        }
    }
    cnt=0;
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=M;j++) {
            if(mp[i][j]=='R') {
                if(!vis[i][j][0]) {
                    cnt++;
                    BFS(i,j,0);
                }
            } else {
                if(!vis[i][j][1]) {
                    cnt++;
                    BFS(i,j,1);
                }
            }
        }
    }
    for(int i=1;i<=Q;i++) {
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        x1++,y1++,x2++,y2++;
        if(vis[x1][y1][1]==vis[x2][y2][mp[x2][y2]=='B']) {
            cout<<"YES"<<endl;
        } else {
            cout<<"NO"<<endl;
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int TT=1;
    cin>>TT;
    for(int i=1;i<=TT;++i) {
        solve();
    }
    return 0;
}