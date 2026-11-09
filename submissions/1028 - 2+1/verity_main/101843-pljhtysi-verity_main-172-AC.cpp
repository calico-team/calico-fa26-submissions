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
        for (int i = 0; i < n; i++) {
            cout << c[i % k];
        }
        cout << endl;
        cout.flush();
        string s;
        int cnt = 0;
        while (cin >> s) {
            if (s == "CORRECT") {
                break;
            }
            else {
                
                for (int i = 0; i < n; i++) {
                    if (s[i] == '_') cout << c[(i+cnt)%k];
                    else cout << s[i];
                }
                cnt++;
                cout << endl; cout.flush();
            }
        }
    }
    
    
}
