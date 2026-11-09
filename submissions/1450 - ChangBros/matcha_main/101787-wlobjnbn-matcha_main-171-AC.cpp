#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define all(x) (x).begin(), (x).end()
#define forn(var,start,end) for(int var=start;var<end;var++)
#define X first
#define Y second

void solve(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int> l(n),r(n),d(n),g(n,-1),fixed(n,-1);
        forn(i,0,n) cin>>l[i];
        forn(i,0,n) cin>>r[i];

        int cnt[30]={},par[30]={};
        int base=0,ans=0;
        forn(i,0,n){
            base^=l[i];
            d[i]=l[i]^r[i];
            forn(b,0,30){
                if((d[i]>>b)&1) g[i]=b;
            }
            if(g[i]==-1) fixed[i]=0;
            else cnt[g[i]]++;
        }

        for(int b=29;b>=0;b--){
            int ones[30]={},last[30]={};
            int cur=(base>>b)&1;
            forn(i,0,n){
                int bit=(d[i]>>b)&1;
                if(fixed[i]!=-1) cur^=fixed[i]*bit;
                else if(bit) ones[g[i]]++;
                else if(g[i]>b) last[g[i]]=i;
            }

            vector<int> mixed;
            forn(j,b+1,30){
                if(ones[j]==cnt[j]) cur^=par[j];
                else if(ones[j]>0) mixed.push_back(j);
            }
            if(cnt[b]) mixed.push_back(b);

            vector<pair<int,int>> cand;
            forn(i,0,n){
                if(g[i]<=b) continue;
                bool low=((l[i]>>b)&1)==0;
                bool high=((r[i]>>b)&1)==1;
                if(!low && !high) continue;

                if(low && high) cand.push_back({-1,0});
                else{
                    int want=low ? 0 : 1;
                    int known=fixed[i];
                    if(known==-1 && cnt[g[i]]==1) known=par[g[i]];
                    if(known!=-1){
                        if(known!=want) continue;
                        cand.push_back({-1,0});
                    }
                    else cand.push_back({i,want});
                }
                if(cand.size()==3) break;
            }

            bool done=cand.size()==3;
            if(cand.size()==2){
                int x=cand[0].X,y=cand[1].X;
                if(x==-1 || y==-1) done=true;
                else if(g[x]!=g[y] || cnt[g[x]]!=2) done=true;
                else if((cand[0].Y^cand[1].Y)==par[g[x]]) done=true;
            }

            forn(j,0,(int)cand.size()){
                int x=cand[j].X,want=cand[j].Y;
                if(mixed.empty()){
                    if(cur==0) done=true;
                }
                else if(x==-1 || mixed.size()>1) done=true;
                else if(g[x]!=mixed[0]) done=true;
                else{
                    int h=g[x];
                    if(cnt[h]-ones[h]==1){
                        if(want==(cur^par[h])) done=true;
                    }
                    else done=true;
                }
            }

            if(done){
                ans|=(1LL<<(b+1))-1;
                break;
            }

            if(mixed.empty()) ans|=cur<<b;
            else{
                ans|=1LL<<b;
                int h=mixed[0];
                if(h==b) par[h]=cur^1;
                else{
                    int x=last[h];
                    fixed[x]=cur^par[h]^1;
                    par[h]^=fixed[x];
                    cnt[h]--;
                }
            }
        }
        cout<<ans<<'\n';
        //hollllyyyy
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}