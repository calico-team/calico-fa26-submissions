#include <bits/stdc++.h>
using namespace std;

int main() {
    int t = 0;
    cin >> t;
    for (int a = 0; a < t; a++) {
        int n, m, k;
        cin >> n >> m >> k;

        int p[n];
        for (int i = 0; i < n; i++) {
            cin >> p[i];
        }
        int depth[n];
        //counts each possible depth
        for (int i = 0; i < n; i++) {
            int cur = p[i];
            int length = 1;
            
            
            while (cur != 0) {
                cur = p[cur - 1]; 
                length++;
            }
            depth[i] = length;
        }

        int cnt[m + 1];
        for (int s = 0; s <= m; s++) {
            cnt[s] = 0;
        }

        for (int i = 0; i < n; i++) {
            if (depth[i] <= m) {
                cnt[depth[i]]++;
            }
        }

        // Simulate semesters
        int total = 0;
        int ready = 0;
        for (int s = 1; s <= m; s++) {
            ready += cnt[s];        
            int take = min(k, ready);
            total += take;
            ready -= take;          
        }

        cout << total << endl;
    }
}