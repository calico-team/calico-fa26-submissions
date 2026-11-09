
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

long long solve(int N, int K, vector<tuple<int, int, int, char>> L) {

   
    vector<tuple<int, int, char>> dr;
    for (auto [x, y, z, d] : L) {
        dr.push_back({x + y, x, d});
    }
    sort(dr.begin(), dr.end());
ll me = 0;
int i = 0;
    while (i < N) {
        int j = i;
        while (j < N &&
               get<0>(dr[j]) == get<0>(dr[i])) {
            j++;
        }
        vector<int> e, nor;
        for (int p = i; p < j; p++) {
            int x = get<1>(dr[p]);
            char d = get<2>(dr[p]);
            if (d == 'E')
                e.push_back(x);
            else
                nor.push_back(x);
        }
        int l = 0, r = 0;
        int m = nor.size();
        for (int x : e) {
            while (l < m && nor[l] <= x)
                l++; 
            while (r < m &&
                   (ll)nor[r] <= (ll)x + K - 1)
                r++;
            me += r - l;
        }
        i = j;
    }
    return (ll)N * K - me;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;




    
    while (t--) {

        int N, K;
        cin >> N >> K;

        vector<tuple<int, int, int, char>> L;

        for (int i = 0; i < N; i++) {

            int X, Y, Z;
            char D;

            cin >> X >> Y >> Z >> D;

            L.push_back({X, Y, Z, D});
        }

        cout << solve(N, K, L) << '\n';
    }

    return 0;
}
