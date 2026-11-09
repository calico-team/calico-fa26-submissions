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
    for (int i =0;i<n;i++){
        vector<vector<int>> ents(m);
        vector<vector<int>> exs(m);
        for (int j = 0;j<q;j++){
            int dcs = eqs[j].p*eqs[j].p-(eqs[j].r-i)*(eqs[j].r-i);
            if (dcs<0){
                continue;
            }
            int dc=sqrt(eqs[j].p*eqs[j].p-(eqs[j].r-i)*(eqs[j].r-i));
            ents[max(0,eqs[j].c-dc)].push_back(j);
            exs[min(m-1,eqs[j].c+dc)].push_back(j);
        }
        set<int> cur;
        for (int j =0;j<m;j++){
            for (int ent : ents[j]){
                cur.insert(ent);
            }

            if (cur.size()>0){
                int c = *cur.rbegin();
                ans[i][j]=eqs[c].p*eqs[c].p-(eqs[c].r-i)*(eqs[c].r-i)-(eqs[c].c-j)*(eqs[c].c-j)+1;
                assert(ans[i][j]>0);
            }

            for (int ex : exs[j]){
                cur.erase(ex);
            }
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
