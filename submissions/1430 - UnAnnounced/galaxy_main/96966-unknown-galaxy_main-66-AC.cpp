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

int n, m;

int get(int i, int j) {
    return i * m + j;
}

vector<int> p;

int getp(int x) {
    if (p[x] == x) return x;
    p[x] = getp(p[x]);
    return p[x];
}

void add(int x, int y) {
    if (rand() & 1 == 0) swap(x, y);
    p[getp(x)] = getp(y);
}

void solve() {
    int q;
    cin >> n >> m >> q;
    p.resize(n * m);
    for (int i = 0; i < p.size(); i++) p[i] = i;
    vector<string> s(n);
    for (string& ss : s) cin >> ss;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char a = s[i][j];
            if (i + 1 < n) {
                char b = s[i + 1][j];
                if ((a == b) or (a == '.') or (b == '.')) add(get(i, j), get(i + 1, j));
            }
            if (j + 1 < m) {
                char b = s[i][j + 1];
                if ((a == b) or (a == '.') or (b == '.')) add(get(i, j), get(i, j + 1));
            }
        }
    }
    while (q--) {
        int r, c;
        cin >> r >> c;
        int A = get(r, c);
        cin >> r >> c;
        int B = get(r, c);
        cout << (getp(A) == getp(B) ? "YES\n" : "NO\n");
    }
}

int main() {
    srand(0);
	int t;
    cin >> t;
    while (t--) solve();
}
