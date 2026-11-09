
#include <bits/stdc++.h>
using namespace std;

struct Drone {
    int s, x, type;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        long long k;
        cin >> n >> k;

        vector<Drone> a(n);

        for (int i = 0; i < n; i++) {
            int x, y, z;
            char d;
            cin >> x >> y >> z >> d;

            a[i] = {x + y, x, d == 'E' ? 0 : 1};
        }

        sort(a.begin(), a.end(), [](const Drone& p, const Drone& q) {
            if (p.s != q.s) return p.s < q.s;
            if (p.type != q.type) return p.type < q.type;
            return p.x < q.x;
        });

        long long meetings = 0;

        for (int i = 0; i < n;) {
            int j = i;

            while (j < n && a[j].s == a[i].s) {
                j++;
            }

            int mid = i;

            while (mid < j && a[mid].type == 0) {
                mid++;
            }

            int l = mid, r = mid;

            for (int p = i; p < mid; p++) {
                while (l < j && a[l].x < a[p].x) {
                    l++;
                }

                if (r < l) {
                    r = l;
                }

                long long limit = (long long)a[p].x + k - 1;

                while (r < j && a[r].x <= limit) {
                    r++;
                }

                meetings += r - l;
            }

            i = j;
        }

        cout << 1LL * n * k - meetings << '\n';
    }

    return 0;
}
