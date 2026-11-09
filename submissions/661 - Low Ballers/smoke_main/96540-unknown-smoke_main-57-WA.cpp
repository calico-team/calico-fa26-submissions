#include <iostream>
#include <vector>
using namespace std;

int main() {
	int t; cin >> t;
	for(int i = 0; i < t; i++) {

		// Input
		int n,r; cin >> n >> r;
		vector<int> requests(n);
		for(int j = 0; j < n; j++) {
			cin >> requests[j];
		}


		int time = 0, latestRequest = 0, timeTillRecharge = r, charges = 2;
		bool recharged = true, perfect = true;
		for(int j = 0; j < requests[requests.size() - 1]; j++) {
			time++;
			if (!recharged) {
				timeTillRecharge--;
			}
			if (timeTillRecharge == 0) {
				if (charges < 2) {
					// Keep charging
					timeTillRecharge = r;
					recharged = false;
				}else {
					// 2 charges
					recharged = true;
					timeTillRecharge = -1;
				}
				charges++;
			}

			if (time == requests[latestRequest]) {
				latestRequest++;
				if (charges > 0) {
					// Use charge
					charges--;
					recharged = false;
					if (charges == 1) {
						timeTillRecharge = r;
					}
				}
				else {
					// Get grilled in vc
					perfect = false;
					break;
				}
			}
		}




		if (perfect) {
			cout << "YES\n";
		}else {
			cout << "NO\n";
		}
	}

}
