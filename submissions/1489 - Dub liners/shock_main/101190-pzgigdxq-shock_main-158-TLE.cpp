// #define DEBUG
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf (int)1e18


void solve(){
    int n, m, q;
    cin >> n >> m >> q;

    bool swapped = false;

    if (n > m){
        swapped = true;
        swap(n, m);
    }

    vector<array<int, 3>> eqs;
    for (int i = 0; i < q; i++){
        int row, col, pow;
        cin >> row >> col >> pow;

        if (swapped) swap(row, col);
        eqs.push_back({row, col, pow});

    }

    int seis[n][m];

    // always less rows
    for (int row = 0; row < n; row++){

        vector<pair<int, int>> point[m];
        int id = -1;
        for (auto eq: eqs){
            id ++;
            if (eq[2] < abs(eq[0] - row)) continue;
            int left, right;
            int rdiff = abs(eq[0] - row);

            {
                int s = sqrt(eq[2] * eq[2] - rdiff * rdiff);
                left = eq[1] - s;
                right = eq[1] + s;
            }
            
            point[left].push_back({1, id});
            point[right].push_back({-1, id});
            // cout << row << " " << left << " " << right << " " << id << "\n";
        }

        // id
        set<int> active;
        for (int col = 0; col < m; col++){
            for (auto i: point[col]){
                if (i.first == 1){
                    active.insert(i.second);
                }
            }
            if (active.empty()) seis[row][col] = 0;
            else {
                int id = *active.rbegin();
                // cout << row << " " << col << " " << id << "\n";
                int rdiff = abs(row - eqs[id][0]);
                int cdiff = abs(col - eqs[id][1]);
                seis[row][col] = eqs[id][2] * eqs[id][2] -  (rdiff * rdiff + cdiff * cdiff) + 1;
            }

            for (auto i: point[col]){
                if (i.first == -1){
                    active.erase(i.second);
                }
            }

        }
    }

    // start or end, id
    // vector<pair<int, int>> point[n][m];



    if (!swapped){
        for (int row = 0; row < n; row++){
            for (int col = 0; col < m; col++){
                cout << seis[row][col] << " ";
            }
            cout << "\n";
        }
    }
    else {

        for (int row = 0; row < m; row++){
            for (int col = 0; col < n; col++){
                cout << seis[col][row] << " ";
            }
            cout << "\n";
        }
    }
    
}

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
        solve();
    }
}