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
int n, m, k;

int calcDepth(int i, vector<int>& prereqs, vector<int>& depth) {
    if (depth[i] != -1) return depth[i];
    if (prereqs[i] == 0) return depth[i] = 0;
    return depth[i] = calcDepth(prereqs[i], prereqs, depth) + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> t;
    while (t--) {
        cin >> n >> m >> k;
        vector<int> prereqs(n + 1, 0);
        vector<int> depth(n + 1, -1);
        for (int i = 0; i < n; i++) {
            cin >> prereqs[i + 1];
        }

        vector<int> unlock(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            unlock[calcDepth(i, prereqs, depth)]++;
        }
        int res = 0;

        // always take as much as you can
        // assume each course at cur depth is definitely unlocked -> even if there are k courses in tier two that are all single 
        // children, you can always take the k prereqs last time which would be optimal
        int unlocked = 0;
        for (int sem = 0; sem < m; sem++) {
            unlocked += unlock[sem];

            res += min(unlocked, k);
            unlocked -= min(unlocked, k);
        }

        cout << res << endl;
    }

    return 0;
}