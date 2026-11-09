#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int main(){
    int tt; cin >> tt;

    while(tt--){
        int n,k; cin >> n >> k;

        vector<int> a(n+1);
        
        queue<int> requests;
        queue<int> recharge;

        for(int i = 1; i <= n; i++){
            cin >> a[i];
            requests.push(a[i]);
        }

        int cnt = 2;
        int ans = 0;


        while(requests.size()){
            int t;
            bool qt;
            if (recharge.empty() || requests.front() < recharge.front()) {
                qt = true;
                t = requests.front();
                requests.pop();
            } else {
                qt = false;
                t = recharge.front();
                recharge.pop();
            }

            //cout << t << " " << qt << " " << tc[0] << " " << tc[1] << "\n";
            if(qt){

                if(!cnt) break;
                cnt--;
                ans++;
                if(cnt == 1) recharge.push(t + k);

            }

            if(!qt){
                cnt++;

                if(cnt == 1) recharge.push(t + k);
            }

        }


        cout << (ans == n ? "YES\n" : "NO\n");

    }
}