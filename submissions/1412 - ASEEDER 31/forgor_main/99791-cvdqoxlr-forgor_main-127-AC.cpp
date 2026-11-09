#include<bits/stdc++.h>
using namespace std;
const long long MOD = 1000001;
string phase;
vector<int> ns;
vector<vector<pair<int, int>>> edges;
vector<vector<int>> values;
vector<long long> encodeTree(int n, const vector<pair<int, int>> &es) {
    vector<int> degree(n + 1, 0);
    vector<vector<int>> adj(n + 1);

    for (const auto &e : es) {
        int u = e.first, v = e.second;
        adj[u].push_back(v);
        adj[v].push_back(u);
        ++degree[u];
        ++degree[v];
    }

    // Prüfer 编码：反复取编号最小的叶子，记下它唯一的邻居
    priority_queue<int, vector<int>, greater<int>> leaves;
    for (int i = 1; i <= n; ++i) {
        if (degree[i] == 1) leaves.push(i);
    }

    vector<int> code;
    code.reserve(n);

    for (int k = 0; k + 2 < n; ++k) {
        int leaf = leaves.top();
        leaves.pop();

        int nb = 0;
        for (int w : adj[leaf]) {
            if (degree[w] > 0) {          // 已删除的邻居 degree 为 0
                nb = w;
                break;
            }
        }
        code.push_back(nb);
        degree[leaf] = 0;
        if (--degree[nb] == 1) leaves.push(nb);
    }

    long long sum = 0;
    for (int x : code) sum += x;

    vector<long long> a(n, 0);
    for (int i = 0; i < (int)code.size(); ++i) a[i] = code[i];
    a[n - 2] = sum % MOD;                 // 校验位（n = 2 时就是 A[0]）
    a[n - 1] = 0;                         // 占位
    return a;
}vector<pair<int, int>> decodeTree(int n, const vector<int> &a) {
    int m = n - 2;                        // Prüfer 序列长度
    int lost = -1;
    for (int i = 0; i < n; ++i) {
        if (a[i] == -1) { lost = i; break; }
    }
    vector<int> code(m, 0);
    if (lost >= 0 && lost < m) {
        long long others = 0;
        for (int i = 0; i < m; ++i) {
            if (i != lost) others += a[i];
        }
        long long restored = ((a[m] - others) % MOD + MOD) % MOD;
        for (int i = 0; i < m; ++i) {
            code[i] = (int)(i == lost ? restored : a[i]);
        }
    } else {
        for (int i = 0; i < m; ++i) code[i] = (int)a[i];
    }
    vector<int> degree(n + 1, 1);
    for (int x : code) ++degree[x];
    priority_queue<int, vector<int>, greater<int>> leaves;
    for (int i = 1; i <= n; ++i) {
        if (degree[i] == 1) leaves.push(i);
    }
    vector<pair<int, int>> res;
    res.reserve(n - 1);
    for (int x : code) {
        int leaf = leaves.top();
        leaves.pop();
        res.push_back({leaf, x});
        if (--degree[x] == 1) leaves.push(x);
    }
    int u = leaves.top();
    leaves.pop();
    int v = leaves.top();
    res.push_back({u, v});
    return res;
}
void amnesiac() {
    if (phase == "FIRST") {
        for (size_t i = 0; i < ns.size(); ++i) {
            vector<long long> a = encodeTree(ns[i], edges[i]);
            for (int j = 0; j < ns[i]; ++j) {
                if (j) cout << ' ';
                cout << a[j];
            }
            cout << '\n';
        }
    } else {
        for (size_t i = 0; i < ns.size(); ++i) {
            vector<pair<int, int>> es = decodeTree(ns[i], values[i]);
            for (const auto &e : es) {
                cout << e.first << ' ' << e.second << '\n';
            }
        }
    }
}
void read_your_input() {
    cin >> phase;
    int n;
    if (phase == "FIRST") {
        while (cin >> n) {
            vector<pair<int, int>> es(n - 1);
            for (auto &e : es) cin >> e.first >> e.second;
            ns.push_back(n);
            edges.push_back(move(es));
        }
    } else {
        while (cin >> n) {
            vector<int> a(n);
            for (auto &x : a) cin >> x;
            ns.push_back(n);
            values.push_back(move(a));
        }
    }
}
int main() {
    read_your_input();
    amnesiac();
    return 0;
}
