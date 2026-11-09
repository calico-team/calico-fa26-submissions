#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while(t--){
        int n, r; cin >> n >> r;
        int a[n];
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int x = 2; int c = 0;
        if(a[1] < a[0] + r){x = 1;}
        for (int i = 1; i < n; i++) {
            if(x == 0 && a[i] < a[i-1] + r){cout << "NO\n"; c = 1;break;}
            else if(x == 0 && a[i] >= a[i-1] + 2*r){x += 1; continue;}
            else if(x == 0 && a[i] >= a[i-1] + r){continue;}
            else if(x == 1 && a[i] >= a[i-1] + r){continue;}
            else if(x == 1 && a[i] < a[i-1] + r){x -= 1; continue;}
            else{x -= 1;}
        }
        if(c == 0) cout << "YES\n";
    }
}