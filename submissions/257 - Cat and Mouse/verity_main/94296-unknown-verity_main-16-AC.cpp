#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using str = string;

#define int long long
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
#define F first
#define S second
#define pb push_back
#define fox(i,n) for(int i=0;i<(n);++i)

vector<pii> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};


signed main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        vector<char> chars(k); 
        fox(i, k) cin>>chars[i];
        vector<int> idx(n, 0);
        // cout << "DEBUG"; return 0;
        while (1) {
            string guess = "";
            fox(i, n) {
                guess += chars[idx[i]];
                // cout << idx[i] << ' ' << chars[idx[i]] << '\n';
            }
            cout << guess << endl;
            // cout << "DEBUG"; return 0;
            string ans; cin >> ans;
            if (ans == "CORRECT") {
                break;
            }
            fox(i, n) {
                if (ans[i] == '_') idx[i]++;
            }
        }
    }

    return 0;
}


/*


*/