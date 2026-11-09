#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void solve() {
    int N, R;
    if (!(cin >> N >> R)) return;
    
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    
    int charges = 2;
    queue<int> recharge_times;
    
    for (int i = 0; i < N; ++i) {
        int t = A[i];

        while (!recharge_times.empty() && recharge_times.front() <= t) {
            recharge_times.pop();
            charges++;
        }

        if (charges == 0) {
            cout << "NO\n";
            return;
        }
        
        charges--;
        if (recharge_times.empty()) {
            recharge_times.push(t + R);
        } else {
            recharge_times.push(recharge_times.back() + R);
        }
    }
    
    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}