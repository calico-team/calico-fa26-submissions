#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string phase;
    int n;
    if (!(cin >> phase >> n)) return 0;

    if (phase == "FIRST") {
        vector<int> deg(n + 1, 0);
        // xor of the neighbors; a leaf has only one left
        vector<int> adj_xor(n + 1, 0);

        for (int i = 0; i < n - 1; i++) {
            int a, b;
            cin >> a >> b;

            deg[a]++;
            deg[b]++;
            adj_xor[a] ^= b;
            adj_xor[b] ^= a;
        }

        priority_queue<int, vector<int>, greater<int>> leaf_heap;

        for (int i = 1; i <= n; i++) {
            if (deg[i] == 1) leaf_heap.push(i);
        }

        vector<int> prufer;
        prufer.reserve(n);
        long long sum_labels = 0;

        // remove the smallest leaf to build the pruefer sequence
        for (int i = 0; i < n - 2; i++) {
            int leaf = leaf_heap.top();
            leaf_heap.pop();

            int next = adj_xor[leaf];
            prufer.push_back(next);
            sum_labels += next;

            deg[leaf]--;
            deg[next]--;
            adj_xor[next] ^= leaf;

            if (deg[next] == 1) leaf_heap.push(next);
        }

        // the checksum restores a missing value modulo n + 1
        // if the checksum or padding is missing, the sequence is intact
        prufer.push_back(sum_labels % (n + 1));
        prufer.push_back(0);

        for (int i = 0; i < n; i++) {
            if (i) cout << ' ';
            cout << prufer[i];
        }
        cout << '\n';
    } else if (phase == "SECOND") {
        vector<int> received(n);
        for (int &x : received) cin >> x;

        vector<int> prufer(n - 2);
        long long sum_labels = 0;
        int missing_pos = -1;

        for (int i = 0; i < n - 2; i++) {
            prufer[i] = received[i];

            if (prufer[i] == -1) {
                missing_pos = i;
            } else {
                sum_labels += prufer[i];
            }
        }

        if (missing_pos != -1) {
            int checksum = received[n - 2];
            int known_mod = sum_labels % (n + 1);
            prufer[missing_pos] = (checksum - known_mod + (n + 1)) % (n + 1);
        }

        // degree is one plus the number of times a vertex appears
        vector<int> remaining_degree(n + 1, 1);
        for (int x : prufer) remaining_degree[x]++;

        priority_queue<int, vector<int>, greater<int>> leaf_heap;

        for (int i = 1; i <= n; i++) {
            if (remaining_degree[i] == 1) leaf_heap.push(i);
        }

        for (int x : prufer) {
            int leaf = leaf_heap.top();
            leaf_heap.pop();

            cout << leaf << ' ' << x << '\n';

            remaining_degree[leaf]--;
            remaining_degree[x]--;

            if (remaining_degree[x] == 1) leaf_heap.push(x);
        }

        int a = leaf_heap.top();
        leaf_heap.pop();
        int b = leaf_heap.top();
        cout << a << ' ' << b << '\n';
    }

    return 0;
}
