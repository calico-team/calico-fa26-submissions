#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string phase;
    int n;
    cin >> phase >> n;
    vector<int> parent(n + 1);
    if (phase == "FIRST") {
        vector<int> head(n + 1, -1), to(2 * (n - 1)), next(to.size());
        auto add = [&](int edge, int from, int dest) {
            to[edge] = dest;
            next[edge] = head[from];
            head[from] = edge;
        };
        for (int i = 0; i < n - 1; ++i) {
            int a, b;
            cin >> a >> b;
            add(2 * i, a, b);
            add(2 * i + 1, b, a);
        }

        vector<int> order{1};
        int checksum = 0;
        order.reserve(n);
        for (int i = 0; i < n; ++i) {
            int vertex = order[i];
            for (int edge = head[vertex]; edge != -1; edge = next[edge]) {
                int child = to[edge];
                if (child == parent[vertex]) continue;
                parent[child] = vertex;
                checksum ^= vertex;
                order.push_back(child);
            }
        }
        parent[1] = checksum;
        for (int i = 1; i <= n; ++i)
            cout << parent[i] << (i == n ? '\n' : ' ');
    } else {
        int missing = 0, checksum = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> parent[i];
            if (parent[i] == -1)
                missing = i;
            else
                checksum ^= parent[i];
        }
        parent[missing] = checksum;
        for (int i = 2; i <= n; ++i) cout << i << ' ' << parent[i] << '\n';
    }
}
