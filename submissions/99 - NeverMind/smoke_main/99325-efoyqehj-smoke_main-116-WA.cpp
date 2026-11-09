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
		for (int i=3; i<a; i++) {
			int p=times[i]-times[i-1]; 
			if (p < b) cando = false;
		}
		if (cando) {
			cout << "YES \n";
		} else {
			cout << "NO \n";
		}
	}
}
