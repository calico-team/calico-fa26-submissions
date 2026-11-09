#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        vector<char>a(k);
        for(int i=0;i<k;i++)cin>>a[i];
        string ans(n,'_');
        for(int i=0;i<k;i++){
            string g=ans;
            for(int j=0;j<n;j++)if(ans[j]=='_')g[j]=a[i];
            cout<<g<<endl;
            string res;
            cin>>res;
            if(res=="CORRECT")break;
            for(int j=0;j<n;j++)if(res[j]!='_')ans[j]=res[j];
        }
    }
    return 0;
}