#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
    int t;
    cin>>t;
    for (int tt=0; tt<t; tt++){
        int n,k;
        cin>>n>>k;
        char c[k];
        char ans[n];
        for (int i=0; i<k; i++) cin>>c[i];
        bool byeeee=false;
        for (int i=0; i<k; i++){
            cout<<string(n,c[i])<<endl;
            string s;
            cin>>s;
            if (s=="CORRECT"){
                byeeee=true;
                break;
            }
            for (int j=0; j<n; j++){
                char x=s[j];
                if (x!='_') ans[j]=c[i];
            }
        }
        if (byeeee) continue;
        for (char C:ans) cout<<C;
        cout<<endl;
        string aaaaaaaa;
        cin>>aaaaaaaa;
    }
}