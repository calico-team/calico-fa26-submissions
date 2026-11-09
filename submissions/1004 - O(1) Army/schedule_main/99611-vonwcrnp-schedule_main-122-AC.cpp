#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    cin >> tests;
    while (tests--) {
        int n, semesters, capacity;
        cin >> n >> semesters >> capacity;
        vector<vector<int>> children(n + 1);
        for (int course = 1; course <= n; ++course) {
            int parent;
            cin >> parent;
            children[parent].push_back(course);
        }
        vector<pair<int, int>> order{{0, 0}};
        vector<int> count(n + 1);
        for (size_t i = 0; i < order.size(); ++i) {
            auto [course, depth] = order[i];
            for (int child : children[course]) {
                order.emplace_back(child, depth + 1);
                ++count[depth + 1];
            }
        }
        long long answer = n;
        int shallower = 0;
        for (int depth = 1; depth <= n && count[depth]; ++depth) {
            answer = min(answer, shallower + 1LL * capacity * max(0, semesters - depth + 1));
            shallower += count[depth];
        }
        cout << answer << '\n';
    }
}

