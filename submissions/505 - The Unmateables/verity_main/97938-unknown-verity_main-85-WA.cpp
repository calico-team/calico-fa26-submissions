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
    ll n, k;
    cin >> n >> k;
    vector<char> chars(k);
    for (auto &x : chars) cin >> x;

    string ans = "";
    ans.resize(n);
    for (int i = 0; i < n; i++){
        string dummy = "";
        dummy.resize(n, chars[i]);
        cout << dummy << endl;
        string output;
        cin >> output;
        if (output == "CORRECT") return;
        else {
            for (int j = 0; j < output.size(); j++){
                if (output[j] != '_'){
                    ans[j] = output[j];
                }
            }
        }
    }

    cout << ans << endl;
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