#include <iostream>
#include <vector>
#include <unordered_map>
#define int long long
using namespace std;

void solve() {
    int n, m, k, count = 0;
    cin >> n >> m >> k;
    vector<int> a(n);
    unordered_map<int, int> index;
    unordered_map<int, int> freq;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        freq[a[i]]++;
        index[a[i]] = i;
    }
    int curr_class = 0;
    for (int i = 0; i < m; i++) {
        count += min(k, freq[curr_class]);
        auto it = index.find(index[curr_class] + 1);
        if (it == freq.end()) break;
        curr_class = index[curr_class] + 1;
    }
    cout << count << endl;
}

signed main() {
	int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
