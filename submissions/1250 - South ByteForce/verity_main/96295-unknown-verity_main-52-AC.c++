#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;cin >> t;
    while (t--) {
        int n,x;cin >>n>>x;
        char a[26];
        for (int i=0;i<x; i++) {cin >> a[i];}
        string s(n, a[0]);
        while (true) {
            cout <<s<< '\n' << flush;
            string response;
            cin >> response;
            if (response == "CORRECT") break;
            for (int i = 0; i < n; i++) {
                if (response[i] != '_') s[i] = response[i];
                else {
                    int k = 0;
                    while (k < x && a[k] != s[i]) k++;
                    s[i] = a[(k+1) % x];
                }
            }
        }
    }
    return 0;
}