#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int top(ll x){return 63-__builtin_clzll(x);}
ll comb(ll x,ll y){
    if(x==0)return y;
    if(y==0)return x;
    int tx=top(x),ty=top(y);
    if(tx==ty)return (2LL<<tx)-1;
    if(tx<ty){swap(x,y);swap(tx,ty);}
    return (1LL<<tx)+comb(x-(1LL<<tx),y);
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        vector<ll>L(n),R(n);
        for(auto&x:L)cin>>x;
        for(auto&x:R)cin>>x;
        ll X0=0;
        vector<vector<pair<ll,ll>>>g(30);
        for(int i=0;i<n;i++){
            if(L[i]==R[i]){X0^=L[i];continue;}
            int h=top(L[i]^R[i]);
            ll M=(R[i]>>h)<<h;
            X0^=M-1;
            g[h].push_back({M-1-L[i],R[i]-M});
        }
        vector<array<pair<int,ll>,2>>opt(30);
        for(int h=0;h<30;h++){
            auto&el=g[h];
            int k=el.size();
            if(!k)continue;
            vector<ll>mx(k),mn(k),pre(k+1,0),suf(k+1,0);
            int par=0;
            for(int i=0;i<k;i++){
                mx[i]=max(el[i].first,el[i].second);
                mn[i]=min(el[i].first,el[i].second);
                if(el[i].second>el[i].first)par^=1;
            }
            for(int i=0;i<k;i++)pre[i+1]=comb(pre[i],mx[i]);
            for(int i=k-1;i>=0;i--)suf[i]=comb(suf[i+1],mx[i]);
            ll down=-1;
            for(int i=0;i<k;i++)down=max(down,comb(comb(pre[i],suf[i+1]),mn[i]));
            opt[h][0]={par,pre[k]};
            opt[h][1]={par^1,down};
        }
        vector<pair<ll,int>>st={{0,0}};
        ll partial=0,best=-1;
        for(int b=29;b>=0;b--){
            if(!g[b].empty()){
                vector<pair<ll,int>>ns;
                for(auto&s:st)for(int t=0;t<2;t++)
                    ns.push_back({comb(s.first,opt[b][t].second),s.second^opt[b][t].first});
                sort(ns.begin(),ns.end());
                ns.erase(unique(ns.begin(),ns.end()),ns.end());
                st=ns;
            }
            vector<pair<ll,int>>one,zero;
            for(auto&s:st){
                int w=((X0>>b)&1)^s.second;
                if((s.first>>b)&1){
                    best=max(best,partial|((ll)w<<b)|((1LL<<b)-1));
                    (w^1?one:zero).push_back(s);
                }else (w?one:zero).push_back(s);
            }
            if(!one.empty()){partial|=1LL<<b;st=one;}
            else st=zero;
        }
        cout<<max(best,partial)<<"\n";
    }
}