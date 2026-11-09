#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Dispatches a probe and returns true if the puzzle is solved
bool send_guess(const string& text, string& reply) {
    cout << text << endl; // endl forces a stream flush
    return (cin >> reply) && (reply == "CORRECT");
}

void play_round() {
    int length, alphabet_size;
    if (!(cin >> length >> alphabet_size)) return;

    vector<char> symbols(alphabet_size);
    for (char& sym : symbols) {
        cin >> sym;
    }

    string answer(length, '?');
    string feedback;

    for (int idx = 0; idx < alphabet_size; ++idx) {
        const char probe = symbols[idx];

        // Assemble probe: replace every wildcard with the current symbol
        string query = answer;
        for (char& slot : query) {
            if (slot == '?') slot = probe;
        }

        if (send_guess(query, feedback)) {
            return;
        }

        // Absorb confirmed positions
        for (int pos = 0; pos < length; ++pos) {
            if (feedback[pos] != '_') {
                answer[pos] = feedback[pos];
            }
        }

        // Logical deduction: remaining blanks can only be the last remaining symbol
        if (idx == alphabet_size - 2) {
            const char last_symbol = symbols.back();
            for (char& slot : answer) {
                if (slot == '?') slot = last_symbol;
            }
            send_guess(answer, feedback);
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_cases;
    if (cin >> test_cases) {
        while (test_cases--) {
            play_round();
        }
    }
    return 0;
}