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

void solve()
{
    int n, k; cin >> n >> k;
    vector<char> a(k);
    for (int i = 0; i < k; i++) cin >> a[i];
    auto qry = [&](string s) -> string
    {
        cout << s << "\n" << flush;
        string res; cin >> res;
        return res;
    };
    string ans(n, '_');
    for (int i = 0; i < k; i++)
    {
        string res = qry(string(n, a[i]));
        if (res == "CORRECT") return;
        for (int j = 0; j < n; j++)
        {
            if (res[j] != '_')
                ans[j] = a[i];
        }
    }
    cout << ans << "\n" << flush;
    string res; cin >> res;
    assert(res == "CORRECT");
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);

    int T; cin >> T;
    while (T-- > 0) solve();

    return 0;
}