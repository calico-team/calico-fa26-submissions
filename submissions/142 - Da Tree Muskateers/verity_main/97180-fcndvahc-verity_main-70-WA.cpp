
#include <bits/stdc++.h>
using namespace std;
using ll = long long;     //remember that long long is for int
using vi = vector<int>;
using vll = vector<long long>;
using vii = vector<pair<int, int>>;
using vc = vector<char>;
using vs = vector<string>;
using vb = vector<bool>;
// note that "int digit = string - '0';" is string to int
//and to_string is int(or anything) to string


// custom loop functions:
#define for_0(idx, final) for (int idx = 0; idx < (final); idx++)
#define for_s(idx, start, final) for (int idx = start; idx < (final); idx++)
#define cout_vec(vec) for(auto element : vec){cout << element;}; cout << endl
#define cout_vec_pair(vec) for(auto element : vec){cout << '{' << element.first << ' ' << element.second << "} ";}; cout << endl


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n, k;
    cin >> t;
    while(t--){
        vc letters;
        cin >> n >> k;
        char x;
        vc correct(n, '*');

        int r = 0;

        for_0(_, k){
            cin >> x;
            letters.push_back(x);
        }

        string inp = "";
        while(true){
            vc rem;

            for(auto c : letters){
                rem.push_back(c);
            }

            if(!rem.empty()){
                rotate(rem.begin(), rem.begin() + (r % rem.size()), rem.end());
            }

            string curr = "";

            int idx = 0;

            for_0(i, n){
                if(correct[i] != '*'){
                    curr += correct[i];
                }
                else{
                    curr += rem[idx++ % rem.size()];
                }
            }
            cout << curr << endl;

            cin >> inp;

            if(inp == "CORRECT"){
                break;
            }
            for_0(i, n){
                if(inp[i] != '_'){
                    correct[i] = inp[i];
                }
            }
            r++;

        }
    }


    return 0;
}
