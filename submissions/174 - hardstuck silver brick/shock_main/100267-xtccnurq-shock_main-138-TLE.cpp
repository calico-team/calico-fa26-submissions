#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    int t;
    cin>>t;
    while(t--){
        int n,m,q;
        cin>>n>>m>>q;

        vector<vector<ll>> grid(n,vector<ll>(m,0));
        for (int i=0;i<q;i++){
            ll r,c,p;
            cin>>r>>c>>p;

            ll r_low=max(0LL,r-p);
            ll r_high=min((long long)(n-1),r+p);
            ll c_low=max(0LL, c-p);
            ll c_high=min((long long)(m-1),c+p);

            ll p_squared=p*p;
            for(ll rr=r_low;rr<=r_high;rr++){
                ll r_diff_squared=(rr-r)*(rr-r);
                for(int cc=c_low;cc<=c_high;cc++){
                    ll c_diff_squared=(cc-c)*(cc-c);
                    ll dist_squared=r_diff_squared+c_diff_squared;

                    if(dist_squared<=p_squared)grid[rr][cc]=p_squared-dist_squared+1;
                }
            }
        }

        for(int r=0;r<n;r++){
            for(int c=0;c<m;c++){
                cout<<grid[r][c]<<" ";
            }
            cout<<endl;
        }
    }
}
