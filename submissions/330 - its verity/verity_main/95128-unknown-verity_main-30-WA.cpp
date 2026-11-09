#include <bits/stdc++.h>

using namespace std;
#define sz(x) ((int)x.size())
typedef long long ll;
int n, m, k;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    while (n --) {
        cin >> m >> k;
        char l[k];
        string s = ""; string b;
        for (int i = 0; i < m; i ++) s += "_";
        for (int i = 0; i < k; i ++) {
            cin >> l[i];
        }
        for (int i = 0; i < k; i ++) {
            for (int j = 0; j < m; j ++) {
                cout << l[i];
            }
            cout << "\n" << flush;
            cin >> b;
            for (int j = 0; j < m; j ++) {
                if (b[j] == l[i]) s[j] = l[i];
            }
        }

        cout << s << "\n" << flush;
        cin >> b;
    }
    return 0;
}
