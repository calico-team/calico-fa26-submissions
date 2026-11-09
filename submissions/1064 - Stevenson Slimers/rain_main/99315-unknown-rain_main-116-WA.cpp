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
        map<pii,int> v1;
        map<pii,int> v2;
        for (int i =0; i < n; i++){
            int x, y, z; cin >> x >> y >> z;
            string a; cin >> a;
            if (a=="E") {
                v1[{x,y}]++;
            }
            else{
                v2[{x,y}]++;
            }
        }
        int ans = n * k;
        map<int,int> m;
        for (auto i : v1){
            for (auto j : v2){
                int x1 = i.f.f;
                int x2 = j.f.f;
                int y1 = i.f.s;
                int y2 = j.f.s;
                if (x2-x1 == y1 - y2 && x2 - x1 <= k-1){
                    ans -= i.s+j.s-1;
                }
            }
        }
        cout << ans<< "\n";
    }
}
