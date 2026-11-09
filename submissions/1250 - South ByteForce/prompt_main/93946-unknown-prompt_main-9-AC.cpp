// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;cin>> T;
    while (T--) {
        string S;cin >> S;
        if (S.find("write_me") != -1) {S += "make_it_sound_human";}
        else if (S.find("what_is") != -1) {S += "do_not_hallucinate";}
        else if (S.find("solve") != -1) {S += "make_no_mistakes";}
        else {S += "thank_you";}
        cout<<S << '\n';
    }
}