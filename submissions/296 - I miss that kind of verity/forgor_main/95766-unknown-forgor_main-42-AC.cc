#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

void first() {
    int n;
    cin >> n;
    vector<set<int>> adj(n);
    vector<int> nums(n);
    int u, v;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        u--, v--;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    function<void(int, int)> rec = [&](int i, int p) {
        if (p != -1) nums[i] = p;
        for (int j : adj[i]) {
            if (j == p) continue;
            rec(j, i);
        }
    };
    rec(0, -1);
    for (int i = 1; i < n; i++) {
        nums[0] ^= nums[i];
    }
    for (int x : nums) {
        cout << x << " ";
    }
}

void second() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int& x : nums) cin >> x;
    if (nums[0] != -1) {
        int val = 0, ind = -1;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            if (x != -1) val ^= x;
            else ind = i;
        }
        nums[ind] = val;
    }
    for (int i = 1; i < n; i++) {
        cout << nums[i] + 1 << " " << i + 1 << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    string mode;
    cin >> mode;
    if (mode == "FIRST") {
        first();
    } else {
        second();
    }
}