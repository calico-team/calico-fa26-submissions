// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
	int t = 0;
    cin >>t;
    for(int a = 0;a<t;a++){

        string w;
        cin>>w;
        if(w.contains("write_me")){
            w += "make_it_sound_human";
        } else if(w.contains("what_is")){
            w += "do_not_hallucinate";
        }else if(w.contains("solve")){
            w += "make_no_mistakes";
        }else{
            w += "thank_you";
        }
        cout<<w<<"\n";
    }
}
