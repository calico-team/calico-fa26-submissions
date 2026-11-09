// #pragma GCC optimize("Ofast,unroll-loops")
#include <algorithm>
#include <bits/stdc++.h>
 
using namespace std;
using namespace std::chrono;
#define endl "\n"
#define fastinput ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back
#define pii pair<int,int>
#define pipii pair<int, pii>
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

// #define int ll
#define endl "\n"
#define fastinput ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<int> ops[1000005];
vector<int> gd[1005];
pair<int, pair<int, int> > pt[20005];

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    int rv = 0;
    if (n > m) {
        swap(n, m);
        rv = 1;
    }

    for (int i = 0; i < q; i++) {
        cin >> pt[i].second.first >> pt[i].second.second >> pt[i].first;
        if (rv) {
            swap(pt[i].second.first, pt[i].second.second);
        }
    }
    auto ds = [&](int x, int y, int j) {
        int p = pt[j].first;
        int r = pt[j].second.first;
        int c = pt[j].second.second;
        int ret = p*p-(x-r)*(x-r)-(y-c)*(y-c)+1;
        return ret;
    };

    
    for (int i = 0; i < n; i++) {
        gd[i] = vector<int> (m, 0);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < q; j++) {
            int p = pt[j].first;
            int r = pt[j].second.first;
            int c = pt[j].second.second;
            int lf = p*p-(r-i)*(r-i);
            if (lf >= 0) {
                int df = (int)sqrt(lf);
                ops[max(0, c - df)].push_back(j + 1);
                int rp = min(m - 1, c + df);
                if(rp + 1 < m) {
                    ops[rp + 1].push_back(-(j+1));
                }
            }
        }
        priority_queue<int> ms, er;
        for (int j = 0; j < m; j++) {
            for (auto ps : ops[j]) {
                if(ps < 0) {
                    er.push(-ps);
                }
            }
            for (auto ps : ops[j]) {
                if(ps > 0) {
                    ms.push(ps);
                }
            }
            while (sz(er)&&sz(ms)&&er.top()==ms.top()) {
                er.pop();
                ms.pop();
            }
            ops[j].clear();
            int id = (sz(ms)?ms.top():0);
            if (!id) {
                gd[i][j] = 0;
            } else {
                gd[i][j] = ds(i, j, id-1);
            }
        }
    }
    if (rv) {
        swap(n, m);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << (rv?gd[j][i]:gd[i][j]) << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < n; i++) {
        gd[i].clear();
    }
}

signed main() {
    fastinput;
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}