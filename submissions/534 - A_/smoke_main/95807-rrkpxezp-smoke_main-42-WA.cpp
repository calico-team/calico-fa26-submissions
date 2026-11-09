#include <bits/stdc++.h>
#include <ostream>
using namespace std;

int main() {
    long long t; cin >> t;
    while(t--){
        long long n,r; cin >> n >> r;
        long long available = 2;
        long long prev = 0;
        long long pos = true;
        for(long long i = 0; i < n; i++){
            long long x; cin >> x;
            if(available+(x-prev)/r<=2){
                available = available+(x-prev)/r;
            }
            else{
                available = 2;
            }
            if((x-prev)/r>0){
                long long a = (x-prev)/r;
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

