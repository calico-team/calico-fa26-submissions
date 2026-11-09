#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        bool req[100005] = {};
        int n, r; cin >> n >> r;
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            req[x] = true;
        }
        
        int time1 = 0, time2 = 0;
        bool pos = true;
        for (int sec = 1; sec < 100005; sec++) {
            if (time1 > 0) time1--;
            else if (time2 > 0) time2--;
            if (!req[sec]) continue;
            
            if (time1 == 0) time1 = r;
            else if (time2 == 0) time2 = r;
            else { pos = false; break; }
        }
        cout << (pos ? "YES\n" : "NO\n");
    }
}
