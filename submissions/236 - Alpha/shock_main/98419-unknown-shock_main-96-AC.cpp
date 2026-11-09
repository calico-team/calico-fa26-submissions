#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n, m, q;
        cin >> n >> m >> q;
        vector<array<int, 3>> e(q);
        for (auto &x : e) cin >> x[0] >> x[1] >> x[2];
        vector<int> a(n * m, 0), p(n * (m + 1));
        iota(p.begin(), p.end(), 0);
        function<int(int)> f = [&](int x){return p[x] == x ? x : p[x] = f(p[x]);};
        for (int i = q - 1; i >= 0; i--){
            int r0 = e[i][0], c0 = e[i][1], pw = e[i][2];
            for (int r = r0 - pw; r <= r0 + pw; r++) {
                int dr = r - r0;
                int rem = pw * pw - dr * dr;
                int w = sqrt((double)rem);
                while (w * w > rem) w--;
                while ((w + 1) * (w + 1) <= rem) w++;
                int base = r * (m + 1);
                int x = f(base + c0 - w);
                while (x <= base + c0 + w){
                    int c = x - base;
                    int dc = c - c0;
                    a[r * m + c] = rem - dc * dc + 1;
                    p[x] = x + 1;
                    x = f(x + 1);}}}
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) cout << a[i * m + j] << " \n"[j == m - 1];}}