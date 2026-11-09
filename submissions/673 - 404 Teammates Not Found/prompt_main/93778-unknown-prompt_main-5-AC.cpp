#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        string a="thank_you";
        int n=s.size();
        for(int i=0;i<n;i++){
            if(s.substr(i,8)=="write_me"){
                a="make_it_sound_human";
                break;
            }
            else if(s.substr(i,7)=="what_is"){
                a="do_not_hallucinate";
                break;
            }
            else if(s.substr(i,5)=="solve"){
                a="make_no_mistakes";
                break;
            }
        }
        cout<<s<<a<<"\n";
    }
    return 0;
}
