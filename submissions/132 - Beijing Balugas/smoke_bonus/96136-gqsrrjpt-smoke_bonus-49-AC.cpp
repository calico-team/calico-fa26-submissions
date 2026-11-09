#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first
#define s second  
#define int long long

bool solve(int N, int R, vector<int> &smokes) {
    int maxCap = R * 2;
    int amo = maxCap;
    int last = 1;
    for (int i = 0; i < smokes.size(); i++) {
        amo += smokes[i] - last;
        last = smokes[i];
        if (amo >= maxCap) amo = maxCap;
        amo -= R;
        if (amo < 0) {
            return false;
        }
    }
    return true;
}

signed main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N, R;
        cin >> N >> R;
        vector<int> smokes(N);
        for (int j = 0; j < N; j++) {
            cin >> smokes[j];
        }
        if (solve(N, R, smokes)) {
            cout << "YES" << "\n";
        } else cout << "NO" << "\n";
    }
}