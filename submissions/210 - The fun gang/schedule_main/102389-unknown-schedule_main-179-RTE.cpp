#include <iostream>
#include <vector>
#include <deque>
using namespace std;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    for (int _ = 0; _ < t; _++) {
        int courses, semesters, max_classes;
        cin >> courses;
        vector<vector<int>> graph(courses + 1);
        for (int i = 0; i < courses; i++) {
            int prq;
            cin >> prq;
            prq--;
            if (prq != -1) {
                graph[prq].push_back(i + 1);
            }
        }
        int ans = 0;
        int times = 0;
        vector<int> indegree(courses + 1);
        deque<int> queue;
        for (int i = 0; i < courses; i++) {
            for (auto neighbor : graph[i]) {
                indegree[neighbor]++;
            }
        }
        for (int i = 0; i < courses; i++) {
            if (indegree[i] == 0) {
                queue.push_back(i);
            }
        }
        times++;
        while (!queue.empty()) {
            vector<int> backedupqueue;
            int currans = 0;
            while (!queue.empty()) {
                int u = queue.front();
                queue.pop_front();
                ans++;
                currans++;
                for (int v : graph[u]) {
                    indegree[v]--;
                    if (indegree[v] == 0) {
                        backedupqueue.push_back(v);
                    }
                }
                if (currans == max_classes) {
                    break;
                }
            }
            for (auto element : backedupqueue) {
                queue.push_back(element);
                times++;
            }
            if (times > semesters) break;
        }
        cout << ans << endl;
    }
    return 0;
}