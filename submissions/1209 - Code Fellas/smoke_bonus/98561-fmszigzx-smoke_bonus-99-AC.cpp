#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests, n;
    long long r, t;
    cin>> tests;
    while (tests--){
        cin>> n >> r;
        long long first = 0, second = 0;
        bool ok = true;
        while (n--){
            cin >> t;
            if (first > t) ok = false;
            if (ok) {
                long long fresh = max(t, second) + r;
                first = second; 
                second = fresh;
            }
        }
        cout << (ok ? "YES" : "NO") << "\n";
    }
}