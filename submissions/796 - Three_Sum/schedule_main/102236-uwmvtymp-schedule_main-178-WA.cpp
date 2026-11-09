#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void schedule_main_func() {
    int t_cases;
    if (!(cin >> t_cases)) return;
    
    while (t_cases--) {
        int N, M;
        long long K;
        cin >> N >> M >> K;
        
        vector<int> prereq(N + 1);
        vector<vector<int> > adj(N + 1);
        vector<int> in_degree(N + 1, 0);
        
        for (int i = 1; i <= N; i++) {
            cin >> prereq[i];
            if (prereq[i] != 0) {
                adj[prereq[i]].push_back(i);
                in_degree[i]++;
            }
        }
        
        vector<int> ready;
        for (int i = 1; i <= N; i++) {
            if (in_degree[i] == 0) {
                ready.push_back(i);
            }
        }
        
        long long total_taken = 0;
        
        for (int sem = 0; sem < M; sem++) {
            if (ready.empty()) break;
            
            long long take_count = min((long long)ready.size(), K);
            vector<int> taken_this_sem(ready.begin(), ready.begin() + take_count);
            ready.erase(ready.begin(), ready.begin() + take_count);
            
            total_taken += take_count;
            
            for (size_t i = 0; i < taken_this_sem.size(); i++) {
                int u = taken_this_sem[i];
                for (size_t j = 0; j < adj[u].size(); j++) {
                    int v = adj[u][j];
                    in_degree[v]--;
                    if (in_degree[v] == 0) {
                        ready.push_back(v);
                    }
                }
            }
        }
        
        cout << total_taken << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    schedule_main_func();
    
    return 0;
}