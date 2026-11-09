#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct drone {
    ll x;
    ll y;
    ll z;
};

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        ll K;
        cin >> n >> K;

        vector<drone> E, N;
        for (int i = 0; i < n; i++) {
            ll x, y, z;
            char D;
            cin >> x >> y >> z >> D;
            if (D == 'E') E.push_back({x, y, z});
            else N.push_back({x, y, z});
        }

        ll lost = 0;  

        for (auto &e : E) {
            for (auto &nd : N) {
               
                ll t = nd.x - e.x;
                if (t < 0 || t > K - 1) continue;  
                if (nd.y + t != e.y) continue;      
                lost++;
            }
        }

        ll total = (ll)n * K - lost;
        cout << total << "\n";
    }
    return 0;
}