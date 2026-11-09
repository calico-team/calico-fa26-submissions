#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int main(){
    int tt; cin >> tt;

    while(tt--){
        int n,k; cin >> n >> k;

        vector<int> a(n+1);

        set<pair<int,int>> events;

        for(int i = 1; i <= n; i++){
            cin >> a[i];
            events.insert({a[i], 1});
        }

        int cnt = 2;
        int ans = 0;

       
        while(events.size()){
            auto [t, qt] = *events.begin();

            events.erase(events.begin());

            //cout << t << " " << qt << " " << tc[0] << " " << tc[1] << "\n";
            if(qt){

                if(!cnt) break;
                cnt--;
                ans++;
                if(cnt == 1) events.insert({t + k, 0});
                
            }

            if(!qt){
                cnt++;

                if(cnt == 1) events.insert({t + k, 0});
            }
        
        }


        cout << (ans == n ? "YES\n" : "NO\n");

    }
}