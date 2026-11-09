#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
    int t;
    cin>>t;
    for (int tt=0; tt<t; tt++){
        int n,k;
        cin>>n>>k;
        int ans=n*k;
        vector<int> v[200001][2];
        for (int i=0; i<n; i++){
            int x,y,z;
            char d;
            cin>>x>>y>>z>>d;
            if (d=='N'){
                v[x+y][0].push_back(x);
            } else {
                v[x+y][1].push_back(x);
            }
        }
        for (int i=0; i<=200000; i++){
            if (v[i][0].size()==0 || v[i][1].size()==0) continue;
            sort(v[i][0].begin(),v[i][0].end());
            sort(v[i][1].begin(),v[i][1].end());
            int l=0, r=0;
            for (int j:v[i][0]){
                while (l<v[i][1].size() && v[i][1][l]<=j-k) l++;
                if (l==v[i][1].size()) break;
                while (r<v[i][1].size() && v[i][1][l]<=j) r++;
                ans-=r-l;
            }
        }
        cout<<ans<<endl;
    }
}