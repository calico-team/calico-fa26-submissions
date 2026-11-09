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
                up.push_back({x + y, x, y});
            } else {
                across.push_back({x + y, x, y});
            }
        }
        sort(up.begin(), up.end());
        sort(across.begin(), across.end());

        // total = drones * k - (collisions)
        // will collide if 
        // b = up drones, a = across drones
        // bx = ax + t
        // by + t = ay
        // ax + t = bx
        // by - ax = ay - bx
        // bx + by = ax + ay
        // t < k
        ll res = n * k;
        int a = 0, b = 0;
        while (a < across.size() && b < up.size()) {
            //cout << "a: " << a << " b: " << b << endl;
            if (up[b][0] < across[a][0]) {
                b++;
            } else if (up[b][0] > across[a][0]) {
                a++;
            } else {

                // will collide if x + y are same, same diagonal
                // int t = up[b][1] - across[a][1];
                // if (t > 0 && t < k) {
                //     res--;
                // }

                int s = across[a][0];
                int aEnd = a, bEnd = b;
                while (aEnd < across.size() && across[aEnd][0] == s) aEnd++;
                while (bEnd < up.size() && up[bEnd][0] == s) bEnd++;

                int l = b, r = b;
                for (int i = a; i < aEnd; i++) {
                    ll ax = across[i][1];
                    while (l < bEnd && up[l][1] < ax) l++;
                    while (r < bEnd && up[r][1] - ax < k) r++;
                    res -= r - l;
                }

                a = aEnd;
                b = bEnd;
            }
        }

        cout << res << endl;
    }

    return 0;
}