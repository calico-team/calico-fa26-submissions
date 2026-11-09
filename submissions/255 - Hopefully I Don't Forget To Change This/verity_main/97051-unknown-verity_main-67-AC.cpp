#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin >> t;
    while(t--){
        int n,k;
        cin >> n >> k;
        vector<char> a(k);
        for(int i=0;i<k;i++){
            cin >> a[i];
        }
        string ans = "";
        for(int i=0;i<n;i++){
            ans+=a[0];
        }
        string aans;
        cout << ans << endl;
        cin >> aans;
        cout.flush();
        int cnt=1;
        while(aans!="CORRECT"){
            for(int i=0;i<n;i++){
                if(aans[i]=='_') ans[i]=a[cnt];
            }
            cout << ans << endl;
            cin >> aans;
            cnt++;
            cout.flush();
        }
    }
}