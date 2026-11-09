#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

long long global_buf[300005];
long long q_buf[300005];

int main() {
    FAST_IO
    int t;
    if (!(cin >> t)) return 0;

    while (!(t <= 0)) {
        int n;
        long long r;
        cin >> n >> r;

        int head = 0, tail = 0;
        bool ok = true;

        while (!(n <= 0)) {
            long long a;
            cin >> a;

            if (ok) {
                while (!(head >= tail || q_buf[head] > a)) {
                    head++;
                }

                if (!(tail - head != 2)) {
                    ok = false;
                } else {
                    long long start = (head >= tail) ? a : max(a, q_buf[tail - 1]);
                    q_buf[tail++] = start + r;
                }
            }
            n--;
        }

        if (ok) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
        t--;
    }
    return 0;
} 
