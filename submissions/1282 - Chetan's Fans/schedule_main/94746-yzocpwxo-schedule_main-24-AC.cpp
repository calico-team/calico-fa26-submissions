#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while (tests--) {
        int n, semesters, limit;
        cin >> n >> semesters >> limit;
        vector<vector<int>> children(n + 1);
        for (int course = 1; course <= n; ++course) {
            int prerequisite;
            cin >> prerequisite;
            children[prerequisite].push_back(course);
        }

        vector<int> order = children[0], height(n + 1, 1);
        order.reserve(n);
        for (int i = 0; i < n; ++i)
            for (int child : children[order[i]]) order.push_back(child);
        for (int i = n - 1; i >= 0; --i)
            for (int child : children[order[i]])
                height[order[i]] = max(height[order[i]], height[child] + 1);

        priority_queue<pair<int, int>> available;
        for (int root : children[0]) available.emplace(height[root], root);
        vector<int> batch;
        batch.reserve(limit);
        int taken = 0;
        while (semesters-- && !available.empty()) {
            batch.clear();
            int count = min(limit, static_cast<int>(available.size()));
            taken += count;
            while (count--) {
                batch.push_back(available.top().second);
                available.pop();
            }
            for (int course : batch)
                for (int child : children[course]) available.emplace(height[child], child);
        }
        cout << taken << '\n';
    }
}
