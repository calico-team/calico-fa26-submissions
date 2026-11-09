#include "bits/stdc++.h"
#define debug(x) cout << #x << " is " << x << endl;
using namespace std;
#define int long long
#define pii pair<int, int>
template<typename T> using min_pq = priority_queue<T, vector<T>, greater<T>>;
template<typename T> using vv = vector<vector<T>>;
template<typename T> using v = vector<T>;
#define fb(x) x.begin(), x.end()
#define lsb(x) (x & -x)

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        unordered_map<int, v<int>> preq;
        for (int i = 1; i <= n; i++) {
            int num;
            cin >> num;
            preq[num].push_back(i);
        }
        unordered_set<int> done = {0};
        for (int sem = 0; sem < m; sem++) {
            int course_left = k;
            v<int> temp;
            for (int can_take: done) {
                for (int course: preq[can_take]) {
                    if (done.count(course) == 0) {
                        temp.push_back(course);
                        course_left--;
                    }
                    if (course_left == 0) {
                        break;
                    }
                }
                if (course_left == 0) {
                    break;
                }
            }
            for (int course: temp) {
                done.insert(course);
            }
        }
        cout << done.size() - 1 << '\n';
    }
    return 0;
}