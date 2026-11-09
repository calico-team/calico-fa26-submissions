#include<iostream>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        int n;
        long long r;
        cin >> n >> r;

        long long a=0, b=0;
        bool ok = true;

        for(int i = 0; i < n; i++){
            long long time;
            cin >> time;

            if(a>b){
                swap(a,b);
            }

            if(time<a){
                ok = false;
            }

            if(ok){
                a = max(time,b) + r;
            }

        }

        if(ok){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }

    }
    return 0;
}
