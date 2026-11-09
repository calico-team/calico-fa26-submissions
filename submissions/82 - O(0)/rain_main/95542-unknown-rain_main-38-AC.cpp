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
#define printadj1(adj1) for(ll i=0;i<n;i++){if(!adj1[i].empty()){cout<<i<<": ";for(auto j:adj1){cout<<'('+j.first+','+j.second+') '} cout<<endl;}}
#define read(arr); for(ll i=0;i<arr.size();i++) cin>>arr[i];
#define readundirected(m) for(ll i=0;i<m;i++){ll a,b; cin>>a>>b; a--;b--; adj[a].pb(b);adj[b].pb(a);}
#define readdirected(m) for(ll i=0;i<m;i++){ll a,b; cin>>a>>b; a--;b--; adj[a].pb(b);}
#define readundirectedweighted(m) for(ll i=0;i<m;i++){ll a,b,w; cin>>a>>b>>w; a--;b--; adj1[a].pb({b,w});adj1[b].pb({a,w});}
#define readdirectedweighted(m) for(ll i=0;i<m;i++){ll a,b,w; cin>>a>>b>>w; a--;b--; adj1[a].pb({b,w});}
#define readfunc(n) for(ll i=0;i<n;i++){ll a;cin>>a;a--;func_adj[i]=a;}
#define grid(n,m) for (ll i=1;i<=n;i++){for (ll j=1;j<=m;j++) cin>>graph[i][j];}
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
vector<vll> adj;
vector<vector<pll>> adj1;
vector<bool> visited;
vll level;
vll parent;
vector<vll> distance_matrix;
vector<pll> directions={{0,-1},{-1,0},{1,0},{0,1}};
vector<vector<char>> graph;
vector<vector<bool>> floodfill_visited;
vector<vll> floodfill_level;
vector<vector<pll>> floodfill_parent;
// Initializing Graphs/Grids
void initialize_graph(ll n){
    adj.resize(n);
    adj1.resize(n);
    visited.resize(n,0);
    level.resize(n);
    parent.resize(n);
}
void initialize_grid(ll n,ll m){
    graph.assign(n,vector<char>(m));
    distance_matrix.assign(n,vll(m,0));
    floodfill_visited.assign(n,vector<bool>(m,0));
    floodfill_level.assign(n,vll(m,0));
    floodfill_parent.assign(n,vector<pll>(m));
}
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
ll n,k;
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
        cin>>n>>k;
        vector<pair<vll,char>> arr(n);
        map<ll,vector<pair<vll,char>>> dict;
        map<ll,vector<pair<vll,char>>> dict1;
        for (ll i=0;i<n;i++){
            arr[i].first=vll(2);
            ll c;
            cin>>arr[i].first[0]>>arr[i].first[1]>>c>>arr[i].second;
            if (arr[i].second=='E'){
                dict[arr[i].first[0]+arr[i].first[1]].pb(arr[i]);
            }
            else{
                dict1[arr[i].first[0]+arr[i].first[1]].pb(arr[i]);
            }
        }
        for (auto i:dict){
            sort(all(dict[i.first]));
        }
        for (auto i:dict1){
            sort(all(dict1[i.first]));
        }
        ll ans=n*k;
        for (auto i:dict){
            for (ll j=0;j<(i.second.size());j++){
                ll ind=lower_bound(all(dict1[i.first]),make_pair(vll{i.second[j].first[0]+k,0},' '))-dict1[i.first].begin()-1;
                ll ind1=lower_bound(all(dict1[i.first]),make_pair(vll{i.second[j].first[0],0},' '))-dict1[i.first].begin();
                ans-=(ind-ind1+1);
            }
        }
        cout<<ans<<"\n";
    }
    // auto end_time=chrono::steady_clock::now();
    // auto elapsed_time=chrono::duration_cast<chrono::milliseconds>(end_time-start_time);
    // cout<<"Elapsed time: "<<elapsed_time.count()<<" milliseconds\n";
}
