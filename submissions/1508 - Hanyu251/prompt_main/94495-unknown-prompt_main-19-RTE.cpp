#include<bits/stdc++.h>
using namespace std;

void solve(){
    string s;cin>>s;
    int n=s.size();
    bool changed=0;
    auto edit=[&](string in,string out){
        // printf("edit %s, %s\n",in.c_str(),out.c_str());
        for(int i=0;i<n-in.size();++i){
                // printf("compare %s\n",s.substr(i,in.size()).c_str());
            if(s.substr(i,in.size())==in){
                changed=1;
                s.append(out);
                // printf("yes\n");
                return;
            }
        }
    };
    edit("what_is","do_not_hallucinate");
    edit("write_me","make_it_sound_human");
    edit("solve","make_no_mistakes");
    if(!changed){
        s.append("thank_you");
    }
    cout<<s<<endl;
}
int main(){
    int t;cin>>t;while(t--){
        solve();
    }
}
