#include <bits/stdc++.h>
using namespace std;

int main() {
	int t = 0;
    cin >>t;
    for(int a = 0;a<t;a++){

        string w = "";
        cin>>w;
        if(w.find("write_me") != string::npos){
            w += "make_it_sound_human";
        } else if(w.find("what_is") != string::npos){
            w += "do_not_hallucinate";
        }else if(w.find("solve") != string::npos){
            w += "make_no_mistakes";
        }else{
            w += "thank_you";
        }
        cout<<w<<"\n";
    }
}
