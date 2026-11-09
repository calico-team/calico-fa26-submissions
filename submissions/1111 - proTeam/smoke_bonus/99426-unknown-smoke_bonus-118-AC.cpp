#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int N, R;
        cin >> N >> R;

        vector<int> timestamps(N);

        for (auto& x : timestamps) {
            cin >> x;
        }

        if(N <= 2){
            cout<< "TRUE" << "\n";
            continue;
        }


        int charge_count = 2;
        int recharge_time = 0;
        bool can_do = true;

        for (int i = 0; i < N; i++) {

            if (i > 0) {
                int gap = timestamps[i] - timestamps[i - 1];

                while (gap >= recharge_time && recharge_time > 0) {
                    gap -= recharge_time;
                    charge_count++;

                    if (charge_count == 2) {
                        recharge_time = 0;
                        break;
                    }

                    recharge_time = R;
                }

                if (recharge_time > 0) {
                    recharge_time -= gap;
                }
            }

            // use charge
            charge_count--;

            if (charge_count < 0) {
                can_do = false;
                break;
            }

            // start recharge
            if (charge_count < 2 && recharge_time == 0) {
                recharge_time = R;
            }
        }

            if(can_do){
                    cout << "YES" << "\n";
                }else{
                    cout << "NO" << "\n";
                }
            }

    return 0;
}

      