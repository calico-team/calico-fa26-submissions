#include <bits/stdc++.h>
using namespace std;

struct Range {
    int l, r;
};

int bestValue(int lo, int hi, int current) {
    int x = 0;

    for (int b = 29; b >= 0; b--) {
        int want = 1 - ((current >> b) & 1);
        int candidate = x | (want << b);

        if (candidate <= hi &&
            candidate + (1 << b) - 1 >= lo) {
            x = candidate;
        } else {
            x |= (1 - want) << b;
        }
    }

    return x;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<Range> a(N);

        for (int i = 0; i < N; i++)
            cin >> a[i].l;

        for (int i = 0; i < N; i++)
            cin >> a[i].r;

        stable_sort(a.begin(), a.end(),
            [](const Range &x, const Range &y) {
                return x.r - x.l > y.r - y.l;
            });

        int ans = 0;

        for (int i = 0; i < N; i++) {
            int x = bestValue(a[i].l, a[i].r, ans);
            ans ^= x;
        }

        cout << ans << '\n';
    }

    return 0;
}