// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define f first
#define s second
int main() {
    int t; cin >> t;
    while (t--){
        int n, k; cin >> n >> k;
        vector<pii> v1;
        vector<pii> v2;
        for (int i =0; i < n; i++){
            int x, y, z; cin >> x >> y >> z;
            string a; cin >> a;
            if (a=="E") {
                v1.push_back({x,y});
            }
            else{
                v2.push_back({x,y});
            }
        }
        int ans = n * k;
        set<tuple<int,int,int>> se;
        for (auto i : v1){
            for (auto j : v2){
                int x1 = i.f;
                int x2 = j.f;
                int y1 = i.s;
                int y2 = j.s;
                if (x2-x1 == y1 - y2 && x2 - x1 <= k-1){
                    ans--;
                    if (se.count({x1,y1,x2-x1})&&se.count({x2,y2,x2-x1})){
                        ans++;
                    }
                    se.insert({x1,y1,x2-x1});
                    se.insert({x2,y2,x2-x1});
                }
            }
        }
        cout << ans<< "\n";
    }
}
