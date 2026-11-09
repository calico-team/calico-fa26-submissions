#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define all(x) x.begin(), x.end()
#define int long long

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tc=1;
    cin>>tc;
    auto solve=[&]()->void{
        int n;
        int m;
        int q;
        cin>>n>>m>>q;
        vector<string> a(n);
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        auto z=[&](int w,int e,int r)->int{
            return (w*m+e)*2+r;
        };
        auto check=[&](int w,int e,int r)->bool{
            if(a[w][e]=='.'){
                return 1;
            }
            if(r==0){
                return a[w][e]=='B';
            }
            return a[w][e]=='R';
        };
        vi s(2*n*m,-1);
        int t=0;
        int y[4]={-1,1,0,0};
        int u[4]={0,0,-1,1};
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                for(int r=0;r<2;r++){
                    if(!check(i,j,r)){
                        continue;
                    }
                    int o=z(i,j,r);
                    if(s[o]!=-1){
                        continue;
                    }
                    stack<array<int,3>> d;
                    d.push({i,j,r});
                    s[o]=t;
                    while(!d.empty()){
                        auto c=d.top();
                        d.pop();
                        int w=c[0];
                        int e=c[1];
                        int r=c[2];
                        if(a[w][e]=='.'){
                            int o=z(w,e,r^1);
                            if(s[o]==-1){
                                s[o]=t;
                                d.push({w,e,r^1});
                            }
                        }
                        for(int k=0;k<4;k++){
                            int p=w+y[k];
                            int f=e+u[k];
                            if(p<0||p>=n||f<0||f>=m){
                                continue;
                            }
                            if(!check(p,f,r)){
                                continue;
                            }
                            int o=z(p,f,r);
                            if(s[o]==-1){
                                s[o]=t;
                                d.push({p,f,r});
                            }
                        }
                    }
                    t++;
                }
            }
        }
        for(int i=0;i<q;i++){
            int c;
            int v;
            int b;
            int g;
            cin>>c>>v>>b>>g;
            int w=z(c,v,0);
            int e=z(b,g,a[b][g]=='R');
            string output="NO";
            if(s[w]==s[e]){
                output="YES";
            }
            cout<<output<<"\n";
        }
    };
    for(int i=0;i<tc;i++){
        solve();
    }
    return 0;
}