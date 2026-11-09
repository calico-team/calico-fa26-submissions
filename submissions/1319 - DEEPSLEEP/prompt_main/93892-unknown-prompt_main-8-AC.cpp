#include <bits/stdc++.h>
using namespace std;

int T;
string s;
bool flag;
map<string, string> mp;

int main(){
    mp["write_me"] = "make_it_sound_human";
    mp["what_is"] = "do_not_hallucinate";
    mp["solve"] = "make_no_mistakes";
    cin >> T;
    while (T--){
        cin >> s; flag = false;
        for (pair<string, string> pii : mp){
            if (s.find(pii.first) != EOF){
                cout << s << pii.second << endl;
                flag = true;
                break;
            }
        }
        if (!flag){
            cout << s << "thank_you" << endl;
        }
    }
    return 0;
}