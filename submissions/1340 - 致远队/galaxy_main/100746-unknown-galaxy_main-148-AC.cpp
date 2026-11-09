#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> rank;
    
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (rank[x] < rank[y]) {
            parent[x] = y;
        } else {
            parent[y] = x;
            if (rank[x] == rank[y]) {
                rank[x]++;
            }
        }
    }
};

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

void solve() {
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<string> grid(N);
    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
    }
    
    // 总状态数：2 * N * M
    // 编码方式：z * N * M + r * M + c
    int total_states = 2 * N * M;
    DSU dsu(total_states);
    
    // Step 1: 同层内的相邻连通（四方向）
    for (int z = 0; z < 2; ++z) { // z=0 Blue, z=1 Red
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < M; ++c) {
                char ch = grid[r][c];
                bool can_enter = false;
                if (z == 0) { // Blue mode
                    if (ch == '.' || ch == 'B') can_enter = true;
                } else { // Red mode
                    if (ch == '.' || ch == 'R') can_enter = true;
                }
                
                if (!can_enter) continue;
                
                // 检查四个方向
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
                    
                    char nch = grid[nr][nc];
                    bool n_can_enter = false;
                    if (z == 0) {
                        if (nch == '.' || nch == 'B') n_can_enter = true;
                    } else {
                        if (nch == '.' || nch == 'R') n_can_enter = true;
                    }
                    
                    if (n_can_enter) {
                        int id1 = z * N * M + r * M + c;
                        int id2 = z * N * M + nr * M + nc;
                        dsu.unite(id1, id2);
                    }
                }
            }
        }
    }
    
    // Step 2: 在普通瓷砖 '.' 上，允许跨层切换（Spin 操作）
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < M; ++c) {
            if (grid[r][c] == '.') {
                int id0 = 0 * N * M + r * M + c;
                int id1 = 1 * N * M + r * M + c;
                dsu.unite(id0, id1);
            }
        }
    }
    
    // Step 3: 处理查询
    while (Q--) {
        int Rs, Cs, Re, Ce;
        cin >> Rs >> Cs >> Re >> Ce;
        
        // 起点状态：蓝色模式（z=0）
        int start_id = 0 * N * M + Rs * M + Cs;
        
        // 终点的两个状态
        int end_id0 = 0 * N * M + Re * M + Ce;
        int end_id1 = 1 * N * M + Re * M + Ce;
        
        // 只要起点和终点的任意一个状态连通，就算可达
        if (dsu.find(start_id) == dsu.find(end_id0) || 
            dsu.find(start_id) == dsu.find(end_id1)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
