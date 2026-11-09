// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;


int main() {
	int c; cin >> c;
    for (int x = 0; x <c; x++){
        string ai; cin >> ai;
        string final = ai;
        if (ai.find("write_me") != string::npos) { 
            final += "make_it_sound_human";     
    }
        else if(ai.find("what_is") != string::npos){
            final += "do_not_hallucinate";
        }
        else if (ai.find("solve") != string::npos){
            final += "make_no_mistakes";
        }
        else{
            final += "thank_you";
        }
    cout << final << "\n";
}
}
