#include <iostream>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;

    while (t--){
        int n;
        long long r;
        cin >> n >> r;

        int c = 2;
        long long pr = -1;
        bool ok = true;

        for (int i = 0; i < n; i++){
            long long a;
            cin >> a;

            if (!ok) continue;

            while (c < 2 && pr != -1 && pr <= a){
                c++;
                pr += r;

                if (c == 2) {
                    pr = -1;
                }
            }

            if (c == 0) {
                ok = false;
            }
            else {
                if (c == 2) {
                    pr = a + r;
                }

                c--;
            }
        }

        if (ok) {
            cout << "YES" << '\n';
        }
        else {
            cout << "NO" << '\n';
        }
    }
    return 0;
}