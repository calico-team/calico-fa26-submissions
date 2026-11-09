#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(a) a.begin(), a.end()
#define sz(a) int(a.size())
#define fastio ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)


const int MAXN = 2e5 + 5;
vector<int> ady[MAXN];
int par[MAXN];

void dfs(int s, int p = 0)
{
    par[s] = p;
    for(auto u : ady[s])
    {
        if(u == p) continue;
        dfs(u, s);
    }
}
void first_phase()
{
    int n;
    cin >> n;

    for(int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        ady[a].push_back(b);
        ady[b].push_back(a);
    }
    dfs(1);
    for(int i = 1; i <= n; i++) cout << par[i] << " ";
}

void second_phase()
{
    int n;
    cin >> n;

    vector<int> par(n + 1);
    for(int i = 1; i <= n; i++)
    {
        cin >> par[i];
    }

    for(int i = 2; i <= n; i++)
    {
        cout << par[i] << " " << i << "\n";
    }
}

int main()
{
    string str;
    cin >> str;

    if(str == "FIRST") first_phase();
    else second_phase();
    return 0;
}