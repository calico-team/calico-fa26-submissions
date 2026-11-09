#include<bits/stdc++.h>
using namespace std;

int a[100005],b[100005],cnt[200005];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
	
    int t;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        for(int i=0;i<=100000;i++){
            a[i]=-1;
            b[i]=-1;
        }
        for(int i=0;i<=200000;i++){
            cnt[i]=0;
        }
        int m=0;
        for(int i=0;i<n;i++){
            int x,y,z;
            char d;
            cin>>x>>y>>z>>d;
            if(d=='N'){
                a[x]=x+y;
            }
            else{
                b[x]=x+y;
            }
            if(x>m){
                m=x;
            }
        }
        long long ans=n;
        ans=ans*k;
        int r=0;
        for(int x=0;x<=m;x++){
            while(r<=m&&r<x+k){
                if(a[r]!=-1){
                    cnt[a[r]]++;
                }
                r++;
            }
            if(a[x]!=-1){
                cnt[a[x]]--;
            }
            if(b[x]!=-1){
                ans-=cnt[b[x]];
            }
        }
        cout<<ans<<"\n";
    }
    return 0;
}
