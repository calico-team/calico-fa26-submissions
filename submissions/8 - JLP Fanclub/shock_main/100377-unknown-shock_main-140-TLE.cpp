#include <bits/stdc++.h>
using namespace std;

#pragma GCC target ("avx,avx2,fma")
#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")

#define ll long long

const ll MAXQ=2e4+5;

ll n, m, q, r[MAXQ], c[MAXQ], p[MAXQ];
bool sw;
vector<vector<ll>> ans, add, rem;
set<ll> s;

void solve()
{
    cin >> n >> m >> q;
    if (n>m)
    {
        sw=1;
        swap(n, m);
    }
    else
    {
        sw=0;
    }
    for (int i=0; i<q; i++)
    {
        cin >> r[i] >> c[i] >> p[i];
        if (sw)
        {
            swap(r[i], c[i]);
        }
    }
    ans = vector<vector<ll>>(n, vector<ll>(m));
    add = vector<vector<ll>>(m);
    rem = vector<vector<ll>>(m);
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
            ans[i][j]=0;
            add[j].clear();
            rem[j].clear();
        }
        s.clear();
        for (int j=0; j<q; j++)
        {
            if (p[j]*p[j]<(r[j]-i)*(r[j]-i))
            {
                continue;
            }
            ll d=sqrt(p[j]*p[j]-(r[j]-i)*(r[j]-i));
            ll l=c[j]-d, r=c[j]+d;
            l=max(l, (ll)0);
            r=min(r, m-1);
            //cout << i << " " << q << " " << d << " " << l << " " << r << "\n";
            add[l].push_back(j);
            if (r+1<m)
            {
                rem[r+1].push_back(j);
            }
        }
        for (int j=0; j<m; j++)
        {
            for (auto k:add[j])
            {
                s.insert(k);
            }
            for (auto k:rem[j])
            {
                s.erase(k);
            }
            if (s.size()>0)
            {
                ll eq=*(prev(s.end()));
                ans[i][j]=p[eq]*p[eq]-(r[eq]-i)*(r[eq]-i)-(c[eq]-j)*(c[eq]-j)+1;
            }
        }
    }
    if (sw)
    {
        for (int i=0; i<m; i++)
        {
            for (int j=0; j<n; j++)
            {
                cout << ans[j][i] << " ";
            }
            cout << "\n";
        }
    }
    else
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
                cout << ans[i][j] << " ";
            }
            cout << "\n";
        }
    }
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