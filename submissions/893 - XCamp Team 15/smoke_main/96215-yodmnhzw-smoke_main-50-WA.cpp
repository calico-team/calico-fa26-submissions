#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int testcases;
    cin >> testcases;
    for (int testcase = 0; testcase < testcases; testcase++) {
        int smokeRequests[100000] = {0};
        int smokeRequestCount = 0;
        int rechargeTime = 0;
        cin >> smokeRequestCount >> rechargeTime;
        int smokeCharges = 2;
        int smokeRechargeProgress = 0;
        bool skip = false;

        for (int i = 0; i < smokeRequestCount; i++) {
            cin >> smokeRequests[i];
        }

        for (int i = 0; i < smokeRequestCount; i++) {
            if (i == 0) {
                smokeRechargeProgress = smokeRequests[i];
            } else {
                smokeRechargeProgress += (smokeRequests[i] - smokeRequests[i - 1]);
            }
            smokeCharges = min(2, smokeCharges + (smokeRechargeProgress / rechargeTime));
            smokeRechargeProgress %= rechargeTime;
            smokeCharges--;
            if (smokeCharges < 0) {
                cout << "NO" << endl;
                skip = true;
                break;
            }
        }
        if (skip) {continue;}

        cout << "YES" << endl;
        continue;
    }
}