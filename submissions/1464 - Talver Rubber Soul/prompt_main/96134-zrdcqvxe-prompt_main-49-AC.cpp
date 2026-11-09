#include <bits/stdc++.h>
using namespace std;
void solve(){
string S;
cin >> S;
 if (S.find("write_me") != string::npos) { 
cout << S << "make_it_sound_human \n";
} else if (S.find("what_is") != string::npos) {
cout << S << "do_not_hallucinate \n";
} else if (S.find("solve") != string::npos) {
cout << S << "make_no_mistakes \n";
} else {
cout << S << "thank_you \n"; // thank_you https://www.geeksforgeeks.org/cpp/string-find-in-cpp/ LOL
}
}
int main (){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
	return 0;
}