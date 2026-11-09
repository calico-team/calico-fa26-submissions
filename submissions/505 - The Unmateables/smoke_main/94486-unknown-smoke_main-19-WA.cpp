// BY THE NAME OF ALMIGHTY ALLAH
// حَسْبُنَا اللَّهُ وَنِعْمَ الْوَكِيلُ

#include <bits/stdc++.h>

#define ll long long int
#define ld long double
#define ull unsigned long long int
#define vi vector<int>
#define vll vector<ll>
#define all(x) (x).begin(), (x).end()

using namespace std;
using u64 = unsigned long long;

const ll INF = 1e18;
const ll NEGINF = -INF;
const ll MOD = 1e9 + 7;

void solve()
{
    ll n,r;
    cin >> n >> r;
    vll a(n);
    for (auto &x : a){
        cin >> x;
    }

    ll p1 = 0;
    ll p2 = 0;

    ll nextUse = 0;
    for (int i = 0; i < 100000; i++){
        if (nextUse >= n){
            cout << "YES" << '\n';
            return;
        }
        if (i + 1 == a[nextUse]){
            if (p1 == 0){p1 += r;}
            else if (p1 != 0 && p2 == 0){p2 += r;}
            else if (p1 != 0 && p2 != 0){cout << "NO" << '\n'; return;}
            nextUse++;
            continue;
        }
        p1 = max(0LL, p1 - 1);
        p2 = max(0LL, p2 - 1);
    }
    cout << "YES" << '\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;

    //------------------------>
    cin >> t;
    //------------------------>

    for (int i = 1; i <= t; i++)
    {
        // cout << "Case " << i << ": ";
        solve();
    }
}