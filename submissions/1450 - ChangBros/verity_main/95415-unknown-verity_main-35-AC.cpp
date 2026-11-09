#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
#define all(x) (x).begin(), (x).end()
#define forn(var,start,end) for(int var=start;var<end;var++)
#define X first
#define Y second

string ask(string s){
    cout<<s<<endl;
    string res;
    if(!(cin>>res)) exit(0);
    return res;
}
void solve(){
    int t;
    if(!(cin>>t)) return;

    while(t--){
        int n,k;
        if(!(cin>>n>>k)) {return;}
        vector<char> a(k);
        forn(i,0,k) cin>>a[i];

        string s(n,'_');

        forn(i,0,k){
            forn(g,0,n){
                if(s[g]=='_') {
                    s[g]=a[i];
                }
            }
            string res=ask(s);
            if(res=="CORRECT") break;
            s=res;
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}