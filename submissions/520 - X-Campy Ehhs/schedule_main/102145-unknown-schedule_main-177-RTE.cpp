#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long M, K;
    cin >> N >> M >> K;

    vector<vector<int>> children(N + 1);
    vector<int> depth(N + 1, 0);
    vector<int> count(N + 1, 0);
    queue<int> q;

    for (int i = 1; i <= N; i++) {
        int prerequisite;
        cin >> prerequisite;

        if (prerequisite == 0) {
            depth[i] = 1;
            q.push(i);
        } else {
            children[prerequisite].push_back(i);
        }
    }

    while (!q.empty()) {
        int course = q.front();
        q.pop();

        count[depth[course]]++;

        for (int next : children[course]) {
            depth[next] = depth[course] + 1;
            q.push(next);
        }
    }

    long long total = 0;
    long long ans = 0;

    int semesters = static_cast<int>(min(M, 1LL * N));

    for (int s = 1; s <= semesters; s++) {
        total += count[s];
        ans = min(ans + K, total);
    }

    cout << ans << endl;
}


