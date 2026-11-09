#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
    cin >> t;
    for(int q = 0; q < t; q++){
        int n, r;
        cin >> n >> r;
        int a[n];
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int charges = 2;
        int rechargeTime = 0;
        int secondRechargeTime = 0;
        bool possible = true;

        for(int i = 0; i < n; i++){
            if(i >= 2 && secondRechargeTime > a[i]){
                possible = false;
                break;
            }
            int finish = max(a[i], secondRechargeTime) + r;
            rechargeTime = secondRechargeTime;
            secondRechargeTime = finish;
        }

        if(possible){
            cout << "YES" << '\n';
        }else{
            cout << "NO" << '\n';
        }
    }
}
