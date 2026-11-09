#include<bits/stdc++.h>
using namespace std;
int X[100005],Y[100005];
char D[100005];
long long key[100005];
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int n;
        long long k;
        scanf("%d %lld",&n,&k);
        for(int i=0;i<n;i++){
            int z;
            scanf("%d %d %d %c",&X[i],&Y[i],&z,&D[i]);
        }
        long long ans=0;
        for(long long t=0;t<k;t++){
            for(int i=0;i<n;i++){
                long long x=X[i],y=Y[i];
                if(D[i]=='E') x+=t;
				else y+=t;
                key[i]=x*2000000001LL+y;
            }
            sort(key,key+n);
            int cnt=0;
            for(int i=0;i<n;i++){
                if(i==0||key[i]!=key[i-1]) cnt++;
            }
            ans+=cnt;
        }
        printf("%lld\n",ans);
    }
    return 0;
}