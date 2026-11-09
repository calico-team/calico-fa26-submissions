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
        //write_me --> make_it_sound_human
        //what_is --> do_not_hallucinate
        //solve --> make_no_mistakes
        //thank_you
        string n; cin >> n;
        if(n.contains("write_me"))
              cout << n << "make_it_sound_human\n";
        else if(n.contains("what_is")) cout << n << "do_not_hallucinate\n";
        else if(n.contains("solve")) cout << n << "make_no_mistakes\n";
        else cout << n << "thank_you\n";
    }
    return 0;
}