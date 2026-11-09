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
    int x,y;
};
int bs(vector<int>v, int lb, int rb){
    int l = 0, r = v.size()-1, il = v.size(), ir = -1;
    while(l <= r){
        int m = l+(r-l)/2;
        if(v[m] >= lb){
            il = m;
            r = m-1;
        }
        else l = m+1;
    }
    l = 0, r = v.size()-1;
    while(l <= r){
        int m = l+(r-l)/2;
        if(v[m] <= rb){
            ir = m;
            l = m+1;
        }
        else r = m-1;
    }
    if(il > ir)return 0;
    else return ir-il+1;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t > 0){
        int n,k;
        cin >> n >> k;
        map<int, vector<int>>r;
        map<int, vector<int>>u;
        for(int i = 0; i < n; i++){
            int x,y,z; string dir;
            cin >> x >> y >> z >> dir;
            if(dir == "E")r[x+y].push_back(x);
            else u[x+y].push_back(x);
        }
        int rmv = 0;
        for(auto &a : r){
            if(u.count(a.first)){
                sort(a.second.begin(), a.second.end());
                sort(u[a.first].begin(), u[a.first].end());
                for(int &x : a.second)rmv += bs(u[a.first], x, x+k-1);
            }
        }
        cout << n*k-rmv << "\n";
        t--;
    }
}