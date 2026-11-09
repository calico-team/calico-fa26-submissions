#include <iostream>
#include <queue>
using namespace std;

int main() {
    int T;

    cin >> T;

    while (T--) {
        int N;
        long long R;

        
        cin >> N >> R;

        queue<long long> recharge;
        int charges = 2;
        bool possible = true;

        

        for (int i = 0; i < N; i++) {
            long long A;
            cin >> A;

            while (!recharge.empty() &&
                   recharge.front() <= A) {
                recharge.pop();
                charges++;
            }

            if (charges > 0) {
                charges--;
                recharge.push(A + R);
            } else {
                possible = false;
            }
        }

        cout << (possible ? "YES" : "NO") << endl;
    }

    return 0;
}
