#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<char> letters(k);
        for (int i = 0; i < k; i++) {
            cin >> letters[i];
        }

        string guess(n, '_');

        for (int i = 0; i < k; i++) {
            
            for (int j = 0; j < n; j++) {
                if (guess[j] == '_') {
                    guess[j] = letters[i];
                }
            }

            
            cout << guess << endl;

            string response;
            if (!(cin >> response)) return 0;
            if (response == "CORRECT") break;

            guess = response;
        }
    }

    return 0;
}
