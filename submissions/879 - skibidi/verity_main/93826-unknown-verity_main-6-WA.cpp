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
        for (int i=0; i<k; i++){
            cout<<string(n,c[i])<<endl;
            string s;
            cin>>s;
            for (int j=0; j<n; j++){
                char x=s[j];
                if (x!='_') ans[j]=c[i];
            }
        }
        for (char C:ans) cout<<C;
        cout<<endl;
        string aaaaaaaa;
        cin>>aaaaaaaa;
    }
}