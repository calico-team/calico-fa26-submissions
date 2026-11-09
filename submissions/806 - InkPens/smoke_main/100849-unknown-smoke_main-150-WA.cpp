// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    for(int uu= 0; uu<T; uu++){
        int N, R;
        cin >> N >> R;
        vector<int>x(N);

        for(int i=0; i<N;i++){ //setup 
            cin >> x[i];
        }

        int charges = 2; //charges remaining 
        int last = 0;
        string ans = "YES";

        for(int j = 0; j < N; j++) {
            int timePassed = x[j] - last; //time since last interval
            charges = min(2, charges + timePassed/R);
            if(timePassed < R && charges <= 0){ //if theres no charges by the next request 
                ans = "NO";
                break;
            }
            charges -= 1;
            last = x[j];
       
    }
    cout << ans << "\n";
 }
}
