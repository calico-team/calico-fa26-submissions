#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin>>T;
    for(int i=1;i<=T;i++){
        int n; long long r; cin>>n>>r;
        static long long a[100005];
        for(int j=0;j<n;j++) cin>>a[j];

        long long s1=-1, s2=-1; 
        bool ok=true;
        for(int j=0;j<n;j++){
            long long t=a[j];
            if(s1!=-1 && s1<=t) s1=-1; 
            if(s2!=-1 && s2<=t) s2=-1;
            if(s1==-1)      s1=(s2==-1?t:s2)+r;
            else if(s2==-1) s2=s1+r;
            else { ok=false; break; }
        }
        cout << (ok?"YES":"NO") << '\n';
    }
    return 0;
}
