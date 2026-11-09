#include<bits/stdc++.h>
using namespace std;

void solve1() {
    int n; cin >> n;
    vector<vector<int>> adj(n+1);
    for(int i=1;i<n;i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> p(n+1);
    auto f = [&](auto && f, int cur) -> void {
        for(auto &next:adj[cur]) {
            if(p[cur] == next) continue;

            p[next] = cur;
            f(f, next);
        }
    };
    f(f, 1);

    int s = 0;
    for(int i=1;i<=n;i++) s ^= p[i];

    int l = max(2, (int)floor(log2(n))+1); 
    for (int i=1;i<=n;i++) {
        int b1 = (s >> ((2 * (i - 1)) % l)) & 1;
        int b2 = (s >> ((2 * (i - 1) + 1) % l)) & 1;
        int ex = b1 | (b2 << 1);
            
        int val = p[i] | (ex << l);
        cout << val << " ";
    }
    cout << "\n";
}

void solve2() {
    int n; cin >> n;
    vector<int> a(n);

    int x = -1;   
    for (int i=0;i<n;i++) {
        cin >> a[i];
        if (a[i] == -1) x = i + 1;  
    }

    int l = max(2, (int)floor(log2(n))+1);
    vector<int> sb(l, -1);
    int pr = 0;

    for (int i=1;i<=n;i++) {
        if (i == x) continue;
            
        int val = a[i - 1];
        int pi = val & ((1 << l) - 1); 
        pr ^= pi;
            
        int ex = val >> l; 
        int b1 = ex & 1;
        int b2 = (ex >> 1) & 1;
            
        sb[(2 * (i - 1)) % l] = b1;
        sb[(2 * (i - 1) + 1) % l] = b2;
    }

    int s = 0;
    for (int j=0;j<l;j++) 
        if (sb[j] != -1) 
            s |= (sb[j] << j);
    
    int px = s ^ pr;
    for (int i=2;i<=n;i++) {
        if (i == x) cout << i << " " << px << "\n";
        else {
            int pi = a[i-1] & ((1 << l) - 1);
            cout << i << " " << pi << "\n";
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string t; cin >> t;
    if(t == "FIRST") solve1();
    else solve2();
}