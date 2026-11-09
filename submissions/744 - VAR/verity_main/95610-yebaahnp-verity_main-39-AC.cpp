
#include <bits/stdc++.h>
using namespace std;

void find(int n, int k, vector<char> &a) {
    string ans;
    for (int i = 0; i < n; i++) {ans += "_";}

    for (int i = 0; i < a.size(); i++) {
        string sol = ans;

        for (int j = 0; j < n; j++) {
            if (sol[j] == '_') {
                sol[j] = a[i];
            }
        }

        cout << sol << endl;
        string inp;
        cin >> inp;
        if (inp == "CORRECT") {return;}

        for (int j = 0; j < n; j++) {
            if (inp[j] != '_') {
                ans[j] = inp[j];
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
