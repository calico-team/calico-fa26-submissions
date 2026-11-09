//srirama
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);
    int T;
    cin >> T;
    while(T--){
        int n, m, q;
        cin>>n>>m>>q;
        vector<ll> rr(q), cc(q), pp(q);
        for(int i=0;i<q;i++) cin>>rr[i]>>cc[i]>>pp[i];

        vector<int> grid(n* m);
        vector<set<int>> s(n);
        for (int i=0;i<n;i++)
            for(int j=0;j<m;++j) s[i].insert(j);

        for(int i=q-1;i>=0;i--){
            ll p = pp[i];
            for(ll d=-p;d<=p;d++){
                int row=rr[i]+d;
                if(s[row].size()==0) continue;
                ll tmp=p*p-d*d;
                ll w = sqrt(tmp);
                while(w*w>tmp)w--;
                while((w+1)*(w+1)<=tmp)w++;   
                int a=cc[i]-w, b= cc[i]+w;
                auto it = s[row].lower_bound(a);
                while(it!=s[row].end() && *it<=b){
                    ll x=*it-cc[i];
                    grid [row*m + *it]= p*p-d*d-x*x+1;
                    it=s [row].erase(it);
                }
            }
        }

        string res;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(j)res+=' ';
                res+=to_string(grid[i*m+j]);
            
            
            
            }
            res += '\n';
        }
        cout<<res;
    }
}