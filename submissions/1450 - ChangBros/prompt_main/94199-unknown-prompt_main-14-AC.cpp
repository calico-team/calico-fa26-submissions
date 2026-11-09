#include <bits/stdc++.h>
#include <ios>
using namespace std;
#define ll long long
#define int long long
#define all(x) (x).begin(), (x).end()
#define forn(var,start,end) for(int var=start;var<end;var++)
#define X first
#define Y second

void solve(){
    int t;
    cin>>t;
    while(t--){
        string str;
        cin>>str;

        if(str.find("write_me")!=-1){
            str+="make_it_sound_human";
        }
        else if(str.find("what_is")!=-1){
            str+="do_not_hallucinate";
        }
        else if(str.find("solve")!=-1){
            str+="make_no_mistakes";
        }
        else{
            str+="thank_you";
        }
        cout<<str<<endl;
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}