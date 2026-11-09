#include <bits/stdc++.h>

using namespace std;



void solve(string alp, int N, int K) {
    string ans(N, alp[0]);
    while(true) {
        cout << ans << endl;
        cout.flush();
        string status;
        cin >> status;
        if(status == "CORRECT") {
            return;
        }
        for(int i = 0; i < N; i++) {
            if(status[i] == '_') {
                ans[i] = alp[(alp.find(ans[i]) + 1) % K];
            }
        }
    }
}

int main() {
    int T;
    cin >> T;
    for(int i = 0; i < T; i++) {
        int N;
        int K;
        cin >> N >> K;
        vector<char> a(K);
        for(int b = 0; b < K; b++) {
            cin >> a[b];
        }
        solve(string(a.begin(), a.end()), N, K);
    }

}


