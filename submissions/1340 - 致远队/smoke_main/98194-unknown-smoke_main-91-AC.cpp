#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    long long r;
    if (!(cin >> n >> r)) return;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    long long t[2] = {0, 0};
    
    bool possible = true;

    for (int i = 0; i < n; ++i) {
        long long current_time = a[i];
        
        // Find which slot is available earliest
        // We prefer the slot that is already available or becomes available sooner
        int slot = -1;
        
        // Check if any slot is available at current_time
        if (t[0] <= current_time && t[1] <= current_time) {
            // Both available, pick the one that results in earlier next availability?
            // Actually, since recharge is sequential, picking either has similar structural impact,
            // but let's just pick index 0 for simplicity if both are ready, 
            // OR strictly follow the "earliest available" logic.
            // If both are ready, their "other" slot time is <= current_time.
            // So new time will be current_time + R for whichever we pick.
            // It doesn't matter which one we pick if both are ready.
            slot = 0; 
        } else if (t[0] <= current_time) {
            slot = 0;
        } else if (t[1] <= current_time) {
            slot = 1;
        } else {
            possible = false;
            break;
        }
        
        if (!possible) break;

        int other_slot = 1 - slot;
        long long new_time;
        if (t[other_slot] > current_time) {
            new_time = t[other_slot] + r;
        } else {new_time = current_time + r;
        }
        
        t[slot] = new_time;
    }

    if (possible) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
