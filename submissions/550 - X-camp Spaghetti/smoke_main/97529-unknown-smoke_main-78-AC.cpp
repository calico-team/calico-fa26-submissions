#include <bits/stdc++.h>
using namespace std;
int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, R;
        cin >> N >> R;
        long long a[100005];
        long long finish[100005];
        for (int i = 0; i < N; i++) {
            cin >> a[i];
        }
        int available = 2;
        int head = 0, tail = 0;
        bool ok = true;
        for (int i = 0; i < N; i++) {
            while (head < tail && finish[head] <= a[i]) {
                available++;
                head++;
            }
            if (available == 0) {
                ok = false;
                break;
            }
            available--;
            if (head == tail) {
                finish[tail] = a[i] + R;
            } else {
                finish[tail] = finish[tail - 1] + R;
            }
            tail++;
        }
        if (ok) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
