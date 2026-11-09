#include <iostream>
#include <fstream> 
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <utility>
#include <array>

using ll = long long;

using namespace std;

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
    	string str; cin >> str;
        int n = str.length();

        string x = "thank_you";
        for (int i=0; i<n; i++) {
            if (i<=n-8 && str.substr(i,8)=="write_me") {
                x = "make_it_sound_human";
            }else if (i<=n-7 && str.substr(i,7)=="what_is") {
                x = "do_not_hallucinate";
            }else if (i<=n-5 && str.substr(i,5)=="solve") {
                x = "make_no_mistakes";
            }
        }

        cout << str + x << endl;
    }
    return 0;
}

