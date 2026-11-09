#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
void solve() {
    int N, K;
    if (!(cin >> N >> K)) return;

    vector<char> chars(K);
    for (int i = 0; i < K; ++i) {
        cin >> chars[i];
    }
    string ans(N, '?'); 
    
    bool solved = false;
    for (int c_idx = 0; c_idx < K; ++c_idx) {
        char current_char = chars[c_idx];
        string guess(N, current_char);
        cout << guess << endl;
        cout.flush();

        string response;
        cin >> response;
        if (response == "CORRECT") {
            solved = true;
            break;
        }
        for (int i = 0; i < N; ++i) {
            if (response[i] != '_') {
                ans[i] = response[i];
            }
        }
    }
        cout << ans << endl;
        cout.flush();
        
        string final_response;
        cin >> final_response;
    }
}

int main() {
    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
