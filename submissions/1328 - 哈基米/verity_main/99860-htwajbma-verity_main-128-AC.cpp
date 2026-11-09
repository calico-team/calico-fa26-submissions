#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        char a[k+105];
        for(int i=0;i<k;i++)cin>>a[i];
        string ans(n,'_');
        for(int i=0;i<k;i++){
        	char c=a[i];
            string g=ans;
            for(int i=0;i<n;i++){
                if(ans[i]=='_')g[i]=c;
            }
            cout<<g<<endl;
            string mj;cin>>mj;
            if(mj=="CORRECT")break; 
            for(int i=0;i<n;i++) 
                if(mj[i]!='_') 
					ans[i]=mj[i];
        }
    }
    return 0;
}
