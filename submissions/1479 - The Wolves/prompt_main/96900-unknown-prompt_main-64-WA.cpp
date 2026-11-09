// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

void solve() {

    string s; cin>>s;
    string OGs = s;
    string phrase1="write_me";
    string phrase2="what_is";
    string phrase3="solve";

    for (int i = 0; i < s.length() - phrase1.length(); i++) {
        int res = 0;
        for (int j = 0; j < phrase1.length(); j++) {
            if (phrase1[j] == s[i + j]) res++;
        }
        if (res == phrase1.length()) s += phrase1;
    }
    if (OGs == s) {
        for (int i = 0; i < s.length() - phrase2.length(); i++) {
            int res = 0;
            for (int j = 0; j < phrase2.length(); j++) {
                if (phrase2[j] == s[i + j]) res++;
            }
            if (res == phrase2.length()) s += phrase2;
        }
    }
    if (OGs == s) {
        for (int i = 0; i < s.length() - phrase3.length(); i++) {
            int res = 0;
            for (int j = 0; j < phrase3.length(); j++) {
                if (phrase3[j] == s[i + j]) res++;
            }
            if (res == phrase3.length()) s += phrase3;
        }
    }
    if (OGs == s) {
        s += "thank_you";
    }

    cout<<s<<"\n";
}


int main() {

    // sets up the fast io


    int tc;
    cin >> tc;
    for (int i = 0; i < tc; i++) {
        solve();
    }



    return 0;
}
