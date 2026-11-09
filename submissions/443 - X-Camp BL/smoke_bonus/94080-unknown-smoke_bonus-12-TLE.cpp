#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve() {
    int n;
    int N; ll R;
    if (!(cin >> N >> R)) return;
    vector<ll> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    ll ch = 2; ll rec = -1;
    ll secnd = -1;
    bool pos = true;
    for (int i = 0; i < N; ++i) {
        ll curt = A[i];
        while (ch < 2 && rec != -1 && rec <= curt) {
            ch++;
            if (ch == 1 && secnd != -1) {
                rec = secnd;
                secnd = -1;
            } else {
                rec = -1;
            }
        }
        if (ch == 0) {
            pos = false; break;
        }
        ch--;   
        if (ch == 1) {
            rec = curt + R;
        } else if (ch == 0) {
            secnd = rec + R;
        }
    }   
    if (pos) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}
int main() {
    int T;
    if (cin >> T) {
        while (T--) solve();
    }
}
