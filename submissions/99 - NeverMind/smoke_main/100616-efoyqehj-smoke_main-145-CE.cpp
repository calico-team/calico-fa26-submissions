#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int x; cin >> x;
    while (x--) {
        bool cando=true;
        int a,b;
		cin >> a >> b;
		vector<int> times(a);
		for (int i=0; i<a; i++) {
			cin >> times[i];
		}
		int ch1cd=0;
		int ch2cd=0;
		for (int t=0; t<times[a-1]; t++) {
		    if (find(times.begin(), times.end(), t) != times.end()) {
		        if (ch1cd > 1 && ch2cd > 1) {
		            cando = false;
		        } else {
		            if (ch1cd == 0) {
		                ch1cd += b;
		            } else {
		                ch2cd += b;
		            }
		        }
		    } else {
	            if ((ch1cd < ch2cd && ch1cd != 0) || (ch2cd == 0 && ch1cd > 0)) {
		            ch1cd--;
		        } else if ((ch2cd < ch1cd && ch2cd != 0) || (ch1cd == 0 && ch2cd > 0)) {
		            ch2cd--;
		        }
		    }
		}
		if (cando) {
		    cout << "YES\n";
		} else {
		    cout << "NO\n";
		}
	}
}
