#include <bits/stdc++.h>
using namespace std;

void program(){
    int n, r;
    cin >> n >> r;
    int c1 = r, c2 = r;
    int a[n];

    bool result = true;

    for(int i = 0; i < n; ++i){
        cin >> a[i];
    }
    
    for(int i = 0; i < n; ++i){
        if(i == 0){
            c1 = 0;
            continue;
        }

        // Update
        int availableTime = a[i] - a[i-1];
        if(c1 + availableTime >= r){
            availableTime -= (r - c1);
            c1 = r;

            if(c2 < r){
                if(c2 + availableTime >= r)
                    c2 = r;
                else
                    c2 += availableTime;
            }
        }else{
            c1 += availableTime;
        }

        // Taking charges
        if(c1 == r){
            c1 = 0;
        }else if(c2 == r){
            c2 = 0;
        }else{
            result = false;
            break;
        }
    }

    if(result)
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        program();
    }

    return 0;
}