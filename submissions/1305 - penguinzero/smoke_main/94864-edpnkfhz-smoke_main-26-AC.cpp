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
        bool possible = true;

        for(int i = 0; i < n; i++){
            while(charges < 2 && rechargeTime <= a[i]){
                charges++;
                rechargeTime += r;
            }
            if(charges == 0){
                possible = false;
                break;
            }
            if(charges == 2){
                rechargeTime = a[i] + r;
            }
            charges--;
        }

        if(possible){
            cout << "YES" << '\n';
        }else{
            cout << "NO" << '\n';
        }
    }
}
