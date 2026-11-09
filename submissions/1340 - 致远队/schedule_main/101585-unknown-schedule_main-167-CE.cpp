#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Course {
    int id;
    int subtree_size;
    
    // For max-heap based on subtree_size
    bool operator<(const Course& other) const {
        return subtree_size < other.subtree_size;
    }
};

void solve() {
    int N, M, K;
    if (!(cin >> N >> M >> K)) return;

    vector<int> P(N + 1);
    vector<vector<int>> children(N + 1); // Adjacency list for successors
    vector<int> in_degree(N + 1, 0);

    for (int i = 1; i <= N; ++i) {
        cin >> P[i];
        if (P[i] != 0) {
            children[P[i]].push_back(i);
            in_degree[i]++;
        }
    }

    // Calculate subtree sizes using DFS or Topological Order (reverse)
    // Since it's a forest/DAG with single parent, we can do DP.
    // But cycles are guaranteed not to exist.
    // We can compute sizes by processing nodes in reverse topological order or just memoized DFS.
    // Given N=10^4, recursion depth might be up to 1000, which is safe.
    
    vector<int> subtree_size(N + 1, 0);
    vector<bool> visited(N + 1, false);

    function<void(int)> dfs = [&](int u) {
        if (visited[u]) return;
        visited[u] = true;
        int size = 1; // Count self
        for (int v : children[u]) {
            dfs(v);
            size += subtree_size[v];
        }
        subtree_size[u] = size;
    };

    for (int i = 1; i <= N; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    // Simulation
    priority_queue<Course> pq;
    
    // Initialize with courses having no prerequisites
    for (int i = 1; i <= N; ++i) {
        if (in_degree[i] == 0) {
            pq.push({i, subtree_size[i]});
        }
    }

    int total_taken = 0;

    for (int sem = 0; sem < M; ++sem) {
        vector<Course> taken_this_sem;
        
        // Take up to K courses
        int count = 0;
        while (!pq.empty() && count < K) {
            Course c = pq.top();
            pq.pop();
            taken_this_sem.push_back(c);
            count++;
        }

        for (const auto& c : taken_this_sem) {
            total_taken++;
            int u = c.id;
            
            // Unlock successors
            for (int v : children[u]) {
                in_degree[v]--;
                if (in_degree[v] == 0) {
                    pq.push({v, subtree_size[v]});
                }
            }
        }
        
        // Note: Courses not taken remain in the priority queue? 
        // No, I popped them. I need to push back the ones NOT taken?
        // Wait, the loop `while (!pq.empty() && count < K)` pops them.
        // If I break because count == K, the remaining items are still in pq. That's correct.
        // If I break because pq.empty(), that's also correct.
        // So I only process the `taken_this_sem` ones. The others stay in `pq` for the next semester.
    }

    cout << total_taken << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
