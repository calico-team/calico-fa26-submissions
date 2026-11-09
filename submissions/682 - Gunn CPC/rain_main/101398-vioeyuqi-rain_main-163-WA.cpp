#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define pii pair<int,int>

void calc(){
    int n, m;
    cin >> n >> m;
    vector<pii> north,east;
    for (int i=0;i<n;i++){
        int x,y,z;
        char c;
        cin >> x >> y >> z >> c;
        if (c=='N'){
            north.pb({x,y});
        }else{
            east.pb({x,y});
        }
    }
    int cnt = 0;
    for (auto [x,y]:north){
        for (auto [x1,y1]:east){
            if (abs(x-x1)==abs(y-y1) and abs(y-y1)<m){
                cnt++;
            }
        }
    }
    cout << n*m-cnt << endl;

}

signed main() {
    int t;
    cin >> t;
    while(t--){
        calc();
    }
}