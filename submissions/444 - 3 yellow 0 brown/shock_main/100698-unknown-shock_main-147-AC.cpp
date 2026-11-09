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
        vector<int> par(m+1);
        for (int i=0;i<m+1;i++){
            par[i]=i;
        }
        auto find = [&](int x,auto&&f)->int{
            if (par[x]!=x){
                int guh=f(par[x],f);
                par[x]=guh;
                return guh;
            }
            return x;
        };
        vector<int> col(m,-1);
        for (int j = q-1;j>=0;j--){
            int dcs = eqs[j].p*eqs[j].p-(eqs[j].r-i)*(eqs[j].r-i);
            if (dcs<0){
                continue;
            }
            int dc=sqrt(dcs);
            int l = max(0,eqs[j].c-dc);
            int r = min(m-1,eqs[j].c+dc);
            int cc = l;
            while (true){
                int fcc=find(cc,find);
                if (fcc>r){
                    break;
                }
                col[fcc]=j;
                par[fcc]=fcc+1;
                cc=fcc+1;
            }
        }
        for (int j =0;j<m;j++){
            int curcol = col[j];
            ans[i][j]=curcol;
            if (curcol==-1){
                ans[i][j]=0;
            }else{
                ans[i][j]=eqs[curcol].p*eqs[curcol].p-(eqs[curcol].r-i)*(eqs[curcol].r-i)-(eqs[curcol].c-j)*(eqs[curcol].c-j)+1;
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
