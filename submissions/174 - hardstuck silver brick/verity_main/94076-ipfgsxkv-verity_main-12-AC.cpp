#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        vector<char> arr(k);
        for (int i = 0; i < k; i++) cin >> arr[i];
        string known = "";
        for (int i = 0; i < n; i++) known += "_";
        for (int i = 0;; i++) {
            int ind = min(i, k - 1);
            string guess = known;
            for (int j = 0; j < n; j++) if (guess[j] == '_') guess[j] = arr[ind];
            cout << guess << endl;
            string res; cin >> res;
            if (res == "CORRECT") break;
            for (int j = 0; j < n; j++) if (res[j] != '_') known[j] = res[j];
        }
    }
}
