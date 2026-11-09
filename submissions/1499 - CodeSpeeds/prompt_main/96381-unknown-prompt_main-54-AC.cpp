#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define all(x) x.begin(), x.end()
#define int long long

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tc=1;
    cin>>tc;
    auto solve=[&]()->void{
        string s;
        cin>>s;
        string output=s;
        if(s.find("write_me")!=string::npos){
            output+="make_it_sound_human";
        }else if(s.find("what_is")!=string::npos){
            output+="do_not_hallucinate";
        }
        else if(s.find("solve")!=string::npos){
            output+="make_no_mistakes";
        }else{
            output+="thank_you";
        }
        cout<<output<<"\n";
    };
    for(int i=0;i<tc;i++){
        solve();
    }
    return 0;
}