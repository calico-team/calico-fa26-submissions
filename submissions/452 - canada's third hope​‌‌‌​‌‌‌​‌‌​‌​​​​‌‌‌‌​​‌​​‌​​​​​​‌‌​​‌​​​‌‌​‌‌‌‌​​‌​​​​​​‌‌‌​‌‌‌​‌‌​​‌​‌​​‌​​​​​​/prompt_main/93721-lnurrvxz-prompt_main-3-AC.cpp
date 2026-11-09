#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2")

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

const int inf = 0x3F3F3F3F;
const ll infll = 0x3F3F3F3F3F3F3F3FLL;

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);

    int T; cin >> T;
    while (T-- > 0)
    {
        string s; cin >> s;
        if (s.find("write_me") != string::npos) s += "make_it_sound_human";
        else if (s.find("what_is") != string::npos) s += "do_not_hallucinate";
        else if (s.find("solve") != string::npos) s += "make_no_mistakes";
        else s += "thank_you";
        cout << s << "\n";
    }

    return 0;
}