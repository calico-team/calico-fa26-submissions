#include <iostream>
using namespace std;

int main(){
    int t;
    cin >> t;

    while (t--){
        int n, r;
        cin >> n >> r;

        int c = 2;
        long long pr = -1;
        bool ok = true;

        for (int i = 0; i < n; i++){
            long long a;
            cin >> a;

            if (ok) {
                while (c < 2 && pr != -1 && pr <= a){
                    c++;
                    pr += r;

                    if (c == 2){
                        pr = -1;
                    }
                }

                if (c == 0){
                    ok = false;
                }
                else {
                    c--;

                    if (c == 0 && pr == -1){
                        pr = a + r;
                    }
                }
            }
        }

        if (ok){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
    }
    return 0;
}