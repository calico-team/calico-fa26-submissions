#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        int N;
        long long R;
        cin >> N >> R;

        vector<long long> A(N);
        for (auto &x : A) cin >> x;

        int sk = 2;
        long long cd = 0;
        bool ok = true;

        for (int i = 0; i < N && ok; i++) {
            long long t = A[i];
            while (sk < 2 && cd <= t) {
                sk++;
                if (sk < 2) {
                    cd += R;  
                }
            }
            if (sk == 0) { 
                ok = false; 
                break;             
            }
            if (sk == 2){
                cd = t + R;  
            } 
            sk--;
        }
        cout << (ok ? "YES" : "NO") << '\n';
    }
    return 0;
}
