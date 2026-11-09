
#include <bits/stdc++.h>
using namespace std;
struct Drone {
    long long x, y, z;
    char d;
    long long s;
};
bool cmp(Drone a, Drone b) {
    if (a.s != b.s) return a.s < b.s;
    return a.x < b.x;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N;
        long long K;
        cin >> N >> K;
        vector<Drone> a(N);
        for (int i = 0; i < N; i++) {
            cin >> a[i].x >> a[i].y >> a[i].z >> a[i].d;
            a[i].s = a[i].x + a[i].y;
        }
        sort(a.begin(), a.end(), cmp);
        long long blocked = 0;
        int start = 0;
        while (start < N) {
            int end = start;
            while (end < N && a[end].s == a[start].s) {
                end++;
            }
            int left = start;
            long long cntE = 0;
            for (int i = start; i < end; i++) {
                while (left < i && a[i].x - a[left].x >= K) {
                    if (a[left].d == 'E') {
                        cntE--;
                    }
                    left++;
                }
                if (a[i].d == 'N') {
                    blocked += cntE;
                }
                if (a[i].d == 'E') {
                    cntE++;
                }
            }
            start = end;
        }
        cout << 1LL * N * K - blocked << '\n';
    }
    return 0;
}