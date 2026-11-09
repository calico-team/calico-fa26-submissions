// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        if(s.contains("write_me")){
            s+="make_it_sound_human";
        }
        else{

        
            if(s.contains("what_is")){
                s+="do_not_hallucinate";
            }
            else{
                if(s.contains("solve")){
                    s+="make_no_mistakes";
                }
                else{
                    s+="thank_you";
                }
            }
            
        }
        cout<<s;
        if(t!=0){
            cout<<endl;
        }
    }
    }
