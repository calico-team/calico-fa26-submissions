#include <bits/stdc++.h>
using namespace std;

/*
 * CALICO Fall '26 - Problem 9: Super Ben Galaxy 2
 *
 * Exact shortest-path queries on a narrow grid.
 *
 * Each usable (row, column, mode) is a vertex:
 *   mode 0 = blue, mode 1 = red.
 * Adjacent usable cells in the same mode have an edge of cost 1.
 * At a normal cell '.', switching modes is an edge of cost 1.
 *
 * The resulting graph is an undirected graph of width at most 2*N.
 * A recursive separator decomposition by columns gives an exact
 * distance oracle. For every separator vertex, BFS computes distances
 * to all vertices in that decomposition interval.
 */

struct Query {
    int sr, sc, er, ec;
    long long k;
};

struct SeparatorNode {
    int left, right, mid;
    vector<int> separator; // global state IDs
    // Flattened [separator index][local state index].
    // local state index = (mode*N + row)*(right-left+1) + (col-left)
    vector<int> dist;
    int width = 0;

    int localIndex(int state, int N, int M) const {
        int mode = state / (N * M);
        int rem = state % (N * M);
        int row = rem / M;
        int col = rem % M;
        return (mode * N + row) * width + (col - left);
    }

    int getDistance(int sepIndex, int state, int N, int M) const {
        int idx = localIndex(state, N, M);
        return dist[sepIndex * (2 * N * width) + idx];
    }
};

class Solver {
    int N, M;
    vector<string> grid;
    vector<char> active;
    vector<SeparatorNode> nodes;
    vector<int> leftChild, rightChild;

    int stateId(int mode, int r, int c) const {
        return mode * N * M + r * M + c;
    }

    bool isActive(int mode, int r, int c) const {
        char ch = grid[r][c];
        return ch == '.' || (mode == 0 && ch == 'B') ||
               (mode == 1 && ch == 'R');
    }

    void bfsFromSeparator(SeparatorNode &node, int source, int sepIndex) {
        const int width = node.right - node.left + 1;
        const int localStates = 2 * N * width;
        const int totalStates = 2 * N * M;
        const int INF = 1e9;

        int offset = sepIndex * localStates;
        fill(node.dist.begin() + offset,
             node.dist.begin() + offset + localStates, INF);

        vector<int> q;
        q.reserve(localStates);

        auto localIndex = [&](int mode, int r, int c) {
            return (mode * N + r) * width + (c - node.left);
        };

        int sm = source / (N * M);
        int sr = (source % (N * M)) / M;
        int sc = source % M;

        int sourceLocal = localIndex(sm, sr, sc);
        node.dist[offset + sourceLocal] = 0;
        q.push_back(source);

        size_t head = 0;
        while (head < q.size()) {
            int u = q[head++];
            int mode = u / (N * M);
            int rem = u % (N * M);
            int r = rem / M;
            int c = rem % M;
            int du = node.dist[offset + localIndex(mode, r, c)];

            auto relax = [&](int nm, int nr, int nc) {
                if (nr < 0 || nr >= N || nc < node.left ||
                    nc > node.right || !isActive(nm, nr, nc)) {
                    return;
                }
                int v = stateId(nm, nr, nc);
                int vi = localIndex(nm, nr, nc);
                if (node.dist[offset + vi] == INF) {
                    node.dist[offset + vi] = du + 1;
                    q.push_back(v);
                }
            };

            relax(mode, r - 1, c);
            relax(mode, r + 1, c);
            relax(mode, r, c - 1);
            relax(mode, r, c + 1);

            if (grid[r][c] == '.') {
                relax(1 - mode, r, c);
            }
        }
    }

    int build(int left, int right) {
        int nodeId = (int)nodes.size();
        nodes.emplace_back();
        leftChild.push_back(-1);
        rightChild.push_back(-1);

        int mid = (left + right) / 2;
        nodes[nodeId].left = left;
        nodes[nodeId].right = right;
        nodes[nodeId].mid = mid;
        nodes[nodeId].width = right - left + 1;

        // All active states in the middle column form the separator.
        for (int mode = 0; mode < 2; ++mode) {
            for (int r = 0; r < N; ++r) {
                if (isActive(mode, r, mid)) {
                    nodes[nodeId].separator.push_back(stateId(mode, r, mid));
                }
            }
        }

        int width = right - left + 1;
        int localStates = 2 * N * width;
        int sepCount = (int)nodes[nodeId].separator.size();
        nodes[nodeId].dist.resize((size_t)sepCount * localStates);

        for (int i = 0; i < sepCount; ++i) {
            // build() may reallocate nodes, so access the node by index.
            int source = nodes[nodeId].separator[i];
            bfsFromSeparator(nodes[nodeId], source, i);
        }

        // Store children after this node; the query traversal uses intervals,
        // so explicit child pointers are unnecessary.
        if (left < mid) {
            int child = build(left, mid - 1);
            leftChild[nodeId] = child;
        }
        if (mid < right) {
            int child = build(mid + 1, right);
            rightChild[nodeId] = child;
        }

        return nodeId;
    }

public:
    Solver(int n, int m, vector<string> g)
        : N(n), M(m), grid(std::move(g)) {}

    void preprocess() {
        nodes.reserve(2 * M);
        leftChild.reserve(2 * M);
        rightChild.reserve(2 * M);
        build(0, M - 1);
    }

    bool canReachWithin(int sr, int sc, int er, int ec, long long k) const {
        const int INF = 1e9;
        int start = stateId(0, sr, sc); // starts in blue mode
        int best = INF;

        // Destination can be reached in either mode, provided its tile
        // is active in that mode.
        int dest[2] = {-1, -1};
        for (int mode = 0; mode < 2; ++mode) {
            if (isActive(mode, er, ec)) {
                dest[mode] = stateId(mode, er, ec);
            }
        }

        int nodeId = 0;
        while (nodeId != -1) {
            const SeparatorNode &node = nodes[nodeId];

            // Consider every possible crossing point in this separator.
            for (int i = 0; i < (int)node.separator.size(); ++i) {
                int ds = node.getDistance(i, start, N, M);
                if (ds >= INF) continue;

                for (int mode = 0; mode < 2; ++mode) {
                    if (dest[mode] == -1) continue;
                    int de = node.getDistance(i, dest[mode], N, M);
                    if (de < INF) best = min(best, ds + de);
                }
            }

            if (sc == node.mid || ec == node.mid) break;

            bool bothLeft = (sc < node.mid && ec < node.mid);
            bool bothRight = (sc > node.mid && ec > node.mid);
            if (bothLeft) nodeId = leftChild[nodeId];
            else if (bothRight) nodeId = rightChild[nodeId];
            else break;
        }

        return best <= k;
    }

    // Filled after preprocessing; right-child index in preorder.
    vector<int> rightChildIndex;
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> grid(N);
        for (int r = 0; r < N; ++r) cin >> grid[r];

        Solver solver(N, M, std::move(grid));
        solver.preprocess();

        for (int i = 0; i < Q; ++i) {
            int rs, cs, re, ce;
            long long k;
            cin >> rs >> cs >> re >> ce >> k;
            cout << (solver.canReachWithin(rs, cs, re, ce, k) ? "YES" : "NO")
                 << '\n';
        }
    }
    return 0;
}
