#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"
using namespace std;
#define fast ios_base::sync_with_stdio(0) , cin.tie(0)
using ll=long long;

struct EQ{
    int r;
    int c;
    int p;
};

void solve() {
    int n,m,q;
    cin >> n >> m >> q;

    vector<EQ> eqs(q);
    for (int i=0;i<q;i++){
        cin >> eqs[i].r >> eqs[i].c >> eqs[i].p;
    }

    bool swp=false;
    if (n>m){
        swp=true;
        swap(n,m);
        for (int i=0;i<q;i++){
            swap(eqs[i].r,eqs[i].c);
        }
    }

    vector<vector<int>> ans(n,vector<int>(m,0));
    vector<vector<pair<int,int>>> ents(m);
    for (int i =0;i<n;i++){
        for (int j = 0;j<q;j++){
            int dcs = eqs[j].p*eqs[j].p-(eqs[j].r-i)*(eqs[j].r-i);
            if (dcs<0){
                continue;
            }
            int dc=sqrt(dcs);
            ents[max(0,eqs[j].c-dc)].push_back({j,min(m-1,eqs[j].c+dc)});
        }
        priority_queue<pair<int,int>> cur;
        for (int j =0;j<m;j++){
            for (pair<int,int>& ent : ents[j]){
                cur.push(ent);
            }
            while (cur.size()>0&&j>cur.top().second){
                cur.pop();
            }

            if (cur.size()>0){
                int c = cur.top().first;
                ans[i][j]=eqs[c].p*eqs[c].p-(eqs[c].r-i)*(eqs[c].r-i)-(eqs[c].c-j)*(eqs[c].c-j)+1;
            }
        }
        for (int j =0;j<m;j++){
            ents[j].clear();
        }
    }
    if (swp){
        for (int j=0;j<m;j++){
            for (int i=0;i<n;i++){
                cout << ans[i][j] << " ";
            }
            cout << '\n';
        }
    }else{
        for (int i=0;i<n;i++){
            for (int j=0;j<m;j++){
                cout << ans[i][j] << " ";
            }
            cout << '\n';
        }
    }
}

signed main() {
    fast;
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
