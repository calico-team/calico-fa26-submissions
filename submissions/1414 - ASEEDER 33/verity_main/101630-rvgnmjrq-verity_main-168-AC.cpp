#include<bits/stdc++.h>
using namespace std;
char c[30];
int main(){
    int t;
    cin>>t;
    while(t--){
        int node[101]={0};
        string r;
        int n,k;
        cin>>n>>k;
        for(int i=0;i<k;i++)cin>>c[i];
        string s(n,c[0]);
        while(1){
            cout<<s<<endl;
            cin>>r;
            if(r=="CORRECT")break;
            for(int i=0;i<n;i++){
                if(r[i]=='_'){
                    s[i]=c[++node[i]];
                }
            }
        }
    }
    return 0;
}