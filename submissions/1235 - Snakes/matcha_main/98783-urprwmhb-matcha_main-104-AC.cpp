#include <bits/stdc++.h>

using namespace std;
using ii = pair<int, int>;

int xor_max(int a, int b)
{
    if (a < 0 or b < 0)
        return -1;
    int x = a & b;
    if (x == 0)
        return a | b;
    int k = 32 - __builtin_clz((unsigned)x);
    return (a | b) | ((1 << k) - 1);
}

int solve(vector<ii> lr)
{
    int ans = 0, x = 0;
    for (int b = 29; b >= 0; --b)
    {
        int bit = 1 << b, mask = bit - 1;
        int cur = (x >> b) & 1, cnt = 0;
        array<int, 2> dp = {0, -1};
        vector<ii>    nxt;
        nxt.reserve(lr.size());

        for (auto [l, r] : lr)
        {
            if ((l & bit) == (r & bit))
            {
                cur ^= bool(l & bit);
                nxt.emplace_back(l & mask, r & mask);
            }
            else
            {
                int lo = mask - l, hi = r - bit;
                dp = {max(xor_max(dp[0], lo), xor_max(dp[1], hi)),
                      max(xor_max(dp[1], lo), xor_max(dp[0], hi))};
                ++cnt;
            }
        }

        x &= mask;
        if (cnt)
        {
            int p = cur ^ 1;
            ans |= bit;
            if ((cnt - p) & 1)
                x ^= mask;
            nxt.emplace_back(0, dp[p]);
        }
        else if (cur)
            ans |= bit;

        lr.swap(nxt);
    }
    return ans;
}

int main(void)
{
    ios::sync_with_stdio(false), cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<ii> lr(n);
        for (auto &[l, r] : lr)
            cin >> l;
        for (auto &[l, r] : lr)
            cin >> r;
        cout << solve(lr) << '\n';
    }
    return 0;
}
