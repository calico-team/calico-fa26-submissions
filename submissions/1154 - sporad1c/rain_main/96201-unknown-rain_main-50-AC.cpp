/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Drone {
    long long s;
    long long x;
    char d;
};
bool cmp(Drone a, Drone b) {
    return a.s < b.s;
}
void solve() {
    int n;
    long long k;
    cin >> n >> k;
    vector<Drone> a(n);
    for (int i = 0; i < n; i++) {
        long long x, y, z;
        char d;
        cin >> x >> y >> z >> d;
        a[i].s = x + y;
        a[i].x = x;
        a[i].d = d;
    }
    sort(a.begin(), a.end(), cmp);
    long long blocked = 0;
    int i = 0;
    while (i < n) {
        int j = i;
        vector<long long> ve;
        vector<long long> vn;
        while (j < n && a[j].s == a[i].s) {
            if (a[j].d == 'E') ve.push_back(a[j].x);
            else vn.push_back(a[j].x);
            j++;
        }
        sort(ve.begin(), ve.end());
        sort(vn.begin(), vn.end());
        int l = 0, r = 0;
        for (int p = 0; p < (int)ve.size(); p++) {
            long long x = ve[p];
            while (l < (int)vn.size() && vn[l] <= x) {
                l++;
            }
            while (r < (int)vn.size() && vn[r] < x + k) {
                r++;
            }
            if (r > l) blocked += (r - l);
        }
        i = j;
    }
    long long ans = (long long)n * k - blocked;
    cout << ans << "\n";
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}