#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll MAXN=2e5+5;

ll n, p[MAXN], sm;
vector<ll> adj[MAXN];

void dfs(ll pos, ll prv)
{
    p[pos]=prv;
    for (auto i:adj[pos])
    {
        if (i==prv)
        {
            continue;
        }
        dfs(i, pos);
    }
}

void p1()
{
    cin >> n;
    for (int i=1; i<n; i++)
    {
        ll a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 0);
    p[1]=0;
    for (int i=2; i<=n; i++)
    {
        p[1]+=p[i];
    }
    for (int i=1; i<=n; i++)
    {
        cout << p[i] << " ";
    }
    cout << "\n";
}

void p2()
{
    cin >> n;
    for (int i=1; i<=n; i++)
    {
        cin >> p[i];
        if (i>1 && p[i]!=-1)
        {
            sm+=p[i];
        }
    }
    if (p[1]!=-1)
    {
        for (int i=2; i<=n; i++)
        {
            if (p[i]==-1)
            {
                p[i]=p[1]-sm;
                break;
            }
        }
    }
    for (int i=2; i<=n; i++)
    {
        cout << i << " " << p[i] << "\n";
    }
}

int main()
{
    string ph;
    cin >> ph;
    if (ph=="FIRST")
    {
        p1();
    }
    else
    {
        p2();
    }
}