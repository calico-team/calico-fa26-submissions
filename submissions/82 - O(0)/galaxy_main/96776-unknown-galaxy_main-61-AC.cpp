#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
#include <set>
#include <time.h>
#include <numeric>
#include <cmath>
#include <iomanip>
#include <random>
#define all(x) (x).begin(),(x).end()
#define vec(n) vll arr(n);
#define printarr(arr) for(auto i:arr){cout<<i<<" ";}cout<<endl;
#define printdict(dict) for(auto i:dict)cout<<i.first<<": "<<i.second<<endl;
#define printadj(adj) for(ll i=0;i<n;i++){if(!adj[i].empty()){cout<<i<<": ";printarr(adj[i])}}
#define printadj1(adj1) for(ll i=0;i<n;i++){if(!adj1[i].empty()){cout<<i<<": ";f or(auto j:adj1[i]){cout<<'('+j.first+','+j.second+') '} cout<<endl;}}
#define read(arr); for(ll i=0;i<arr.size();i++) cin>>arr[i];
#define readundirected(m) for(ll i=0;i<m;i++){ll a,b; cin>>a>>b; a--;b--; adj[a].pb(b);adj[b].pb(a);}
#define readdirected(m) for(ll i=0;i<m;i++){ll a,b; cin>>a>>b; a--;b--; adj[a].pb(b);}
#define readundirectedweighted(m) for(ll i=0;i<m;i++){ll a,b,w; cin>>a>>b>>w; a--;b--; adj1[a].pb({b,w});adj1[b].pb({a,w});}
#define readdirectedweighted(m) for(ll i=0;i<m;i++){ll a,b,w; cin>>a>>b>>w; a--;b--; adj1[a].pb({b,w});}
#define readfunc(n) for(ll i=0;i<n;i++){ll a;cin>>a;a--;func_adj[i]=a;}
#define grid(n,m) for (ll i=0;i<n;i++){for (ll j=0;j<m;j++) cin>>graph[i][j];}
#define vll vector<ll>
#define sll set<ll>
#define msll multiset<ll>
#define qll queue<ll>
#define pll pair<ll,ll>
#define str string
#define pb push_back
#define ll long long
#define ld long double
using namespace std;
const str alph="abcdefghijklmnopqrstuvwxyz";
const str capalph="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const ll inf=1e6+1;
const ll graph_size=1e3+2;
const ll mod=1e9+7;
const ld pi=3.141592653589793238462643383279502884197;
const ll large=1e18;
const ll small=-1e18;
vll adj[inf];
vector<pll> adj1[inf];
bool visited[inf];
ll level[inf];
ll parent[inf];
ll distance[graph_size][graph_size];
char graph[graph_size][graph_size];
vector<pll> directions={{0,-1},{-1,0},{1,0},{0,1}};
bool floodfill_visited[graph_size][graph_size][2];
// Fast Input/Output
void fastio(){
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
}
// File Input/Output
str fileio(const str filePath=__FILE__){
    ll lastSlash=filePath.find_last_of('/');
    ll lastDot=filePath.rfind('.');
    return filePath.substr(lastSlash+1,lastDot-lastSlash-1);
}
// For Yes Or No Problems
str yes_or_no(bool test){
    if (test){
       return "YES";
    }
    return "NO";
}
ll n,m,q;
ll f(char c){
    if (c=='R'){
        return 0;
    }
    else{
        return 1;
    }
}
char inverse(char c){
    if (c=='R'){
        return 'B';
    }
    else{
        return 'R';
    }
}
ll comp_num=0;
ll comp[graph_size][graph_size];
// Floodfill DFS
void floodfill_dfs(pll coord,char mode){
    ll x=coord.first;
    ll y=coord.second;
    if ((graph[x][y]!='.' and graph[x][y]!=mode) or x<0 or x>=n or y<0 or y>=m or floodfill_visited[x][y][f(mode)]){
        return;
    }
    comp[x][y]=comp_num;
    floodfill_visited[x][y][f(mode)]=1;
    for (auto i:directions){
        floodfill_dfs({x+i.first,y+i.second},mode);
    }
    if (graph[x][y]=='.'){
        floodfill_dfs({x,y},inverse(mode));
    }
}
int main(){
    // auto start_time=chrono::steady_clock::now();
    fastio();
    // str filename=fileio();
    // ifstream cin(filename+".in");
    // ofstream cout(filename+".out");
    cout<<setprecision(20);
    ll t=1;
    cin>>t;
    while (t--){
        cin>>n>>m>>q;
        grid(n,m);
        for (ll i=0;i<n;i++){
            for (ll j=0;j<m;j++){
                floodfill_visited[i][j][0]=0;
                floodfill_visited[i][j][1]=0;
            }
        }
        for (ll i=0;i<n;i++){
            for (ll j=0;j<m;j++){
                if (graph[i][j]=='R'){
                    if (floodfill_visited[i][j][0]){
                        continue;
                    }
                    floodfill_dfs({i,j},'R');
                }
                else{
                    if (floodfill_visited[i][j][1]){
                        continue;
                    }
                    floodfill_dfs({i,j},'B');
                }
                comp_num++;
            }
        }
        while (q--){
            ll a,b,c,d;
            cin>>a>>b>>c>>d;
            cout<<yes_or_no(comp[a][b]==comp[c][d])<<"\n";
        }
    }
    // auto end_time=chrono::steady_clock::now();
    // auto elapsed_time=chrono::duration_cast<chrono::milliseconds>(end_time-start_time);
    // cout<<"Elapsed time: "<<elapsed_time.count()<<" milliseconds\n";
}