#include <bits/stdc++.h>
using namespace std;
#define int long long

bool solve(){
    int n, r; cin >> n >> r;

    vector<int> a(n); for(int &x : a) cin >> x;

    int c = 2, nxt = 0;

    for(int x : a){
        while(c < 2 && nxt <= x){
            c++;
            if(c < 2) nxt += r;
        }

        if(c == 0) return false;

        if(c == 2) nxt = x + r; //max of 2

        c--;
    }

    return true;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t = 1; cin >> t;
    
    while(t--){
        if(solve()){
            cout << "YES\n";
        }else cout << "NO\n";
    }

}