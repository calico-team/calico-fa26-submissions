#include <bits/stdc++.h>
using namespace std;
bool check_charge(bool charge1, bool charge2, int time_charge1, int time_charge2, int time) {
    if(charge1) return true;
    else if(charge2) return true;
    else return false;
}
int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) {
        int r; int n;
        bool charge1 = true; bool charge2 = true;
        cin >> n >> r;
        int a;
        int time = 0;
        int time_charge1 = 0; int time_charge2 = 0;
        bool ok = true;
        for (int i = 0; i < n; i++) {
            cin >> a;
            if(!ok) continue;
            time = a;
            //add charges before request
            if(!charge1 && time_charge1 <= time) {
                charge1 = true;
            }
            if(!charge2 && time_charge2 <= time) {
                charge2 = true;
            }
            if(!check_charge(charge1, charge2, time_charge1, time_charge2, time)) {
                cout << "NO" << endl;
                ok = false;
                continue;
            }
            //use charge
            if(charge2) {
                charge2 = false;
                if(charge1) time_charge2 = time + r;
                else time_charge2 = time_charge1 + r;
            } else if(charge1) {
                charge1 = false;
                time_charge1 = time_charge2 + r;
            }
        }
        if(ok) cout << "YES" << endl;
    }
}