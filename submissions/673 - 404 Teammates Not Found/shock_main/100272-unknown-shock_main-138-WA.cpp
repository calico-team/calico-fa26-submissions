#include<bits/stdc++.h>
using namespace std;

int m;
int a[1000005],f[1000005];
int r[20005],c[20005],p[20005];
int get(int x){
    while(f[x]!=x){
        f[x]=f[f[x]];
        x=f[x];
    }
    return x;
}
void upd(int x,int y,int w,int num){
    int s=x*m+y;
    if(a[s-w]>0&&a[s+w]>0){
        return;
    }
    int i=get(s-w);
    while(i<=s+w){
        int d=i-s;
        a[i]=num-d*d;
        f[i]=get(i+1);
        i=f[i];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin>>t;
    while(t--){
        int n,q;
        cin>>n>>m>>q;
        for(int i=0;i<q;i++){
            cin>>r[i]>>c[i]>>p[i];
        }
        for(int i=0;i<=n*m;i++){
            a[i]=0;
            f[i]=i;
        }

        for(int i=q-1;i>=0;i--){
            int w=p[i];
            int s=p[i]*p[i];
            for(int d=0;d<=p[i];d++){
                while(d*d+w*w>s){
                    w--;
                }
                int num=s-d*d+1;
                upd(r[i]-d,c[i],w,num);
                if(d!=0){
                    upd(r[i]+d,c[i],w,num);
                }
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(j>0){
                    cout<<" ";
                }
                cout<<a[i*m+j];
            }
            cout<<"\n";
        }
    }
    return 0;
}
