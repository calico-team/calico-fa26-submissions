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

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--){
        int n;
        cin >> n;
        vpii A(n);
        for (int i=0; i<n; ++i) cin >> A[i].first;
        for (int i=0; i<n; ++i) cin >> A[i].second;
        int ans=0;
        for (int i=29; i>=0; --i){
            int a=0;
            for (int j=0; j<n; ++j){
                if (A[j].first<(1<<i) && A[j].second>=(1<<i)) ++a;   
            }
            if (a>=2){
                ans^=(1<<(i+1))-1;
                break;
            }
            for (int j=0; j<n; ++j) ans^=(A[j].first&(1<<i));
            if (a==0){
                for (int j=0; j<n; ++j){
                    if (A[j].first&(1<<i)) A[j].first^=(1<<i);
                    if (A[j].second&(1<<i)) A[j].second^=(1<<i);
                }
                continue;
            }
            int ind=0;
            for (int j=0; j<n; ++j){
                if (A[j].first<(1<<i) && A[j].second>=(1<<i)) ind=j;
            }
            if (ans&(1<<i)) A[ind].second=(1<<i)-1;
            else A[ind].first=(1<<i);
            ans|=(1<<i);
            for (int j=0; j<n; ++j){
                if (A[j].first&(1<<i)) A[j].first^=(1<<i);
                if (A[j].second&(1<<i)) A[j].second^=(1<<i);
            }
        }
        cout << ans << endl;
    }
}