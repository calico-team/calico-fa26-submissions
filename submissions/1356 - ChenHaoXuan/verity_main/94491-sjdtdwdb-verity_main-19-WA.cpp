#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
typedef long long ll;

void solve()
{
    int n,k; cin>>n>>k;
    vector<int>v(n);
    for(int i=0;i<n;i++)cin>>v[i];
    string g(n, v[0]);
    for(int i=0;i<n;i++){
        for(auto u : v){
            g[i] = u;
            cout << g << endl;
            string s; cin>>s;
            if(s=="CORRECT")return;
            if(s[i]!='_')break;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t; cin>>t;
    while(t--) solve();
    return 0;
}