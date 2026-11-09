#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    if (!(cin >>t)) return 0;
    
    while (t--) {
        int n, k;
        cin >> n>>k;
        char a[30];
        for (int i =0; i < k; i++) cin >> a[i];
        string ans(n, '?'), res;
        int j =0;

        while (j <k) {
            string cur =ans;
            for (char &c :cur) {
                if (c =='?') c = a[j];
            }

            cout << cur << endl;

            if (!(cin >>res)) return 0;
            if (res =="CORRECT") break;

            for (int i =0; i < n; i++) {
                if (res[i] != '_') ans[i] = res[i];
            }
            j++;
        }
    }
    // semoga ga ada corner case nyeleneh

    return 0;
}