#include <bits/stdc++.h>
#include <ostream>
using namespace std;

int main() {
    int t; cin >> t;
    while(t--){
        int n,r; cin >> n >> r;
        int available = 2;
        int prev = 0;
        int pos = true;
        for(int i = 0; i < n; i++){
            int x = 0; cin >> x;
            available = min(available+(x-prev)/r,2);
            if((x-prev)/r >0){
                int a = (x-prev)/r;
                prev += a*r;
            }
            if(available<=0){
                pos = false;
            }
            available--;
        }
        if(pos){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
    }
}

