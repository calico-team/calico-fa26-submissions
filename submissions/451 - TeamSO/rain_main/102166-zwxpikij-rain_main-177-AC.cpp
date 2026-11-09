#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    while (T--){
        ll N, K; cin >> N >> K;
        vector<pair<int,int>> E, V;
        for (int i = 0; i < N; i++){
            ll x, y, z; cin >> x >> y >> z;
            char d; cin >> d;
            if (d == 'E'){
                E.push_back({x + y, x});
            }
            else{
                V.push_back({x + y, x});
            }
        }
        sort(E.begin(), E.end());
        sort(V.begin(), V.end());
        ll total = N * K;
        int j = 0, l = 0;
        for (pair [s, x] : V){
            while ((j < (int)E.size()) && (E[j].first < s)){
                j++;
            }
            l = max(l, j);
            while ((l < (int)E.size()) && (E[l].first == s) && (E[l].second < x - K + 1)){
                l++;
            }
            int r = l;
            while (r < ((int)E.size()) && (E[r].first == s) && (E[r].second < x)){
                r++;
            }
            total -= r - l;
        }
        cout << total << '\n';
    }
    return 0;
}