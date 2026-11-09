#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first
#define s second  
#define int long long

signed main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {

        int n, k;
        cin >> n >> k;

        map<int, vector<pair<int, int>>> c;
        for(int i = 0; i < n; i++) {

            int x, y, z;
            char d;
            cin >> x >> y >> z >> d;

            if(d == 'N') {

                c[x + y].push_back({y, 0});

            } else {

                c[x + y].push_back({y, 1});

            }

        }

        int ans = n * k;

        for(auto i : c) {

            vector<pair<int, int>> vals = i.s;

            vector<int> east, north;

            for(int i = 0; i < vals.size(); i++) {

                if(vals[i].s == 0) {

                    north.push_back(vals[i].f);

                } else {

                    east.push_back(vals[i].f);

                }

            }

            sort(north.begin(), north.end());

            for(int i = 0; i < east.size(); i++) {

                auto l = upper_bound(north.begin(), north.end(), east[i] - k), r = upper_bound(north.begin(), north.end(), east[i]);
                ans -= (r - l);

            }

        }

        cout << ans << endl;
        
    }

}