//
// Created by Алан


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define bul cout << (ok ? "YES\n" : "NO\n")
#define all(x) begin(x), end(x)
#define mp(a, b) make_pair((a), (b))
#define pb(a) push_back(a);

const ll MOD = 1e9 + 7;
const int INF = 1e9;
const int K = 20;
const int big_N = 200000 + 5;
const ll to_min = -4e18;
constexpr int MAXN = 1e5 + 9;
const long long NEG = -4e18;
using ull = unsigned long long;
const int MAXA = 1e7;



void solve()
{
    int n; cin >> n;
    ll r; cin >> r;
    
    int chargers = 2;
    ll retime = 0;
    bool ok = true;
    
    for(int i = 0; i < n; i++) {
        ll timer; cin >> timer;
        if (!ok) continue;
        
        while (chargers < 2 && retime <= timer) {
            chargers++;
            retime += r;
        }
        
        if (chargers == 0) {
            ok = false;
            continue;
        }
        
        if(chargers == 2){
            retime = timer + r;
        }
        chargers--;
    }
    
    bul;

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }


    return 0;
}
