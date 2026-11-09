
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int T;
    if (!(cin >> T)) return 0;

    while (T--) {
        int N, K;
        cin >> N >> K;
        vector<char> alpha(K);
        for (int i = 0; i < K; i++) cin >> alpha[i];   

        string res(N, '?');                            
        bool solved = false;

        for (int a = 0; a < K && !solved; a++) {
            bool allKnown = true;
            for (int i = 0; i < N; i++)
                if (res[i] == '?') { allKnown = false; break; }
            if (allKnown) break;

    
            cout << string(N, alpha[a]) << endl;

            string resp;
            cin >> resp;

            if (resp == "CORRECT") {
                solved = true;                          
            } else {
                for (int i = 0; i < N; i++)             
                    if (resp[i] != '_') res[i] = resp[i];
            }
        }

        if (!solved) {
            cout << res << endl;                        
            string resp;
            cin >> resp;                               
        }
    }
    return 0;
}
