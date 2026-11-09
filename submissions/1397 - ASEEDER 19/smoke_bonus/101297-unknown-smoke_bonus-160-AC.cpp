#include <iostream>
using namespace std;

const long long INF = 4e18;

string solve(int N, long long R, long long A[]) {
    int smoke = 2;
    long long next_recharge = INF;

    for (int i = 0; i < N; i++) {
        while (next_recharge <= A[i] && smoke < 2) {
            smoke++;
            if (smoke == 2) {
                next_recharge = INF; 
            } else {
                next_recharge += R; 
            }
        }
        if (smoke == 0) {
            return "NO";
        }
        smoke--;
        if (smoke == 1) {
            next_recharge = A[i] + R;
        }
    }

    return "YES";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T; 
    if (cin >> T) {
        while (T--) {
            int N;
            long long R;
            cin >> N >> R;
            long long A[100005];
            for (int i = 0; i < N; i++) {
                cin >> A[i];
            }
            cout << solve(N, R, A) << "\n";
        }
    }
    return 0;
}
