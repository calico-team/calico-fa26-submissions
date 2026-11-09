// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
    string S;
    cin >> T;
	while (T--){
        bool notFound = true;
        cin >> S;
        //cout << "s: " << S << endl;
        for(int i = 0; i<S.length(); i++){
            if(S[i] == ('w')){
                if(S.substr(i, 8) == "write_me"){
                    cout << S << "make_it_sound_human" << endl;
                    notFound = false;
                    break;
                }
                else if(S.substr(i, 7) == "what_is"){
                    cout << S << "do_not_hallucinate" << endl;
                    notFound = false;
                    break;
                }
            }
            else if( S[i]=='s'){
                if(S.substr(i, 5) == "solve"){
                    cout << S << "make_no_mistakes" << endl;
                    notFound = false;
                    break;
                }
            }
        }
        if (notFound){
            cout << S << "thank_you" << endl;
        }
    }
}
