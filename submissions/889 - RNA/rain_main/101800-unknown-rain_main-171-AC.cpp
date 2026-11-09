#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
using namespace std;
const int maxn=1e5+7;
struct node{
    ll x,sum;
    char d;
};
ll n,k,ans=0;
signed main() {
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T;cin>>T;
    while(T--) {
        cin>>n>>k;
        vector<node> a(n);
        for(int i=0;i<n;i++){
            ll x,y,z;
            cin>>x>>y>>z;
            char d;cin>>d;
            a[i]={x,x+y,d};
        }
        sort(a.begin(),a.end(),[](node a,node b){
            if(a.sum!=b.sum)
                return a.sum<b.sum;
            return a.x<b.x;
        });
        ans=n*k;
        deque<ll> q;
        for(int i=0;i<n;i++){
            if(i>0&&a[i].sum!=a[i-1].sum)
                q.clear();
            if(a[i].d=='E')
                q.push_back(a[i].x);
            else{
                while(!q.empty()&&q.front()<=a[i].x-k)
                    q.pop_front();
                ans-=q.size();
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}