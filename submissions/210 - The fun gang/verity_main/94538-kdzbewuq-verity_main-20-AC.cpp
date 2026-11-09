#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; // test cases
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n, k;
        cin >> n >> k;
        vector<char> characters(k);
        for (int i = 0; i < k; i++) {
            cin >> characters[i];
        }
        vector<deque<char>> possible(n);
        for (auto &letter : possible) {
            for (int i = 0; i < k; i++) {
                letter.push_back(characters[i]);
            }
        }
        while (true) {
            for (auto &letter : possible) {
                cout << letter.front();
            }
            cout << endl;
            string result;
            cin >> result;
            if (result == "CORRECT") break;
            for (int i = 0; i < result.length(); i++) if (result[i] == '_') possible[i].pop_front();

        }
    }
    return 0;
}