// #define DEBUG
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf (int)1e18

int32_t main() {
	#ifdef DEBUG
    freopen("problemname.in", "r", stdin);
    // freopen("problemname.out", "w", stdout); 
    #endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--){
        int n, k;
        cin >> n >> k;

        map<int, vector<pair<int, int>>> east;
        map<int, vector<pair<int, int>>> north;
        int ans = n * k;
        set<int> sms;

        for (int i = 0; i < n; i++){
            int a, b, c;
            char d;
            cin >> a >> b >> c >> d;

            if (d == 'E') east[a + b].push_back({a, b});
            if (d == 'N') north[a + b].push_back({a, b});
            sms.insert(a + b);
        }

        for (auto i: sms){
            sort(east[i].begin(), east[i].end());
            sort(north[i].begin(), north[i].end());
        }
        for (auto i: sms){
            int ei = 0;
            int ni = 0;
            int ne = 0;
            while (ei < east[i].size() && ni < north[i].size()){
                if (east[i][ei].first > north[i][ni].first){
                    ni++;
                }
                else {
                    ne = ni;
                    while (true){
                        if (ne == north[i].size()) break;
                        if (north[i][ne].first - east[i][ei].first >= k) break;

                        ne++;

                    }
                    
                    ans -=  ne - ni;
                    ei++;
                }
            }
        }
        

        cout << ans << "\n";
    }
    
}