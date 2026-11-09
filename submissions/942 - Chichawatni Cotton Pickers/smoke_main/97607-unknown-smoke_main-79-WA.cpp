#include <iostream>
#include <vector>
using namespace std;

/**
 * Output whether all the requests can be fulfilled.
 *
 * N: Number of smoke requests
 * R: Number of seconds needed for a smoke charge to recharge
 * A: List of timestamps where smokes are requested
 */
string solve(int N, int R, vector<int> A) {
    int smoke = 2;
    int lastuse = -5;
    for (auto& i : A) {
        if (lastuse != -5) {
            if (lastuse + R*2 <= i) {
                smoke = min(2, smoke+2);
            }
            else if (lastuse + R <= i) {
                smoke = min(2, smoke+1);
            }
        }
        if (smoke-1 < 0) {
            return "NO";
            break;
        }
        smoke --;
        lastuse = i;
    }
    return "YES";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    while (T--) {
        int N, R; cin >> N >> R;
        vector<int> A(N);
        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }

        cout << solve(N, R, A) << "\n";
    }
}