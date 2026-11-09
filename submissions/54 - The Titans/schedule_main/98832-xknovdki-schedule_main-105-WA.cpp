#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void run_test() { int n, m, k; if (!(cin >> n >> m >> k)) return;
    
    vector<int> p(n + 1); vector<vector<int>> children(n + 1); vector<int> deg(n + 1, 0);
    
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        if (p[i] != 0) {
            children[p[i]].push_back(i);
            deg[i]++;
        }
    }
    
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }
    
    int total_taken = 0; priority_queue<int, vector<int>, greater<int>> ready;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) {
            ready.push(i);
        }
    }
    
    vector<int> current_ready;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) {
            current_ready.push_back(i);
        }
    }
    
    int courses_count = 0;
    for (int sem = 0; sem < m; sem++) {
        if (current_ready.empty()) break;
        
        vector<int> next_ready;
        int taken_this_semester = 0; vector<int> leftover;
        
        for (int i = 0; i < current_ready.size(); i++) {
            int u = current_ready[i];
            if (taken_this_semester < k) {
                taken_this_semester++;
                courses_count++;
                for (int v : children[u]) {
                    deg[v]--;
                    if (deg[v] == 0) {
                        next_ready.push_back(v);
                    }
                }
            } else {
                leftover.push_back(u);
            }
        }
        
        current_ready = leftover;
        for (int v : next_ready) {
            current_ready.push_back(v);
        }
    }
    cout << courses_count << "\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); int t;
    if (cin >> t) {
        while (t--) {
            run_test();
        }
    }
    return 0;
}