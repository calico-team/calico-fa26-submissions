#include <bits/stdc++.h>
using namespace std;

int main() {
    mt19937 rng(random_device{}());

    auto pick = [&](const vector<string>& v) -> string {
        uniform_int_distribution<size_t> dist(0, v.size() - 1);
        return v[dist(rng)];
    };

    string line;
    getline(cin, line);
    int n = stoi(line);

    for (int t = 0; t < n; t++) {
        getline(cin, line);
        istringstream header(line);
        int a, b;
        header >> a >> b;

        getline(cin, line);
        istringstream tokens(line);
        vector<string> arr;
        string tok;
        while (tokens >> tok) {
            arr.push_back(tok);
        }

        while ((int)arr.size() < a) {
            if (arr.empty()) break;
            string chosen = pick(arr);
            arr.push_back(chosen);
        }

        for (const auto& s : arr) {
            cout << s;
        }

        while (true) {
            if (!getline(cin, line)) break;
            string next = line;
            if (next.find('_') == string::npos) break;

            size_t origLen = next.size();
            for (size_t i = 0; i < origLen; i++) {
                if (i < next.size() && next[i] == '_') {
                    if (arr.empty()) break;
                    string chosen = pick(arr);
                    next = next.substr(0, i) + chosen + next.substr(i + 1);
                }
            }
            cout << next << "\n";
        }
    }

    return 0;
}