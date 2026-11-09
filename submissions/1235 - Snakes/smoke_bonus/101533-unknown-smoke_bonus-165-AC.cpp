#include <bits/stdc++.h>

using namespace std;
using ll = long long;

string solve(const vector<ll> &a, ll r)
{
    ll prev = 0, finish_time = 0;
    for (auto ai : a)
    {
        if (ai < prev)
            return "NO";

        prev = finish_time;
        if (finish_time < ai)
            finish_time = ai + r;
        else
            finish_time += r;
    }
    return "YES";
}

int main(void)
{
    ios::sync_with_stdio(false), cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        ll  r;
        cin >> n >> r;

        vector<ll> a(n);
        for (auto &ai : a)
            cin >> ai;

        cout << solve(a, r) << endl;
    }
    return 0;
}