#include <iostream>
#include <vector>
#include <string>

using namespace std;

void find_string(int length, const vector<char>& possible_letters) {
    string final(length, ' ');
    string response;
    for (const char& letter: possible_letters) {
        string guess(length, letter);
        cout << guess << endl;
        cin >> response;
        if (response == "CORRECT") return;
        for (int i = 0; i < response.size(); i++) {
            if (response[i] != '_') final[i] = response[i];
        }
    }
    cout << final << endl;
    cin >> response;
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int num_testcases, length, num_possible_letters;
    char letter;
    cin >> num_testcases;
    while (num_testcases--) {
        cin >> length >> num_possible_letters;
        vector<char> possible_letters;
        while (num_possible_letters--) {
            cin >> letter;
            possible_letters.push_back(letter);
        }
        find_string(length, possible_letters);
    }
    return 0;
}