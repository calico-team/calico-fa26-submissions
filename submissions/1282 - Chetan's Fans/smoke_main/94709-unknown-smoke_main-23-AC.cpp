#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while (tests--) {
        int requests, recharge;
        cin >> requests >> recharge;
        long long ready = 0, last = 0;
        bool possible = true;
        while (requests--) {
            int time;
            cin >> time;
            if (ready > time) possible = false;
            ready = last;
            last = max(last, static_cast<long long>(time)) + recharge;
        }
        cout << (possible ? "YES\n" : "NO\n");
    }
}
