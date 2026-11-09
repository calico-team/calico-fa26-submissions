#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct pos {
    int x, y, z;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        vector<pos> vec;
        vector<char> dir;
        set<tuple<int, int, char>> dup;
        for (int i = 0; i < n; i++) {
            pos p; char d; cin >> p.x >> p.y >> p.z >> d;
            if (dup.count({p.x, p.y, d}) > 0) continue;
            vec.push_back(p); dir.push_back(d);
            dup.insert({p.x, p.y, d});
        }
        vector<tuple<int, int, int>> st; // x+y, x, is N
        for (int i = 0; i < vec.size(); i++) {
            st.push_back({vec[i].x + vec[i].y, vec[i].x, dir[i] == 'N'});
        }
        sort(st.begin(), st.end());

        ll dup2 = 0;

        int prevK = -1e9;
        queue<int> q;
        for (const auto &it : st) {
            if (get<0>(it) != prevK) {
                prevK = get<0>(it);
                while (q.size()) q.pop();
            }
            if (get<2>(it) == 0) {
                q.push(get<1>(it));
            } else {
                while (q.size()) {
                    int t = q.front();
                    if (get<1>(it) - t >= k) q.pop();
                    else break;
                }
                dup2 += q.size();
            }
        }

        ll ans = ll(k) * n - dup2;
        cout << ans << endl;
    }
    return 0;
}