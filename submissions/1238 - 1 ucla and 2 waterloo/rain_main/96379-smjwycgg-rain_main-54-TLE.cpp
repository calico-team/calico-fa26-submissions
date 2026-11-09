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

ll t, n, k;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> t;
    while (t--) {
        cin >> n >> k;
        vector<vector<int>> up;
        vector<vector<int>> across;
        int x, y, z;
        char d;
        for (int i = 0; i < n; i++) {
            cin >> x >> y >> z >> d;
            if (d == 'N') {
                up.push_back({x, y});
            } else {
                across.push_back({x, y});
            }
        }

        // total = drones * k - (collisions)
        // will collide if 
        // b = up drones, a = across drones
        // bx = ax + t
        // by + t = ay
        // ax + t = bx
        // by - ax = ay - bx
        // t < k
        ll res = n * k;
        for (int a = 0; a < across.size(); a++) {
            for (int b = 0; b < up.size(); b++) {
                if (up[b][1] - across[a][0] == across[a][1] - up[b][0]) {
                    int t = up[b][0] - across[a][0];
                    if (t > 0 && t < k) {
                        res--;
                    }
                }
            }
        }

        cout << res << endl;
    }

    return 0;
}