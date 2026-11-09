// Shortcuts:
// Ctrl+Shift+B  -> Build & Run
// Ctrl+Shift+R  -> Reset Workspace (new problem)
// Ctrl+Alt+L    -> 3-pane layout (main.cpp | input.txt | output.txt)

#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
    string s;
    cin>>s;

    if(s.find("write_me") != string::npos){   // !=npos ka mean ha k hme apna target mil gya ha.
        s+= "make_it_sound_human";
    }
    else if(s.find("what_is") != string::npos){
        s+= "do_not_hallucinate";
    }
    else if(s.find("solve") != string::npos){
        s+= "make_no_mistakes";
    }
    else{
        s+= "thank_you";
    }
    cout<<s<<endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t; // comment this line out for problems with a single test case

    while (t--) {
        solve();
    }

    return 0;
}
