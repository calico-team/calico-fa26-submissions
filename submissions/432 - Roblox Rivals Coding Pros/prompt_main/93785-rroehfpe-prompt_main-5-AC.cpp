#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <cmath>
#include <cctype>
#include <numeric>
#include <iomanip>
#include <climits>
#include <list>
using namespace std;



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(12);

    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        string S;
        cin >> S;

        if (S.find("write_me") != string::npos) {
            S += "make_it_sound_human";
        } else if (S.find("what_is") != string::npos) {
            S += "do_not_hallucinate";
        } else if (S.find("solve") != string::npos) {
            S += "make_no_mistakes";
        } else {
            S += "thank_you";
        }

        cout << S << '\n';
    }


    
    return 0;
}