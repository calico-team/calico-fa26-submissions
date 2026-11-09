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
    string s; cin >> s;
    if (s.find("write_me") != string::npos)
    {
        s += "make_it_sound_human";
    }
    else if (s.find("what_is") != string::npos)
    {
        s += "do_not_hallucinate";
    }
    else if (s.find("solve") != string::npos)
    {
        s += "make_no_mistakes";
    }
    else
    {
        s += "thank_you";
    }

    cout << s << "\n";

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
