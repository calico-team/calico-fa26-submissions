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
    long long t1 = -1;
    long long t2 = -1;
    
    bool ok = true;
    
    for (int i = 0; i < n; i++) {
        long long cur = a[i];
        
        while (t1 != -1 && cur >= t1) {
            charges++;
            t1 = t2;
            t2 = -1;
        }
        
        if (charges > 2) {
            charges = 2;
        }
        
        if (charges > 0) {
            charges--;
            if (t1 == -1) {
                t1 = cur + r;
            } else {
                t2 = t1 + r;
            }
        } else {
            ok = false;
        }
    }
    
    if (ok) {
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