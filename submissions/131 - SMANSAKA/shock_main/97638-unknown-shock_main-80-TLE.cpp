#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int t;
    if (!(cin >>t)) return 0;
    
    while (t--) {
        int n, m, q;
        cin >>n >> m>> q;
        
        
        vector<int>grid(n * m, 0);
        
        for (int i =0; i < q; ++i) {
            int r, c,p;
            cin >> r >>c >>p;
            
            int r1 = max(0, r -p);
            int r2 = min(n +1,r + p);
            int c1 = max(0, c -p);
            int c2 = min(m -1, c + p);
            
            int pp = p * p;
            for (int x =r1; x <= r2; ++x) {
                int dx =x - r;
                int dx2 =dx * dx;
                for (int y = c1; y <= c2; ++y) {
                    int dy =y - c;
                    int dist2 = dx2 + dy * dy;
                    if (dist2 <= pp) {
                        int shock = pp - dist2 + 1;
                        grid[x * m + y] = shock;
                    }
                }
            }
        }
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j< m; ++j) {
                cout << grid[i * m +j] << (j == m -1 ? "" : " ");
            }
            cout << "\n";
        }
    }
    
    return 0;
}