#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool possible(vector<ll> &data, ll n, ll k)
{
    int availabe = 2;
    int done = 0;
    int time = 0;
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            done++;
            availabe--;
            continue;
        }

        time += data[i] - data[i - 1];
        if (time / k > 0)
        {
            availabe += time / k;
            time = time % k;
        }
        if (availabe >= 2)
        {
            availabe = 2;
            time = 0;
        }
        if (availabe > 0)
        {
            // cout << done << " " << i + 1 << "\n";
            done++;
            availabe--;
        }
    }
    return done >= n;
}
void solve()
{
    ll n, k;
    cin >> n >> k;

    vector<ll> data(n);
    for (int i = 0; i < n; i++)
        cin >> data[i];

    if (possible(data, n, k))
    {
        cout << "YES" << "\n";
    }
    else
    {
        cout << "NO" << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--)
        solve();

    return 0;
}