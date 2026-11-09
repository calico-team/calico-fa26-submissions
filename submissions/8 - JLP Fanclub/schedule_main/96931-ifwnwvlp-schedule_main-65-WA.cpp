#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll MAXN=5e4+5;

ll n, m, k, p[MAXN], ans;
priority_queue<pair<ll, ll>> pq;
vector<ll> nxt, kids[MAXN];

void solve()
{
    cin >> n >> m >> k;
    for (int i=0; i<=n; i++)
    {
        kids[i].clear();
    }
    m++;
    for (int i=1; i<=n; i++)
    {
        cin >> p[i];
        kids[p[i]].push_back(i);
    }
    while (!pq.empty())
    {
        pq.pop();
    }
    pq.push({0, 0});
    ans=-1;
    while (m--)
    {
        nxt.clear();
        for (int i=0; i<k; i++)
        {
            if (pq.empty())
            {
                break;
            }
            ll cur=pq.top().second;
            pq.pop();
            ans++;
            for (auto j:kids[cur])
            {
                nxt.push_back(j);
            }
        }
        for (auto i:nxt)
        {
            pq.push({kids[i].size(), i});
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}