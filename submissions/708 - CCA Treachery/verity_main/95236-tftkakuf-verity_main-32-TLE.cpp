#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
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
        string guess = "";
        string inp = "";
        FOR(i, 0, n) inp += "_";
        guess = inp;
        int done = 0;
        for(char& i : guess){
            if(i == '_') i = chars[done];
        };
        ++done;
        cout << guess << endl;
        while(inp != "CORRECT"){
            cin >> inp;
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