#include<bits/stdc++.h>
using namespace std;
int T;
int main(){
    scanf("%d", &T);
    while(T--){
        long long n,k;
        scanf("%d %lld",&n,&k);
        vector<int> X(n), Y(n);
        vector<char> D(n);
        for(int i=0;i<n;i++){
            int z;
            scanf("%d %d %d %c",&X[i],&Y[i],&z,&D[i]);
        }
        set<pair<int,int>> init_pos;
        for(int i=0;i<n;i++){
            init_pos.insert(make_pair(X[i],Y[i]));
        }
        long long C=init_pos.size();
        long long chonghe=0;
        for(int i=0;i<n;i++){//n
            for(int j=0;j<n;j++){  //e
                if(i==j) continue;
                if(D[i]=='E'&&D[j]=='N'){
                    if(X[i]+Y[i]==X[j]+Y[j]){
                        long long t=X[j]-X[i];
                        if(t>=0&&t<k){
                            chonghe++;
                        }
                    }
                }
            }
        }
        printf("%lld\n",C*k-chonghe);
    }
    return 0;
}