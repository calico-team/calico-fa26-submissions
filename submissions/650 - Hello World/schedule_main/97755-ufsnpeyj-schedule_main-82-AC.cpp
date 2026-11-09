#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int getLevel(int i, const vector<int>& pre, vector<int>& level) {
    if (i == 0) {
        return 0;
    }

    if (level[i] == 0) {
        level[i] = getLevel(pre[i], pre, level) + 1;
    }

    return level[i];
}

int main() {
    int t;
    cin >> t;

    for (int test = 0; test < t; test++) {
        int n, m, k;
        cin >> n >> m >> k;

        vector<int> pre(n + 1);
        vector<int> level(n + 1, 0);
        vector<int> cnt(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            cin >> pre[i];
        }

        for (int i = 1; i <= n; i++) {
            int d = getLevel(i, pre, level);
            cnt[d]++;
        }

        int ans = n;
        int before = 0;

        for (int d = 1; d <= min(m + 1, n); d++) {
            int slots = (m - d + 1) * k;
            ans = min(ans, before + slots);
            before += cnt[d];
        }

        cout << ans << '\n';
    }

    return 0;
}