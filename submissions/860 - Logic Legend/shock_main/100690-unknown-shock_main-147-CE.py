# Source: https://usaco.guide/general/io

using namespace std;

struct Earthquake {
    int r, c, p;
};

int findNext(vector<int>& parent, int x) {
    int root = x;

    while (parent[root] != root) {
        root = parent[root];
    }

    while (parent[x] != x) {
        int next = parent[x];
        parent[x] = root;
        x = next;
    }

    return root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<Earthquake> earthquakes(Q);

        for (int i = 0; i < Q; ++i) {
            cin >> earthquakes[i].r >> earthquakes[i].c >> earthquakes[i].p;
        }

        vector<vector<long long> > reading(N, vector<long long>(M, 0));
        vector<vector<int> > parent(N, vector<int>(M + 1));

        for (int r = 0; r < N; ++r) {
            for (int c = 0; c <= M; ++c) {
                parent[r][c] = c;
            }
        }

        for (int i = Q - 1; i >= 0; --i) {
            int R = earthquakes[i].r;
            int C = earthquakes[i].c;
            int P = earthquakes[i].p;
            long long p2 = 1LL * P * P;

            for (int r = R - P; r <= R + P; ++r) {
                long long dr = r - R;
                long long remaining = p2 - dr * dr;
                int d = (int)sqrt((double)remaining);

                int left = C - d;
                int right = C + d;

                int c = findNext(parent[r], left);

                while (c <= right) {
                    long long dc = c - C;
                    reading[r][c] = p2 - dr * dr - dc * dc + 1;

                    parent[r][c] = findNext(parent[r], c + 1);
                    c = parent[r][c];
                }
            }
        }

        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < M; ++c) {
                if (c > 0) cout << ' ';
                cout << reading[r][c];
            }
            cout << '\n';
        }
    }

    return 0;
}
