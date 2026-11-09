#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 5;
const int LOG = 17, MAXB = 1<<LOG;
const int MOD = 998244353;
const int mod = 1e9 + 7;
const int K = 5e3+5;

void solve(){
    int n,m,k;cin >> n >> m >> k;
    vector<vector<int>> ch(n+1);
    vector<int> p;
    for(int i = 1 ; i <= n ;i ++){
        int pi;cin >> pi;
        if(pi != 0)ch[pi].push_back(i);
        else p.push_back(i);
    }
    priority_queue<pair<int,int>> pq;
    for(auto par: p){
        pq.push({ch[par].size(), par});
    }
    int ans = 0;
    while(m--){
        vector<pair<int,int>> Cur;
        int u = k;
        while(u>0 and pq.size()>0){
            Cur.push_back(pq.top());
            pq.pop();
            u--;
        }
        ans += (k - u);
        for(auto it : Cur){
            for(auto child : ch[it.second]){
                pq.push({ch[child].size(),child});
            }
        }
    }
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(0); //DO NOT USE THIS IN INTERACTIVE
    cin.tie(0), cout.tie(0);
    cout << fixed<<setprecision(9);
    int t = 1;
    cin >> t;
    while(t --){
        solve();
    }
}
