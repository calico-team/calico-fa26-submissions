#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define int long long
#define double long double
#define vi vector<int>
#define vvi vector<vector<int>>
#define pii pair<int,int>
#define sz(s) s.size()
#define all(x) x.begin(), x.end()
#define pb push_back
#define fi first
#define se second

#define dbg(x) cerr << #x << " = " << x << '\n'

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

string query(string s) {
    cout<<""<<s<<"\n";
    cout.flush();

    string t;
    cin>>t;
    return t;
}

void solve() {
    int n,k;
    cin>>n>>k;

    vector<char> ch (k);
    for(int i=0;i<k;i++)
        cin>>ch[i];

    string ans (n, '_');
    for(char c:ch) {
        string t (n, c);
        string cr=query(t);

        if(cr=="CORRECT") {
            return;
        }

        for(int i=0;i<n;i++) {
            if(cr[i]!='_'&&ans[i]=='_')
                ans[i]=cr[i];
        }
    }
    cout<<ans<<"\n";
    cout.flush();

    string s;
    cin>>s;
    

}

signed main () {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t=1;
    cin>>t;

    while(t>0) {
        solve();
        t--;
    }
}