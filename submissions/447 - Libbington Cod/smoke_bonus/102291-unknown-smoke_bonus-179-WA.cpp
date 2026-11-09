// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
	int t;
    cin >> t;
    while (t--) {
        int n, r;
        cin >> n >> r; 
        vector<int> calls(n);
        int charges = 2; 
        int extra = 0; 
        charges--;
        bool right = true; 
        cin >> calls[0];
        for (int i = 1; i < n; i++) {
            cin >> calls[i];
            extra += (calls[i]-calls[i-1]);
            if (extra >= r && charges < 2) {
                extra-=r; 
                charges++; 
            }
            if (extra >= r && charges < 2) {
                extra-=r; 
                charges++; 
            }
            charges--;
            if (charges < 0) {
                if (right != false) {
                cout << "NO" << endl;

                }
                            right = false;

            }
        }
        if (right == true) {
            cout << "YES" << endl;
        }
    }
}
