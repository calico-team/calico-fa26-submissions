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

vector<int> ops[(int)1e6+5];
// vector<int> gd[(int)1e3+5];
pipii pt[(int)2e4+5];

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    int rv=0;
    // if (n>m) {
    //     swap(n,m);
    //     rv=1;
    // }
    // vector<pipii> pt(q);
    for (int i = 0; i < q; i++) {
        cin >> pt[i].second.first >> pt[i].second.second >> pt[i].first;
        if (rv) {
            swap(pt[i].second.first,pt[i].second.second);
        }
    }
    auto ds = [&](int x, int y, int j) {
        int p = pt[j].first;
        int r = pt[j].second.first;
        int c = pt[j].second.second;
        int ret = p*p-(x-r)*(x-r)-(y-c)*(y-c)+1;
        // assert(ret > 0);
        return ret;
    };
    // assert(n<=m);
    // assert(n<=1e3);
    priority_queue<int> ms,er;
    // vector<vector<int> > gd(n, vector<int>(m, 0));
    if (n<=m) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < q; j++) {
                int p = pt[j].first;
                int r = pt[j].second.first;
                int c = pt[j].second.second;
                int lf = p*p-(r-i)*(r-i);
                if (lf>=0) {
                    int df = (int)sqrt(lf);
                    ops[max(0, c-df)].pb(j+1);
                    int rp = min(m-1, c+df);
                    if(rp+1<m) {
                        ops[rp+1].pb(-(j+1));
                    }
                }
            }
            // int ps = 0;
            while (sz(ms)) {
                ms.pop();
            }
            while (sz(er)) {
                er.pop();
            }
            for (int j = 0; j < m; j++) {
                for (auto ps : ops[j]) {
                    if(ps<0) {
                        er.push(-ps);
                    }
                }
                for (auto ps : ops[j]) {
                    if(ps>0) {
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
                    cout << 0 << " ";
                } else {
                    cout << ds(i, j, id-1) << " ";
                }
            }
            cout << endl;
        }
    } else {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < q; j++) {
                int p = pt[j].first;
                int r = pt[j].second.first;
                int c = pt[j].second.second;
                int lf = p*p-(c-i)*(c-i);
                if (lf>=0) {
                    int df = (int)sqrt(lf);
                    ops[max(0, r-df)].pb(j+1);
                    int rp = min(n-1, r+df);
                    if(rp+1<n) {
                        ops[rp+1].pb(-(j+1));
                    }
                }
            }
            // int ps = 0;
            while (sz(ms)) {
                ms.pop();
            }
            while (sz(er)) {
                er.pop();
            }
            for (int j = 0; j < n; j++) {
                for (auto ps : ops[j]) {
                    if(ps<0) {
                        er.push(-ps);
                    }
                }
                for (auto ps : ops[j]) {
                    if(ps>0) {
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
                    cout << 0 << " ";
                } else {
                    cout << ds(j, i, id-1) << " ";
                }
            }
            cout << endl;
        }
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