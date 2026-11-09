#include <bits/stdc++.h>
using namespace std;



void solve(){
    int n;
    cin >> n;
    vector<int> l(n),r(n);
    for(int i=0;i<n;i++) cin >> l[i];
    for(int i=0;i<n;i++) cin >> r[i];
    vector<vector<int>> split(30);
    int u=0;
    for(int i=0;i<n;i++){
        u^=l[i];
        if(l[i]!=r[i]) split[31-__builtin_clz(l[i]^r[i])].push_back(i);
    }
    vector<int> rail(n,-1),grp(n,-1);
    vector<int> gt,gf,gr;
    vector<vector<int>> gm;
    vector<int> cnt,wr,orl,t;
    int lp=0;
    long long out=0;
    for(int i=29;i>=0;i--){
        for(int o:split[i]) u^=l[o];
        int p=(u>>i)%2;
        int q=p^lp;
        int s=0,tc=0,lc=-1;
        t=vector<int>();
        for(int o:orl){
            int lb=(l[o]>>i)%2;
            int rb=(r[o]>>i)%2;
            if(lb==1 and rb==0) continue;
            if(lb==0 and rb==1){
                s++;
                continue;
            }
            if(rail[o]!=-1){
                if(rail[o]==lb) s++;
                continue;
            }
            if(cnt[grp[o]]==0) t.push_back(grp[o]);
            cnt[grp[o]]++;
            wr[grp[o]]+=lb;
            lc=o;
        }
        int mj=s;
        tc=s;
        for(int o:t){
            tc+=cnt[o];
            if(cnt[o]<gf[o]) mj+=cnt[o];
            else{
                mj+=cnt[o];
                if((wr[o]+gr[o])%2!=gt[o]) mj--;
            }
            cnt[o]=0;
            wr[o]=0;
        }
        if(mj>=2 or (mj>=1 and (split[i].size()>=1 or q>0))){
            out|=(1LL<<(i+1))-1;
            break;
        }
        if(split[i].size()>=1){
            out|=1LL<<i;
            int gts=gt.size();
            gt.push_back(1^p^lp);
            gf.push_back(split[i].size());
            gr.push_back(0);
            gm.push_back(split[i]);
            cnt.push_back(0);
            wr.push_back(0);
            for(int o:split[i]){
                grp[o]=gts;
                orl.push_back(o);
            }
            if(split[i].size()==1){
                rail[split[i][0]]=gt[gts];
                gf[gts]=0;
                gr[gts]=gt[gts];
            }
            lp=(split[i].size()+1+p)%2;
        }
        else if(q>0){
            out|=1LL<<i;
        }
        else if(mj==1){
            out|=1LL<<i;
            if(tc==1 and s==0){
                int o=lc;
                int g=grp[o];
                rail[o]=(l[o]>>i)%2;
                gf[g]--;
                gr[g]^=rail[o];
                if(gf[g]==1){
                    for(int p:gm[g]) if(rail[p]==-1){
                        rail[p]=gt[g]^gr[g];
                        gr[g]^=rail[p];
                        gf[g]=0;
                        break;
                    }
                }
            }
        }
    }
    cout << out << '\n';
}


int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tc=1;
  cin >> tc;
  for (int t=1;t<=tc;t++){
    solve();
  }
}