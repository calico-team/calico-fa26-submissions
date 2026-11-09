#include<bits/stdc++.h>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        vector<char> a(k);
        for(int i=0;i<k;i++){
            cin>>a[i];
        }
        string s(n,'_');
        for(int i=0;i<k;i++){
            for(int j=0;j<n;j++){
                if(s[j]=='_'){
                    s[j]=a[i];
                }
            }
            cout<<s<<endl;
            cin>>s;
            if(cin.fail()){
                return 0;
            }
            if(s=="CORRECT"){
                break;
            }
        }
    }
    return 0;
}
