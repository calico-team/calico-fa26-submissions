#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
typedef long long ll;

void solve()
{
    int n,k; cin>>n>>k;
    vector<char>v(n);
    for(int i=0;i<n;i++)cin>>v[i];
    string g(n, '?'); 
    int cnt = n;
    for(int i=0;i<k-1;i++){
        if(cnt == 0) break;
        string s = g;
        for(int j=0;j<n;j++){
            if(s[j] == '?') s[j] = v[i]; 
        }
        cout << s << endl;
        string c; cin>>c;
        if(c=="CORRECT")return;
        for(int j=0;j<n;j++){
            if(c[j]!='_' && g[j]=='?'){
                g[j] = c[j];
                cnt--;
            }
        }
    }
    for(int i=0;i<n;i++) if(g[i]=='?') g[i] = v[k-1];
    cout << g << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t; cin>>t;
    while(t--) solve();
    return 0;
}