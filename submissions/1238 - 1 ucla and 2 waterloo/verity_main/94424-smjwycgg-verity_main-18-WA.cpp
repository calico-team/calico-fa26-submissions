#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>  
#define pll pair<ll, ll>
#define pdd pair<double, double>
#define vi vector<int>
#define vl vector<ll>
#define vs vector<string>
#define vb vector<bool>
#define vd vector<double>
#define vpii vector<pii>
#define bitcnt __builtin_popcount
void precise() {cout << fixed << setprecision(7);}
ll MOD = 1e9 + 7;
ll BASE = 31;

int t;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> t;
    while (t--) {
        string s;
        int n, k;
        cin >> n >> k;

        char c;
        for (int i = 0; i < k; i++) {
            cin >> c;
            s += c;
        }

        string res = "";
        string ans(n, '*');
        for (int i = 0; i < k; i++) {
            cout << string(n, s[i]) << endl;
            cin >> res;
            for (int j = 0; j < n; j++) {
                if (res[j] != '_') {
                    ans[j] = s[i];
                }
            }
        }

        cout << ans << endl;
        int correct;
        cin >> correct;
    }
    return 0;
}