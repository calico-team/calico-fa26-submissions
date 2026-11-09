#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        vector<char> c(k);
        for (int i = 0; i < k; i++) {
            cin >> c[i];
        }
        string s;
        while (cin >> s) {
            if (s == "CORRECT") {
                return 0;
            }
            else {
                for (int i = 0; i < n; i++) {
                    if (s[i] == '_') cout << c[i];
                    else cout << s[i];
                }
                cout << endl; cout.flush();
            }
        }
    }
    
    
}
