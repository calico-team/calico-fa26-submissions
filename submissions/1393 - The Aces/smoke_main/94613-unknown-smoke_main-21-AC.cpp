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
        int n,r;
        cin >> n >> r;
        bool pos = true;
        vector<int>smk(2);
        vector<int>v(n);
        smk[0] = r;
        smk[1] = r;
        for(int i = 0; i < n; i++){
            cin >> v[i];
            if(i != 0){
                int dif = v[i]-v[i-1];
                smk[0] += dif;
                if(smk[0] > r){
                    smk[1] += smk[0]-r;
                    smk[0] = r;
                    if(smk[1] > r)smk[1] = r;
                }
            }
            if(smk[0] == r){
                smk[0] = smk[1];
                smk[1] = 0;
            }
            else pos = false;
        }
        if(pos)cout << "YES\n";
        else cout << "NO\n";
        t--;
    }
}