//#define DEBUG
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

    vector<vector<int>> eqs;
    for (int i = 0; i < q; i++){
        int row, col, pow;
        cin >> row >> col >> pow;

        if (swapped) swap(row, col);
        eqs.push_back({row, col, pow});

    }

    // start or end, id
    vector<pair<int, int>> point[n][m];
    // always less rows
    for (int row = 0; row < n; row++){
        int id = -1;
        for (auto eq: eqs){
            id ++;
            if (eq[2] < abs(eq[0] - row)) continue;
            int left, right;
            int rdiff = abs(eq[0] - row);
            {
                int l = 0, r = eq[1];

                while (l != r){
                    int mid = (l + r) / 2;
                    int cdiff = abs(eq[1] - mid);
                    bool works;
                    if ((eq[2] * eq[2]) - ((rdiff * rdiff) + (cdiff * cdiff)) + 1 > 0){
                        works = true;
                    }
                    else {
                        works = false;
                    }

                    if (works){
                        r = mid;
                    }
                    else {
                        l = mid + 1;
                    }
                }
                left = l;

            }
            {
                int l = eq[1], r = m - 1;

                while (l != r){
                    int mid = (l + r + 1) / 2;
                    int cdiff = abs(eq[1] - mid);
                    bool works;
                    if ((eq[2] * eq[2]) - ((rdiff * rdiff) + (cdiff * cdiff)) + 1 > 0){
                        works = true;
                    }
                    else {
                        works = false;
                    }

                    if (works){
                        l = mid;
                    }
                    else {
                        r = mid - 1;
                    }
                }
                right = l;

            }

            point[row][left].push_back({1, id});
            point[row][right].push_back({-1, id});
            // cout << row << " " << left << " " << right << " " << id << "\n";
        }
    }

    // start or end, id
    // vector<pair<int, int>> point[n][m];


    int seis[n][m];

    for (int row = 0; row < n; row++){
        // id
        set<int> active;
        for (int col = 0; col < m; col++){
            for (auto i: point[row][col]){
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

            for (auto i: point[row][col]){
                if (i.first == -1){
                    active.erase(i.second);
                }
            }

        }
    }

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