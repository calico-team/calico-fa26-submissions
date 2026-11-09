#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve() {
    int N, K;
    if (!(cin >> N >> K)) return;
    vector<char> A(K);
    for (int i = 0; i < K; ++i) {
        cin >> A[i];
    }
    string curk(N, '_');
    while (true) {
        string idk = curk;
        for (int i = 0; i < N; ++i) {
            if (idk[i] == '_') {
                idk[i] = A[0];
            }
        }
        cout << idk << endl;
        string verty; cin >> verty;
        if (verty == "CORRECT") {
            break;
        }
        for (int i = 0; i < N; ++i) {
            if (verty[i] != '_') {
                curk[i] = verty[i];
            }
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) solve();
    }
}