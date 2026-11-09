#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
using lli=long long int;
using pii=pair<int, int>;
using plli=pair<lli, lli>;
using vlli=vector<lli>;
using vpii=vector<pii>;
using vplli=vector<plli>;
using vvi=vector<vi>;
using vvlli=vector<vlli>;
using vc=vector<char>;
using vvc=vector<vc>;
using vb=vector<bool>;
using vvb=vector<vector<bool>>;

struct query{
    int r, c, p;
};

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--){
        int n, m, q;
        cin >> n >> m >> q;
        int tm=m;
        while (tm&(tm-1)) ++tm;
        vvi tree(n, vi(2*tm, -1));
        vector<query> Q(q);
        for (int qi=0; qi<q; ++qi){
            int r, c, p;
            cin >> r >> c >> p;
            Q[qi]={r, c, p};
            assert(p<=sqrt(n*m)+2);
            for (int i=r-p; i<=r+p; ++i){
                // j+c so that j^2<=p^2-(i-r)^2
                int v=p*p-(i-r)*(i-r);
                int sq=sqrt(v);
                while (sq*sq<v) ++sq;
                while (sq*sq>v) --sq;
                // -sq<=j<=sq
                for (int l=c-sq+tm, r=c+sq+tm; l<=r; l>>=1, r>>=1){
                    if (l&1) tree[i][l]=max(tree[i][l], qi), ++l;
                    if (!(r&1)) tree[i][r]=max(tree[i][r], qi), --r;
                }
            }
        }
        vvi B(n, vi(m));
        for (int i=0; i<n; ++i){
            for (int j=2; j<2*tm; ++j) tree[i][j]=max(tree[i][j], tree[i][j>>1]);
            for (int j=0; j<m; ++j) B[i][j]=tree[i][j+tm];
        }
        for (int i=0; i<n; ++i){
            for (int j=0; j<m; ++j){
                if (B[i][j]==-1) cout << 0;
                else{
                    query v=Q[B[i][j]];
                    cout << v.p*v.p-((i-v.r)*(i-v.r)+(j-v.c)*(j-v.c))+1;
                }
                cout << (j==m-1 ? "" : " ");
            }
            cout << endl;
        }
    }
}