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

bool contains(const string& s, const string& subs) {
    return (s.find(subs)!=string::npos);
}

int32_t main() {
    fastIO();

    int t;cin>>t;
    while (t--){
        string s;cin>>s;
        if (contains(s,"write_me")){
            s.append("make_it_sound_human");
        } 
        else if (contains(s,"what_is")){
            s.append("do_not_hallucinate");
        } 
        else if (contains(s,"solve")){
            s.append("make_no_mistakes");
        }
        else {
            s.append("thank_you");
        }
        cout<<s<<endl;
    }

    return 0;
}





