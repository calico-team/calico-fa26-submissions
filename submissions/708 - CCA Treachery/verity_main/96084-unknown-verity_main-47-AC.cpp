#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define pb push_back
#define ins insert
#define lb lower_bound
#define ub upper_bound
#define str string
#define vec vector
#define prq priority_queue
#define mprq(x) priority_queue<x, vec<x>, greater<x>>
#define FOR(i, a, b) for(int i = a; i < b; ++i)
#define print(x) for(auto i : x) {cout << i << " ";} cout << endl;
#define cinVec(x) for(auto& i : x) cin >> i;


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        vec<char> chars(k); cinVec(chars);
        string inp(n, '_');
        string guess = inp;
        int done = 0;
        for(char& i : guess){
            if(i == '_') i = chars[done];
        };
        ++done;
        cout << guess << endl;
        while(true){
            cin >> inp;
            if(inp == "CORRECT") break;
            guess = inp;
            for(char& i : guess){
                if(i == '_') i = chars[done];
            };
            ++done;
            cout << guess << endl;
        }
    }
    return 0;
}