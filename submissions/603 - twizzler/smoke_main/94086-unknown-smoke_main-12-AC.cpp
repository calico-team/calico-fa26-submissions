#include <iostream>
using namespace std;
#define ll long long
#define nl "\n"

void solve(){
    ll r, n;
    cin>>n>>r;
    int ch=2;
    long long nx=0;
    bool ok=true;
    for(int i=0; i<n; i++){
        ll a;
        cin>>a;
        if(!ok){
            continue;
        }
        while(ch<2 && nx<=a){
            ch++;
            if (ch<2){
                nx+=r;
            }
        }
        if(ch==0){
            ok=false;
            continue;
        }
        if(ch==2){
            nx=a+r;
        }
        ch--;
    }
    cout<<(ok ? "YES" : "NO")<<"\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
