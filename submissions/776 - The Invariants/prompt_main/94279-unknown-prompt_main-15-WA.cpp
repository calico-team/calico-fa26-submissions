#include <iostream>
#include <string>
using namespace std;

int main(){
    int n;
    cin >> n;
    while(n--){
        string s;
        getline(cin, s);
        cout << s;
        if(s.find("write_me") != string::npos) cout << "make_it_sound_human" << endl;
        else if(s.find("what_is") != string::npos) cout << "do_not_hallucinat" << endl;
        else if(s.find("solve") != string::npos) cout << "make_no_mistakes" << endl;
        else cout << "thank_you" << endl;

        cout << "\n";

    }
    return 0;
}