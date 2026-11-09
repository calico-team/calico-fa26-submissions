#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


const int MAX_S = 200005;


vector<long long> E_drones[MAX_S];
vector<long long> N_drones[MAX_S];


vector<int> active_S; 

void solve() {
    int n;
    long long k;
    cin >> n >> k;
    
    for (int i = 0; i < n; i++) {
        long long x, y, z;
        char d;
        cin >> x >> y >> z >> d;
        






        
        int s = x + y;
        

        if (E_drones[s].empty() && N_drones[s].empty()) {
            active_S.push_back(s);
        }
        
        if (d == 'E') {
            E_drones[s].push_back(x);
        } else {
            N_drones[s].push_back(x);
        }
    }
    
    long long total_rain = (long long)n * k;
    

    for (int s : active_S) {

        if (E_drones[s].empty() || N_drones[s].empty()) continue;
        

        sort(N_drones[s].begin(), N_drones[s].end());
        

        for (long long xe : E_drones[s]) {

            auto it1 = lower_bound(N_drones[s].begin(), N_drones[s].end(), xe);
            

            auto it2 = upper_bound(N_drones[s].begin(), N_drones[s].end(), xe + k - 1);
            
            // distance() returns the number of valid 'N' drones that block this 'E' drone
            long long blocked = distance(it1, it2);
            total_rain -= blocked;
        }
    }
    
    cout << total_rain << "\n";

    for (int s : active_S) {
        E_drones[s].clear();
        N_drones[s].clear();
    }
    active_S.clear();
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}