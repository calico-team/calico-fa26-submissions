// Success consists of going from failure to failure without loss of enthusiasm.
// ad hoc ad hoc go away, come again another day
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <iostream>
#define int long long
#define double long double
#pragma GCC optimize("Ofast,unroll-loops")
using namespace std;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t > 0){
        int n,k;
        cin >> n >> k;
        bool solved = false;
        vector<string>v(k);
        vector<string>pos(n);
        for(int i = 0; i < k; i++)cin >> v[i];
        for(int i = 0; i < k; i++){
            string q = "";
            for(int j = 0; j < n; j++)q += v[i];
            cout << q << "\n";
            cout.flush();
            string res;
            cin >> res;
            if(res == "CORRECT"){
                solved = true;
                break;
            }
            else for(int j = 0; j < n; j++)if(res[j] != '_')pos[j] = v[i];
        }
        if(!solved){
            string ans = "";
            for(int i = 0; i < n; i++)ans += pos[i];
            cout << ans << "\n";
            cout.flush();
            string garbage;
            cin >> garbage;
        }
        t--;
    }
}