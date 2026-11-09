#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int N, R; cin >> N >> R;
        vector<int> a(N);
        for (auto& i : a) cin >> i;

        int s1=0, s2=0;
        bool pos = true;
        for (int i=0; i < N; i++) {
            if (s1<=a[i]) {
                s1 = max(a[i]+R, s2+R+1);
            } else if (s2<=a[i]) {
                s2 = max(a[i]+R, s1+R+1);
            } else {
                pos = false; break;
            }
        }

        cout << (pos? "YES" : "NO") << '\n';
    }
}