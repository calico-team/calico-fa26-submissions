// Success consists of going from failure to failure without loss of enthusiasm.
// ad hoc ad hoc go away, come again another day
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <iostream>
#define int long long
#define double long double
#pragma GCC optimize("Ofast,unroll-loops")
using namespace std;
struct pi{
    int r,c,p;
};
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    vector<int>near((int)1e6+1);
    for(int i = 1; i <= 1e3; i++)for(int j = i*i; j < min((i+1)*(i+1), (int)1e6+1); j++)near[j] = i;
    while(t > 0){
        int n,m,q;
        cin >> n >> m >> q;
        vector<pi>v(q);
        for(int i = 0; i < q; i++){
            int r,c,p;
            cin >> r >> c >> p;
            v[i] = {r,c,p};
        }
        vector<vector<int>>ans(n, vector<int>(m));
        for(int i = q-1; i >= 0; i--){
            int cr = v[i].r, cc = v[i].c, cp = v[i].p;
            for(int j = 0; j <= cp; j++){
                int d = near[cp*cp-j*j];
                for(int k = max((int)0,cr-d); k <= min(n-1, cr+d); k++){
                    if((cc+j) >= 0 && (cc+j) < m && ans[k][cc+j] == 0)ans[k][cc+j] = cp*cp-(j*j)-(abs(k-cr)*abs(k-cr))+1;
                    if((cc-j) >= 0 && (cc-j) < m && ans[k][cc-j] == 0)ans[k][cc-j] =  cp*cp-(j*j)-(abs(k-cr)*abs(k-cr))+1;
                }
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++)cout << ans[i][j] << " ";
            cout << "\n";
        }
        t--;
    }
}