#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
    int n, r;
    cin >> n >> r;

    priority_queue<pair<int,int>> pq;
    //{-n, 1} = refill
    //{-n, 0} = use

    int charges = 2;
    for (int i = 0; i < n; i ++){
        int time;
        cin >> time;

        pq.push({-time, 0});
    }
    int last = 4e18;
    while(!pq.empty()){
        int a = pq.top().first;
        int b = pq.top().second;
        pq.pop();

        if (b == 0){
            //use
            if (charges == 0){
                //not possible;
                cout << "NO" << "\n";
                return;
            }
            else{
                charges--;
                pq.push({min(a-r, last-r),1});
                last = min(last-r, a-r);
            }
        }
        if (b == 1){
            charges ++;
            if (charges < 2){
                pq.push({min(a-r, last-r), 1});
            }
            last = min(last-r, a-r);
        }

    }
    cout << "YES" << "\n";
}

int32_t main(){
    int tt;
    cin >> tt;
    while(tt--){
        solve();
    }
}