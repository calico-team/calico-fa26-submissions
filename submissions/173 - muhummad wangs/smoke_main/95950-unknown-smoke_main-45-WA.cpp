#include<bits/stdc++.h>


using namespace std;

int main() {
ios::sync_with_stdio(false);
cin.tie(nullptr);

    int cases = 0;
    cin >> cases;
    cin.ignore(1000, '\n');
    for (int _ = 0; _ < cases; ++_) {

        int n, r;

        cin >> n >> r;

        bool one = true;
        bool two = true;

        int curTime = 0;

        bool first = true;
        bool bad = false;
        
        for (int i = 0; i < n; ++i) {
            int time;
            cin >> time;

            curTime += time;

            if (curTime % r == 0) {
                if (!one) {
                    one = true;
                } else {
                    two = true;
                }
            }

            if (!one && !two) {
                bad = true;
                break;
            } else {
                if (two) {
                    two = false;
                } else {
                    one = false;
                }
            }
        }

        if (bad) {
            cout << "NO" << '\n';
        } else {
            cout << "YES" << '\n';
        }

        
    // REMEMBER TO CLEAN UP OUTPUT FOR SUBMISSION!!!
    }
}