#include <iostream>
#include <vector>
using namespace std;

vector<int> t;
bool found = false;

int main() {
    int T, N, R;
    cin >> T;

    while (T--) {
        cin >> N >> R;
        t.resize(N);
        for (int i = 0; i < N; i++) {
            cin >> t[i];
        }
        if (N <= 2) {
            cout << "YES" << "\n";
            continue;
        }
        
        for (int i = 2; i < N; i++) {
            if (t[i-2] > t[i] - R) {
                found = true;
                break;
            }
        }
        if (found) cout << "NO" << "\n";
        else cout << "YES" << "\n";
    }

    return 0;
}