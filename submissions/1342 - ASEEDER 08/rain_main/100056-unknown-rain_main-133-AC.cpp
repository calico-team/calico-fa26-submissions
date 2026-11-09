#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
struct Aircraft {
    i64 px, py, alt;
    char dir;
};
i64 count_rain(int num, int nights, vector<Aircraft>& fleet) {
    map<i64, vector<int>> by_diagonal;
    for (int k = 0; k < num; k++) {
        by_diagonal[fleet[k].px + fleet[k].py].push_back(k);
    }
    i64 collisions = 0;
    for (int a = 0; a < num; a++) {
        i64 key = fleet[a].px + fleet[a].py;
        for (int b : by_diagonal[key]) {
            const Aircraft& u = fleet[a];
            const Aircraft& v = fleet[b];

            if (u.dir == 'E' && v.dir == 'N') {
                i64 t = v.px - u.px;
                if (u.py - v.py == t && t >= 0 && t < nights && u.alt != v.alt) {
                    collisions++;
                }
            }
            else if (u.dir == 'N' && v.dir == 'E') {
               
                i64 t = u.px - v.px;
                if (v.py - u.py == t && t >= 0 && t < nights && u.alt != v.alt) {
                    collisions++;
                }
            }
        }
    }

    i64 total = (i64)num * nights;
    return total - collisions / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    while (tc--) {
        int num, nights;
        cin >> num >> nights;

        vector<Aircraft> fleet;
        fleet.reserve(num);
        for (int k = 0; k < num; k++) {
            i64 px, py, alt;
            char dir;
            cin >> px >> py >> alt >> dir;
            fleet.push_back({px, py, alt, dir});
        }
        cout << count_rain(num, nights, fleet) << '\n';
    }
    return 0;
}
