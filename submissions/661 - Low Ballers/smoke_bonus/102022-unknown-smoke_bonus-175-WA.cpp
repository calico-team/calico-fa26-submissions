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


		int time = 0, latestRequest = 0, timeTillRecharge = -1, charges = 2;
		bool recharged = true, perfect = true;
		for(int j = 0; j < requests.size(); j++) {
			//cout << timeTillRecharge << " " << charges << " " << recharged << endl;
			int alksdjf = charges;
			charges += (requests[j] - time) / r;
			charges = min(charges, 2);
			if (charges != alksdjf) {
				time = requests[j];
			}

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




		if (perfect) {
			cout << "YES\n";
		}else {
			cout << "NO\n";
		}
	}

}
