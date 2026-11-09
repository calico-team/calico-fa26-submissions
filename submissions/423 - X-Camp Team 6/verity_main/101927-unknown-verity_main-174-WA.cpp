#include <bits/stdc++.h>

using namespace std;

int main(){
    int cases;
    for (int i = 0 ; i < 0 ; i ++){
        int strl,cs;
        cin >> strl >> cs;
        vector<char> chars;
        chars.reserve(cs);
        for (int j = 0 ; j < cs ; j++){
            cin >> chars[j];
        }

        int incr = 0;

        string guess(strl,chars[0]);

        while (1){
            cout << guess << endl;

            string correction;
            cin >> correction;

            if (correction == "CORRECT"){
                break;
            }

            incr++;

            for (int l = 0 ; l < strl ; l++){
                if (correction[l] == '_'){
                    guess[i] = chars[incr];
                }
            }
        }
    }
}