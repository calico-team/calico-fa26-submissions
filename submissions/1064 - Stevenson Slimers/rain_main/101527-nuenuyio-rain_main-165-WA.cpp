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
        set<pii> v1;
        set<pii> v2;
        for (int i =0; i < n; i++){
            int x, y, z; cin >> x >> y >> z;
            char a; cin >> a;
            if (a=='E') {
                v1.insert({x,y});
            }
            else{
                v2.insert({x,y});
            }
        }
        int ans = n * k;
        for (auto i : v1){
            for (auto j : v2){
                int x1 = i.f;
                int x2 = j.f;
                int y1 = i.s;
                int y2 = j.s;
                if (x2 >= x1 && y1 >= y2 &&x2-x1 == y1 - y2 && x2 - x1 <= k-1){
                    ans--;
                }
            }
        }
        cout << ans<< "\n";
    }
}
