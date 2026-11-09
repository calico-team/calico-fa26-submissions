#include "bits/stdc++.h"

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

constexpr int mm = 2e5 + 3;

void solve() {
    int n, k;
    cin >> n >> k;
    
    char a[30];
    for (int i = 0; i < k; i++) cin >> a[i];
    
    string s(n, a[0]);
    for (int i = 1; i <= k; i++) {
        cout << s << '\n';
        cin >> s;
        if (s == "CORRECT") break;
        for (int j = 0; j < n; j++) {
            if (s[j] == '_') s[j] = a[i];
        }
    }
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(nullptr); cout.tie(nullptr);
    
    int t = 1;
    cin >> t;
    while (t--) solve();
} 