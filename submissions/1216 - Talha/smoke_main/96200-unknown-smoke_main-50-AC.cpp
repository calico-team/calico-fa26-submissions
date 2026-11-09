#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

string solve(int N, int R, vector<int> A) {
    queue<long long> ready;
    ready.push(0);
    ready.push(0);
    long long last_finish = 0;

    for (int t : A) {
        if (ready.front() > t) {
            return "NO";
        }
        ready.pop();
        last_finish = max((long long)t, last_finish) + R;
        ready.push(last_finish);
    }
    return "YES";
}

int main() {
    int T; cin >> T;
    while (T--) {
        int N, R; cin >> N >> R;
        vector<int> A(N);
        for (int i = 0; i < N; i++) cin >> A[i];
        cout << solve(N, R, A) << "\n";
    }
}