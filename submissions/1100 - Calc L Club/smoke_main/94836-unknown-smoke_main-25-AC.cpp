#include <iostream>
#include <vector>
#include <string>

using namespace std;

string possible(int recharge, const vector<int>& times) {
    int num_charges = 1;
    int time_left = recharge;
    for (int i = 1; i < times.size(); i++) {
        time_left -= times[i] - times[i - 1];
        while (num_charges < 2 && time_left <= 0) {
            num_charges++;
            time_left += recharge;
        }
        if (num_charges == 2) time_left = recharge;
        if (num_charges == 0) return "NO";
        num_charges--;
    }
    return "YES";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int num_testcases, num_smoke_requests, recharge, time;
    cin >> num_testcases;
    while (num_testcases--) {
        cin >> num_smoke_requests >> recharge;
        vector<int> times;
        while (num_smoke_requests--) {
            cin >> time;
            times.push_back(time);
        }
        string result = possible(recharge, times);
        cout << result << "\n";
    }
    return 0;
}