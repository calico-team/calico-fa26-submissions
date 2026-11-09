#include <iostream>
using namespace std;
int main(){
    cin.sync_with_stdio(0);cin.tie(0);
    int t,n,r,a,counter,l;
    bool flag;
    cin>>t;
    while (t--){
        cin>>n>>r;
        l=0;
        counter=r*2;
        flag=1;
        while (n--){
            cin>>a;
            if (!flag) continue;
            counter=min(r*2,counter+a-l);
            l=a;
            if (counter<r){
                cout<<"NO\n";
                flag=0;
            }else{
                counter-=r;
            }
        }
        if (flag) cout<<"YES\n";
    }
}