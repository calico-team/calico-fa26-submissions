#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while(t--){
        int n; int r; cin >> n >> r;
        int a[n];
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        if(n == 1 || n == 2){cout << "YES\n";}
        else{
            int b1 = 0; int b2 = r;
            int ar[n-1]; 
            for (int i = 1; i < n; i++) {
                ar[i-1] = a[i] - a[i-1];
            }
            int c = 0;
            for (int i = 1; i < n; i++) {
                if(b1 < r && b2 < r){
                    int e = ar[i]; if(b1 + e < r){cout << "NO\n"; c = 1; break;}
                    else{
                        b1 = r; b1 = 0; e = b1 + e - r; if(b2 + e < r){b2 = b2 +e;}
                        else{b2 = r;}
                    }
                }
                else if(b1 == r && b2 < r){
                    int e = ar[i]; b1 = 0;
                    if(b2 + e < r){b2 = b2 +e;}
                    else{b2 = r;}
                }
                else if(b1 < r && b2 == r){
                    int e = ar[i];
                    if(b1 + e < r){b1 = b1 +e; b2 = 0;}
                    else{b1 = r; b1 = 0;}
                }
                else if(b1 == r && b2 == r){
                    b1 = 0;
                }
            }
            if(c == 0){cout << "YES\n";}
        }
    }
}