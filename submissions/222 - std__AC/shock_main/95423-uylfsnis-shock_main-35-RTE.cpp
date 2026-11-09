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
        vector<query> Q(q);
        vector<vector<pair<pii, int>>> A(n);
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
                A[i].push_back({{c-sq, c+sq}, qi+1});
            }
        }
        vvi B(n, vi(m));
        for (int i=0; i<n; ++i){
            set<int> s;
            vvi upds(m+1);
            for (auto [p, v] : A[i]){
                upds[p.first].push_back(v);
                upds[p.second+1].push_back(-v);
            }
            for (int j=0; j<m; ++j){
                for (int x : upds[j]){
                    if (x>0) s.insert(x);
                    else s.erase(-x);
                }
                B[i][j]=(s.empty() ? -1 : (*s.rbegin())-1);
            }
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