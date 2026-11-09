#include <iostream>
#include <string>
using namespace std;

int main() 
{ int s;
cin >> s;

while (s--){
    string t;
    cin >> t;
    
    if (t.find("write_me") != string::npos) {
        t = t + "make_it_sound_human";
       }
       else if (t.find("what_is") != string::npos) {
        t = t + "do_not_hallucinate";
       }
       else if (t.find("solve") != string::npos) {
        t = t + "make_no_mistakes";
       }
       else {
        t = t + "thank_you";
       }
       cout << t << endl;
    }
    return 0;
}