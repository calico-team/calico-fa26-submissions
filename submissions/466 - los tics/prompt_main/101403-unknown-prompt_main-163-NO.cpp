#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main () {
    int T, C;
    
    cin >> T;
    while (1<=T and T>=100) {
        cin >> T;
    }

    cin.ignore();

    vector <string> S (T);
    for (C=0; C<T; C++) {
        getline (cin, S[C]);
        while(1<=S[C].size() and S[C].size()>=100) {
            getline(cin, S[C]);
        }
    }
    for (C=0; C<T; C++) {
        size_t posicion1 = S[C].find("write_me");
        size_t posicion2 = S[C].find("what_is");
        size_t posicion3 = S[C].find("solve");
        if(posicion1!=string::npos) {
            S[C].append("make_it_sound_human");
        } else if (posicion2!=string::npos) {
            S[C].append("do_not_hallucinate");
        } else if (posicion3!=string::npos) {
            S[C].append("make_no_mistakes");
        } else {
            S[C].append("thank_you");
        }
    }
    
    for (C=0; C<T; C++) {
        cout << S[C] << endl;
    }
}