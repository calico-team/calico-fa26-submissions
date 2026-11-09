// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

template<typename T>
ostream& operator << (ostream& out, vector<T>& a) {
    out << "[";
    for (int i = 0; i < a.size(); i++) {
        if (i) out << ", ";
        out << a[i];
    }
    out << "]";
    return out;

}

int DFS(int v, vector<int>& p, vector<int>& d) {
    if (p[v] == -1) {
        d[v] = 0;
        return 0;
    }
    if (d[v] > 0) {
        return d[v];
    }
    d[v] = DFS(p[v], p, d) + 1;
    return d[v];
}


void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> p(n);
    for (int& x : p) {cin >> x; x--;};
    vector<int> d(n, 0);
    for (int i = 0; i < n; i++) DFS(i, p, d);
    //cout << "D= " << d << endl;
    vector<int> num_taken(m);
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) a[i] = {d[i], i};
    sort(a.begin(), a.end());
    set<int> taken;
    for (int i = m - 1; i >= 0; i--) {
        while ((num_taken[i] < k) and (a.size() > 0)) {
            int course = a[a.size() - 1].second;
            a.pop_back();
            if (taken.count(course) > 0 or d[course] > i) continue;
            int j = i;
            while (true) {
                taken.insert(course);
                num_taken[j] ++;
                j--;
                course = p[course];
                if ((course == -1) or (taken.count(course) > 0)) break;
            }
        }
    }
    cout << taken.size() << "\n";

}

int main() {
    srand(0);
	int t;
    cin >> t;
    while (t--) solve();
}
