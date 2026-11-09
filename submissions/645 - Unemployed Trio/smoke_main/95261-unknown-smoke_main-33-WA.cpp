/*
  ╔══════════════════════════════════════════════════════╗
  ║ ██████╗  █████╗ ██╗   ██╗██╗   ██╗ █████╗ ███╗   ██╗ ║
  ║ ██╔══██╗██╔══██╗╚██╗ ██╔╝╚██╗ ██╔╝██╔══██╗████╗  ██║ ║
  ║ ██████╔╝███████║ ╚████╔╝  ╚████╔╝ ███████║██╔██╗ ██║ ║
  ║ ██╔══██╗██╔══██║  ╚██╔╝    ╚██╔╝  ██╔══██║██║╚██╗██║ ║
  ║ ██║  ██║██║  ██║   ██║      ██║   ██║  ██║██║ ╚████║ ║
  ║ ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝ ║
  ╚══════════════════════════════════════════════════════╝
*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long; const ll INF = 1e18;
#define all(x) x.begin(),x.end()
#define int long long 
#define pb push_back
#define endl "\n"
void fastIO() {ios::sync_with_stdio(false);cin.tie(NULL);}

template<typename A, typename B>
ostream& operator<<(ostream& os, const pair<A, B>& p) {
    return os<<"("<<p.first<<", "<<p.second<<")";
}
 
template<typename T>
void print(const vector<T>& v) {
    for (const T& x:v)cout<<x<<" ";cout<<"\n";
}

int32_t main() {
    fastIO();

    int t;cin>>t;
    while (t--){
        int n;cin>>n;
        int r;cin>>r;
        vector<int> a(n);
        for (int i=0;i<n;i++){
            cin>>a[i];
        }
        int ref1=0;
        int ref2=0;
        bool res=true;
        for (int i=0;i<n;i++){

            if (ref1!=0 and ref2==0){
                ref1=max(0LL,ref1-(a[i]-a[i-1]));
            } else if (ref2!=0 and ref1==0){
                ref2=max(0LL,ref2-(a[i]-a[i-1]));
            } else if (ref1!=0 and ref2!=0){
                if (ref1<=a[i]-a[i-1] and ref2>a[i]-a[i-1]){
                    ref1=max(0LL,ref1-(a[i]-a[i-1]));
                } else if (ref1>a[i]-a[i-1] and ref2<=a[i]-a[i-1]){
                    ref2=max(0LL,ref2-(a[i]-a[i-1]));
                } else{
                    if (ref1>ref2)swap(ref1,ref2);
                    ref2=max(0LL,ref2-(a[i]-a[i-1]));
                }
            }


            if (ref1 and ref2){
                res=false;break;
            }

            if (!ref1){
                ref1=r;
            } else if (!ref2){
                ref2=r;
            }
        }
        if (res){
            cout<<"YES";
        } else{
            cout<<"NO";
        }
        cout<<endl;
    }

    return 0;
}





