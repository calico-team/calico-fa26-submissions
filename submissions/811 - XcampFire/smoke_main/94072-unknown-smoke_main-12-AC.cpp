#include<iostream>
#include<vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin>>T;
    while(T--){
        int n,r;
        cin>>n>>r;
        vector<int>a(n);
        for(int i=0;i<n;i++)cin>>a[i];
        int c=2,cd=0,j=0;
        bool ok=true;
        for(int s=1;s<=a[n-1]&&ok;s++){
            if(c<2){
                cd--;
                if(cd==0){
                    c++;
                    if(c<2)cd=r;
                }
            }
            if(j<n&&a[j]==s){
                if(c==0)ok=false;
                else{
                    c--;
                    if(c==1)cd=r;
                }
                j++;
            }
        }
        cout<<(ok?"YES":"NO")<<"\n";
    }
    return 0;
}