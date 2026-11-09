#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define endl '\n'
#define int long long
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int BLOCK = 90;
void solve(){
    string s;cin>>s;
    if(s.contains("write_me")) s+="make_it_sound_human";
    else if(s.contains("what_is")) s+="do_not_hallucinate";
    else if(s.contains("solve")) s+="make_no_mistakes";
    else s += "thank_you";
    cout << s << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t=1; cin>>t;
    while(t--)solve();
}
