#include<bits/stdc++.h>
using namespace std;
string s;
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s;
        int ans1=s.find("write_me");
        int ans2=s.find("what_is");
        int ans3=s.find("solve");
        if(ans1!=-1)cout<<s<<"make_it_sound_human"<<endl;
        else if(ans2!=-1)cout<<s<<"do_not_hallucinate"<<endl;
        else if(ans3!=-1)cout<<s<<"make_no_mistakes"<<endl;
        else cout<<s<<"thank_you"<<endl;
    }
    return 0;
}