#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct drone{
    ll x,y,z;
    char d;
};

ll calc(vector<drone> a, ll k,bool same){
 auto key = [&](const drone &p) {
        return make_pair(p.x+p.y,same ? p.z : 0LL);
    };
    sort(a.begin(),a.end(),[&](const drone &p,const drone &q) {
        if(key(p)!=key(q)) return key(p)<key(q);
        return p.x<q.x;
    });

 ll ans=0;
 int n=a.size();
    for(int l=0; l<n; ) {
        int r=l;
        while(r<n && key(a[l])==key(a[r])) r++;
        vector<ll> e;
        for(int i=l;i<r;++i)
          if(a[i].d=='E') e.push_back(a[i].x);
        for(int i=l;i<r;i++) {
            if(a[i].d!='N') continue;
            ll x=a[i].x;
            auto hi=lower_bound(e.begin(), e.end(),x);
            auto lo=lower_bound(e.begin(),e.end(),x-k+1);
            ans+=hi-lo;
        }
        l=r;
    }
 return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 int t;
 cin>>t;
 while(t--){
        int n;
        ll k;
        cin>>n>>k;
        vector<drone> a(n);
        for(auto &p:a){
          cin>>p.x>>p.y>>p.z>>p.d;
        }

        ll bad=calc(a,k,false)-calc(a,k,true);
        cout<<1LL*n*k-bad<<'\n';
 }
 return 0;
}
