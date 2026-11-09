#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin>>T;
    while(T--){
        int N,M,Q; cin>>N>>M>>Q;
        vector<array<int,3>> e(Q);
        for(auto&x:e) cin>>x[0]>>x[1]>>x[2];
        int W=M+1;
        vector<int> nx((size_t)N*W),a((size_t)N*M,0);
        for(size_t i=0;i<nx.size();i++) nx[i]=i;
        auto fnd=[&](int x){
            int r=x;
            while(nx[r]!=r) r=nx[r];
            while(nx[x]!=r){int t=nx[x];nx[x]=r;x=t;}
            return r;
        };
        for(int q=Q-1;q>=0;q--){
            int R=e[q][0],C=e[q][1],P=e[q][2];
            for(int r=R-P;r<=R+P;r++){
                int dr=r-R;
                ll rem=(ll)P*P-(ll)dr*dr;
                int w=(int)sqrtl((long double)rem);
                while((ll)w*w>rem) w--;
                while((ll)(w+1)*(w+1)<=rem) w++;
                int lo=C-w,hi=C+w;
                int base=r*W;
                int c=fnd(base+lo)-base;
                while(c<=hi){
                    ll dc=c-C;
                    a[(size_t)r*M+c]=(int)((ll)P*P-(ll)dr*dr-dc*dc+1);
                    nx[base+c]=base+c+1;
                    c=fnd(base+c+1)-base;
                }
            }
        }
        string out;
        for(int r=0;r<N;r++){
            for(int c=0;c<M;c++){
                out+=to_string(a[(size_t)r*M+c]);
                out+=c+1<M?' ':'\n';
            }
        }
        cout<<out;
    }
}