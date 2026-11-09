// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
    cin >> t;
    while (t--){
        string s;
        cin >> s;
        int n = 0;
        if (s.find("write_me") != -1){
            s += "make_it_sound_human";
            n++;
        }
        if (s.find("what_is") != -1){
            s += "do_not_hallucinate";
            n++;
        }
        if (s.find("solve") != -1){
            s += "make_no_mistakes";
            n++;
        }
        if (n==0){
            s += "thank_you";
        }
        cout << s << endl;
    }
}
