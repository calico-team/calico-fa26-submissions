
#include <bits/stdc++.h>
using namespace std;

void find(int n, int k, vector<char> &a) {
    string ans;
    for (int i = 0; i < n; i++) {ans += "_";}

    for (int i = 0; i < a.size(); i++) {
        string sol = ans;

        for (int k = 0; k < n; k++) {
            if (sol[i] == '_') {
                sol[i] = a[i];
            }
        }

        cout << sol << endl;
        string inp;
        cin >> inp;
        if (inp == "CORRECT") {return;}

        for (int k = 0; k < n; k++) {
            if (inp[i] != '_') {
                ans[i] = inp[i];
            }
        }
    }
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, k; cin >> n >> k;
        vector<char> a(k);
        for (char &i : a) {cin >> i;}
        find(n, k, a);
    }
    return 0;
}
