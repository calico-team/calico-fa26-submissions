#include <iostream>
#include <string>
using namespace std;

int main() {
    int t ;
    cin>> t;
    for(int l=0; l<t; l++){
    string prompt;
    cin>>prompt;
    if (prompt.find("write_me") != -1) {
    cout << prompt + "make_it_sound_human" << endl;
    }
    else if  (prompt.find("what_is") != -1)
    {
     cout << prompt + "do_not_hallucinate" << endl;
    }
     else if (prompt.find("solve") != -1)
     {
     cout << prompt + "make_no_mistakes" << endl;}
    else 
    {
    cout << prompt + "thank_you" << endl;
    }
    }
    return 0;
}