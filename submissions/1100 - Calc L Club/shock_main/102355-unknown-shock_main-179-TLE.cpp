#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
void solve(){
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<ll>> grid(n, vector<ll>(m, 0));
    for (int i = 0; i < q; i++){
        ll r, c, p;
        cin >> r >> c >> p;
        ll sp = p * p;
        ll rMin = max(0LL, r - p);
        ll rMax = min((ll)n - 1, r + p);
        ll cMin = max(0LL, c - p); 
        ll cMax =  min((ll)m - 1, c + p);

        for(ll re = rMin; re <= rMax; re++){
            ll dr = re - r;
            ll remaining_sq = sp - (dr * dr);
            ll max_dc = sqrt(remaining_sq+1e-9);
            for (ll ce = c - max_dc; ce <= c + max_dc; ce++) {
                ll dc = ce - c;
                grid[re][ce] = sp - (dr * dr + dc * dc) + 1;
            }
        }
    }
    for(int r = 0; r < n; r++){
        for(int c = 0; c < m; c++){
            cout << grid[r][c] << (c == m - 1 ? "" : " ");
        }
        cout << "\n";
    }
}
int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t){
        while(t--){
            solve();
        }
    }
    return 0;
}