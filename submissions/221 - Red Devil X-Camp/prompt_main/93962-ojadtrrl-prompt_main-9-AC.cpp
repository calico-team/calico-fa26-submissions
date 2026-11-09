#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solv(){
    string s, output;
    cin >> s;

    output = s;

    if(s.find("write_me") != string::npos) output += "make_it_sound_human";
    if(s.find("what_is") != string::npos) output += "do_not_hallucinate";
    if(s.find("solve") != string::npos) output += "make_no_mistakes";

    if(output.size() == s.size()) output += "thank_you";

    cout << output << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll t;
    cin >> t;

    while(t--) solv();
}
