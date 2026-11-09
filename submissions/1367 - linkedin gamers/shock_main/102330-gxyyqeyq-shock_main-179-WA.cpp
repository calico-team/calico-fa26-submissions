// Author: JustKitkat
// Status: WIP

#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;

// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define int long long
#define el "\n"
#define arr array
#define ll long long
#define ld long double
#define ii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define vii vector<ii>
#define vllll vector<pll>
#define umap unordered_map
#define uset unordered_set
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define all(a) (a).begin(), (a).end()
#define FOR(a,b) for(int i=a;i<b;++i)
#define DFOR(a,b) for(int i=a;i>=b;--i)
#define JFOR(a,b) for(int j=a;j<b;++j)
#define DJFOR(a,b) for(int j=a;j>=b;--j)
#define show(x) cerr << #x << " is " << x << endl;
#define show2(x,y) cerr << #x << " is " << x << " " << #y << " is " << y << endl;
#define show3(x,y,z) cerr << #x << " is " << x << " " << #y << " is " << y << " " << #z << " is " << z << endl;
#define show_vec(a) { for(auto &x:a)cerr<<x<<' '; cerr<<endl; }
#define discretize(x) sort(x.begin(), x.end()); x.erase(unique(x.begin(), x.end()), x.end());
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
string to_upper(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='a' && a[i]<='z') a[i]-='a'-'A'; return a; }
string to_lower(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='A' && a[i]<='Z') a[i]+='a'-'A'; return a; }
bool prime(ll a) { if (a==1) return 0; for (int i=2;i<=round(sqrt(a));++i) if (a%i==0) return 0; return 1; }
void yes() { cout<<"YES\n"; }
void no() { cout<<"NO\n"; }
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

#define __time__ { auto duration = chrono::duration<double>( /* Show runtime */ \
chrono::high_resolution_clock::now() - BEG); cout<<"Time: "<<duration.count()<<endl;}

// PBDS -> initialise using `ordered_set s;` -> change to greater<int> for reversed order.
// using namespace __gnu_pbds;
// #define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
// #define ordered_multiset tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>

const int MAX_N = 1e5 + 5;
const ll INF = 1e15;
const ll MOD = 1e9+7;
const double PI = acos(-1);
const auto BEG = std::chrono::high_resolution_clock::now(); //Begining of the program
// r is y axis
ll n=0, m=0, k=0, q=0;
void solve(int tc){
    cin>>n>>m>>q;
    vector<tuple<int,int,int>> a(q);
    for(auto &[r,c,p]:a)cin>>r>>c>>p;
    reverse(all(a));
    priority_queue<tuple<int,int,int,int>,vector<tuple<int,int,int,int>>,std::greater<tuple<int,int,int,int>>> pq;
    vector<vector<int>>vis(n,vector<int>(m));
    vector<vector<int>>eqs(n,vector<int>(m, -1));
    int eq_ind=0;
    for(auto &[r,c,p]:a){
        if(eqs[r][c]=-1) eqs[r][c] = eq_ind;
        eq_ind++;
    }
    int ind=0;
    for(auto [R,C,p]:a){
        // bfs pq{latest, r, c, othereq}
        pq.push(make_tuple(ind, R, C, ind));
        while(!pq.empty() and get<0>(pq.top()) == ind){
            auto [eq, r, c, othereq] = pq.top(); pq.pop();
            auto [R,C,p] = a[eq];
            if(vis[r][c]!=0)continue;
            int neweq = othereq;
            if(eqs[r][c] != -1) neweq = eqs[r][c];
            neweq = max(neweq, othereq);
            int pow=p*p - (r-R)*(r-R) - (c-C)*(c-C) + 1;
            // show3(ind, neweq, othereq);
            // show3(r, c, pow);
            // show3(R,C,p);
            // show((int)pq.size());
            if(pow>0){    
                if(vis[r][c]==0)vis[r][c]=pow;
                if(r>0 and !vis[r-1][c]){ // go up
                    pq.push(make_tuple(ind,r-1,c,neweq));
                }
                if(r<n-1 and !vis[r+1][c]){ // go down
                    pq.push(make_tuple(ind,r+1,c,neweq));
                }
                if(c>0 and !vis[r][c-1]){ // go left
                    pq.push(make_tuple(ind,r,c-1,neweq));
                }
                if(c<m-1 and !vis[r][c+1]){ // go right
                    pq.push(make_tuple(ind,r,c+1,neweq));
                }
            }else{
                if(neweq!=ind)pq.push(make_tuple(neweq,r,c,neweq));
            }
            for(auto &x:vis){
                for(auto &xx:x){
                    cout<<xx<<' ';
                }
                cout<<el;
            }
        }
        ++ind;
    }
    // for(auto &x:vis){
    //     for(auto &xx:x){
    //         cout<<xx<<' ';
    //     }
    //     cout<<el;
    // }
    
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    // freopen("out", "w", stdout);
    // freopen("in", "r", stdin);

    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve(t);
    }

    //__time__ //Runtime
}
