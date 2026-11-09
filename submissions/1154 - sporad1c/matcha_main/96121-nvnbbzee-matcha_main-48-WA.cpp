#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> l(n), r(n);
        for (int i = 0; i < n; ++i) cin >> l[i];
        for (int i = 0; i < n; ++i) cin >> r[i];
        long long a = 0;
        for (int b = 29; b >= 0; --b) {
            long long m = 1LL << b;
            long long sz = 1LL << (b + 1);
            int c1 = 0;
            vector<int> f;
            for (int i = 0; i < n; ++i) {
                long long bs = (l[i] >> (b + 1)) << (b + 1);
                long long md = bs + m;
                if (r[i] < md) {
                } else if (l[i] >= md) {
                    c1++;
                } else {
                    f.push_back(i);
                }
            }
            int sf = f.size();
            bool ok = false;
            if (sf > 0) {
                ok = true;
            } else {
                if (c1 % 2 == 1) ok = true;
            }
            int tb = 0;
            if (ok) {
                tb = 1;
                a |= m;
            }
            if (sf > 0) {
                for (int k = 0; k < sf; ++k) {
                    int idx = f[k];
                    long long bs = (l[idx] >> (b + 1)) << (b + 1);
                    long long md = bs + m;
                    long long top = bs + sz - 1;
                    if (k < sf - 1) {
                        l[idx] = md;
                        if (r[idx] > top) r[idx] = top;
                    } else {
                        int req = (tb - (c1 + sf - 1)) % 2;
                        if (req < 0) req += 2;
                        if (req == 1) {
                            l[idx] = md;
                            if (r[idx] > top) r[idx] = top;
                        } else {
                            r[idx] = md - 1;
                            if (l[idx] < bs) l[idx] = bs;
                        }
                    }
                }
            }
        }
        cout << a << "\n";
    }
    return 0;
}