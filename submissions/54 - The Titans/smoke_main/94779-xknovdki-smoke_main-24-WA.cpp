#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    long long r;
    cin >> n >> r;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    int charges = 2;
    long long time1 = -1; 
    long long time2 = -1; 
    
    bool possible = true;
    
    for (int i = 0; i < n; i++) {
        long long cur = a[i];
        
        
        if (time1 != -1 && cur >= time1) {
            charges++;
            time1 = -1;
        }
        if (time2 != -1 && cur >= time2) {
            charges++;
            time2 = -1;
        }
        
        if (charges > 2) charges = 2;
        
        if (charges > 0) {
            charges--;
            if (time1 == -1) {
                time1 = cur + r;
            } else if (time2 == -1) {
                time2 = cur + r;
            }
        } else {
            possible = false;
        }
    }
    
    if (possible) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}