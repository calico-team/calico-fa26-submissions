#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll MAXN=105;
const ll MAXK=26;

ll n, k;
char a[MAXK];
bool works[MAXN][MAXK];
map<char, ll> rev;

void solve()
{
    cin >> n >> k;
    rev.clear();
    for (int i=0; i<k; i++)
    {
        cin >> a[i];
        rev[a[i]]=i;
    }
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<k; j++)
        {
            works[i][j]=1;
        }
    }
    string res(n, '_');
    string ans(n, a[0]);
    while (true)
    {
        cout << ans << endl;
        cin >> res;
        if (res=="CORRECT")
        {
            return;
        }
        for (int i=0; i<n; i++)
        {
            if (res[i]!='_')
            {
                continue;
            }
            works[i][rev[ans[i]]]=0;
            for (int j=0; j<k; j++)
            {
                if (works[i][j])
                {
                    ans[i]=a[j];
                    break;
                }
            }
        }
    }
}

int main()
{
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}