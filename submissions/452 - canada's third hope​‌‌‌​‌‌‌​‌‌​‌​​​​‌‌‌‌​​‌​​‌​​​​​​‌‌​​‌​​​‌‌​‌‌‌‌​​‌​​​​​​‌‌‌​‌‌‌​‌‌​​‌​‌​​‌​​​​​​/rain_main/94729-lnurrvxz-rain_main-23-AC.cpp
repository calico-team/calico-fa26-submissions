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
    vector<array<int, 3>> est;
    map<int, vi> mp;
    for (int i = 0; i < n; i++)
    {
        int x, y, z; char d; cin >> x >> y >> z >> d;
        if (d == 'N') mp[x+y].push_back(y);
        else est.push_back({ x, y, z });
    }
    for (auto& [_, srt] : mp) sort(srt.begin(), srt.end());
    ll ans = 1LL*n*k;
    for (auto [x, y, z] : est)
    {
        if (mp.find(x+y) != mp.end())
        {
            vi& srt = mp[x+y];
            auto lb = lower_bound(srt.begin(), srt.end(), y);
            auto lb2 = lower_bound(srt.begin(), srt.end(), y-k+1);
            ans -= max(0, (int)(lb-lb2));
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);

    int T; cin >> T;
    while (T-- > 0) solve();

    return 0;
}