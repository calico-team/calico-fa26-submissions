#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int T, n, k, z;
pair<int, int> a[N];
vector<int> G[2 * N];
long long ans;

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    while (T--){
        cin >> n >> k; ans = n * k; z = 0;
        for (int i = 0; i < 2 * N; i++)
            G[i].clear();
        for (int i = 1; i <= n; i++){
            int x, y, tr; char p; cin >> x >> y >> tr >> p;
            if (p == 'E') G[x + y].push_back(x);
            else { a[++z] = {x, y}; }
        }
        for (int i = 0; i < 2 * N; i++)
            if (!G[i].empty())
                sort(G[i].begin(), G[i].end());
        for (int i = 1; i <= z; i++){
            int x = a[i].first, y = a[i].second;
            if (G[x + y].empty()) continue;
            ans -= upper_bound(G[x + y].begin(), G[x + y].end(), x) - lower_bound(G[x + y].begin(), G[x + y].end(), x - k + 1);
        }
        cout << ans << "\n";
    }
    return 0;
}