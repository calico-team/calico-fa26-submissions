#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
using namespace std;
const int maxn=1e5+7;
int n,k,ans=0;
signed main() {
    int T;cin>>T;
    while(T--) {
        cin>>n>>k;
        vector<char> a(k);
        for(int i=0;i<k;i++) cin>>a[i];
        string op="";
        for(int i=0;i<n;i++) op+='_';
        int index=0;
        string s="";
        for(int i=0;i<n;i++) s+=" ";
        do{
            for(int i=0;i<n;i++)
                if(op[i]=='_')
                    s[i]=a[index];
            index++;
            cout<<s<<endl;
            cin>>op;
        }while(op!="CORRECT");
    }
    return 0;
}