// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

void run_guess(int n, vector<unordered_set<char>>& options, vector<char>& assignment) {
    string output = "";
    for (int i=0; i<n; i++) {
        if (assignment[i] != '_') {
            output += assignment[i];
        } else {
            char option = *options[i].begin();
            options[i].erase(option);
            output += option;
        }
    }
    cout << output << "\n";
}
int main() {
	int t; cin >> t;
    while (t-- > 0) {
        int n,k;
        char j;
        cin >> n;
        cin >> k;
        unordered_set<char> characters;
        for (int i =0 ; i<k; i++) {
            cin >> j;
            characters.insert(j);
        }
        vector<unordered_set<char>> options(n, characters);
        vector<char> assignment(n, '_');
        string response;
        while (true)
        {
            run_guess(n, options, assignment);
            string response; cin >> response;
            if (response == "CORRECT") {
                break;
            }
            int i=0;
            for (char c : response) {
                if (c != '_') {
                    assignment[i] = c;
                }
                i++;
            }
        }

    }
}
