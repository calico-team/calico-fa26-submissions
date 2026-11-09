#include <bits/stdc++.h>
using namespace std;
#define int long long
#define vt vector
#define pb push_back
#define pob pop_back
#define fi first
#define se second
//#define endl '\n'
#define fast() ios::sync_with_stdio(false);cin.tie(nullptr);


signed main(){
    int tt;
    cin >> tt;
    while(tt--){
        int n , k;
        cin >> n >> k;
        vt<char> a(k);
        for(int i=0 ; i<k ; i++)
        cin >> a[i];
        string ans(n , '0');
        bool ok = false;
        for(int i=0 ; i<k ; i++){
            cout << string(n , a[i]) << endl;
            string rec;
            cin >> rec;
            if(rec == "CORRECT"){
                ok = true;
                break;
            }
            for(int i=0 ; i<n ; i++)
            if(rec[i] != '_') ans[i] = rec[i];
        }
        if(ok) continue;
        cout << ans << endl;
        string temp;
        cin >> temp;
    }
}