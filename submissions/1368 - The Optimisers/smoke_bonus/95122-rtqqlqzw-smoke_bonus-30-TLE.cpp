
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        long long n;
        long long r;
        cin >> n >> r;

        queue<long long> re;
        long long ch = 2;

        for (int i = 0; i < n; i++) {
            long long a;
            cin >> a;

           
            while (!re.empty() && re.front() <= a) {
                re.pop();
                ch++;
            }

           
            if (ch == 0) {
                cout << "NO\n";

               
                for (int j = i + 1; j < n; j++) {
                    cin >> a;
                }

                break;
            }

           
            ch--;

          
            long long f;

            if (re.empty()) {
                f = a + r;
            } else {
                f = re.back() + r;
            }

            re.push(f);

            if (i == n - 1) {
                cout << "YES\n";
            }
        }
    }

    return 0;
}
