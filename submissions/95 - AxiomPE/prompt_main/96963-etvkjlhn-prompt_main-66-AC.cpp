#include <iostream>
#include <string>
using namespace std;

int main(){
    int cas;
    cin >> cas;

    for (int i = 0; i < cas; i++){
        string text;
        cin >> text;

        if (text.find(string("write") + char(95) + "me") != string::npos){
            text += string("make") + char(95) + "it" + char(95) + "sound" + char(95) + "human";
        }
        else if (text.find(string("what") + char(95) + "is") != string::npos){
            text += string("do") + char(95) + "not" + char(95) + "hallucinate";
        }
        else if (text.find("solve") != string::npos){
            text += string("make") + char(95) + "no" + char(95) + "mistakes";
        }
        else{
            text += string("thank") + char(95) + "you";
        }

        cout << text << endl;
    }
    return 0;
}