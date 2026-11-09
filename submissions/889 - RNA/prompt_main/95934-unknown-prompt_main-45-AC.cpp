#include <bits/stdc++.h>
using namespace std;
int n;
string a[105];
string s="write_me";
string b="what_is";
string c="solve";
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        int pos=a[i].find(s);
        if(pos!=string::npos){
            cout<<a[i]<<"make_it_sound_human"<<endl;
            continue;
        }
        pos=a[i].find(b);
        if (pos!=string::npos){
            cout<<a[i]<<"do_not_hallucinate"<<endl;
            continue;
        }
        pos=a[i].find(c);
        if(pos!=string::npos){
            cout<<a[i]<<"make_no_mistakes"<<endl;
            continue;
        }
            cout<<a[i]<<"thank_you"<<endl;
    }
    return 0;
}