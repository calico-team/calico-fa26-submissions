#include <bits/stdc++.h>
using namespace std;

struct Drone {
    int sum, x;
    char dir;

    bool operator<(const Drone& other) const {
        if (sum != other.sum) return sum < other.sum;
        return x < other.x;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        int N;
        long long K;
        cin >> N >> K;

        vector<Drone> a(N);

        for (int i = 0; i < N; i++) {
            int x, y, z;
            char d;
            cin >> x >> y >> z >> d;

            a[i] = {x + y, x, d};
        }

        sort(a.begin(), a.end());

        long long ans = N * K;
        deque<int> q;

        for (int i = 0; i < N; i++) {
            if (i > 0 && a[i].sum != a[i-1].sum)
                q.clear();

            if (a[i].dir == 'E') {
                q.push_back(a[i].x);
            } else {
                while (!q.empty() && q.front() + K <= a[i].x)
                    q.pop_front();

                ans -= q.size();
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
