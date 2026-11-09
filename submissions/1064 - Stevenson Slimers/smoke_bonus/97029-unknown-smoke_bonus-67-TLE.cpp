// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while(t--){
        int n, cd; cin >> n >> cd;
        int time = 0;
        int acc= 0;
        int charges = 2;
        bool x = true;
        // code doesn't do anything
        while(n--){
            int a; cin >> a;
            if (!x) continue;
            int dif = a - time;
            acc += dif;
            time = a;
            while (charges < 2 && acc >= cd){
                charges++;
                acc = acc - cd;
            }
            if (charges == 2){
                acc = 0;
            }
            if (charges == 0){
                x = false;
            }
            charges--;
        }
        if (x) cout << "YES\n";
        else cout << "NO\n";
    }
}
