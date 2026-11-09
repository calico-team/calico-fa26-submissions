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
    int r; cin >> r;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    
    ll mn = 10000000;
    for(int i = 1; i < n; i++){
        ll ku = a[i] - a[i - 1];
        if (mn > ku) mn = ku;
    }
    if (mn < r) {
        cout << "NO\n";
    }
    else{
        cout << "YES\n";
    }

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
