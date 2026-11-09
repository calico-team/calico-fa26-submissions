#include <iostream>
#include <set>
#include <vector>
using namespace std;

long long solveOne(const vector<long long>& L, const vector<long long>& R) {
    set<long long> S = {0};
    int n = (int)L.size();
    for (int i = 0; i < n; ++i) {
        set<long long> ns;
        for (long long x : S) {
            for (long long y = L[i]; y <= R[i]; ++y) {
                ns.insert(x ^ y);
            }
        }
        S.swap(ns);
    }
    return *S.rbegin();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> L(n), R(n);
        for (auto& x : L) cin >> x;
        for (auto& x : R) cin >> x;
        cout << solveOne(L, R) << '\n';
    }
}
