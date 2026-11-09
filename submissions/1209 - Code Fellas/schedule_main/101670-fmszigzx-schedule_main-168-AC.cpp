#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int semesterSuffering;
    cin >> semesterSuffering;
    while (semesterSuffering--) {
        int courses, terms, perTerm;
        cin >> courses >> terms >> perTerm;

        vector<int> dad(courses + 1);
        vector<vector<int>> kids(courses + 1);
        for (int i = 1; i <= courses; i++) {
            cin >> dad[i];
            kids[dad[i]].push_back(i);
        }

        vector<int> order = {0};
        for (size_t i = 0; i < order.size(); i++)
            for (int c : kids[order[i]]) order.push_back(c);

        vector<int> tall(courses + 1, 1);
        for (int i = (int) order.size() - 1; i > 0; i--) {
            int v = order[i];
            tall[dad[v]] = max(tall[dad[v]], tall[v] + 1);
        }

        priority_queue<pair<int, int>> ready;
        for (int r : kids[0]) ready.push({tall[r], r});

        long long gpa = 0;
        for (int t = 0; t < terms && !ready.empty(); t++) {
           vector<int> today;
           while ((int)today.size() < perTerm && !ready.empty()) {
            today.push_back(ready.top().second);
            ready.pop();
        }
        gpa += today.size();
        for (int v : today)
            for (int c : kids[v]) ready.push({tall[c], c});
    }
    cout << gpa << "\n";

}
return 0;
} 



