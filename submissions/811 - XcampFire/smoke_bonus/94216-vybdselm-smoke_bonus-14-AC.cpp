#include<iostream>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin>>T;
    while(T--){
        int n;
        long long r;
        cin>>n>>r;
        int c=2;
        long long t=0;
        bool ok=true;
        for(int i=0;i<n;i++){
            long long a;
            cin>>a;
            if(!ok)continue;
            while(c<2&&t<=a){
                c++;
                if(c<2)t+=r;
            }
            if(c==0){
                ok=false;
                continue;
            }
            c--;
            if(c==1)t=a+r;
        }
        cout<<(ok?"YES":"NO")<<"\n";
    }
    return 0;
}