#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

long long maxCls(int nc, long long terms, long long cap, const vector<int>& pre) {
    vector<vector<int>> nxt(nc + 1);
    for (int c = 1; c <= nc; c++) {
        nxt[pre[c]].push_back(c);
    }

    // lvl[i] = number of classes on level i + 1 (classes with no prerequisite are level 1)
    vector<long long> lvl;
    queue<pair<int, int>> q;
    for (int c : nxt[0]) q.push({c, 1});
    while (!q.empty()) {
        auto [c, d] = q.front();
        q.pop();
        if (d > (int)lvl.size()) lvl.push_back(0);
        lvl[d - 1]++;
        for (int ch : nxt[c]) q.push({ch, d + 1});
    }

    long long took = 0;
    long long room = cap * terms;

    for (int i = 0; i < (int)lvl.size(); i++) {
        if (room <= 0) break;
        long long d = i + 1;
        long long cnt = lvl[i];
        if (cnt > room) {
            took += room;
            break;
        }
        took += cnt;
        long long left = terms - d;
        room = min(room - cnt, cap * left);
    }
    return took;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int nc;
        long long terms, cap;
        cin >> nc >> terms >> cap;
        vector<int> pre(nc + 1);
        for (int i = 1; i <= nc; i++) cin >> pre[i];
        cout << maxCls(nc, terms, cap, pre) << "\n";
    }
    return 0;
}
