#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin>>t;
    while(t--){
        int n,r;
        cin>>n>>r;
        int cnt=2,x=0;
        bool ok=true;
        for(int i=0;i<n;i++){
            int a;
            cin>>a;
            if(!ok){ 
				continue;
			}
            while(cnt<2&&x<=a){
                cnt++;
                x+=r;
            }
            if(cnt==0){
                ok=false;
                continue;
            }
            if(cnt==2){
				x=a+r;
			}
            cnt--;
        }
        if(ok) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
