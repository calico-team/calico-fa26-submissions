#include <iostream>
#include <string>
#include <random>
#include <vector>
using namespace std;
typedef long long ll;
int main() {
	ios_base::sync_with_stdio(false);
    int x; cin >> x;
    while (x--) {
		int n; cin >> n;
		int m; cin >> m;
		vector<char> letters;
		vector<char> correct;
		vector<int> idxs;
		for (int i=0; i<m; i++) cin >> letters[i];
		string feedback;
		for (int i=0; i<n; i++) {
			feedback += "_";
		}

		while (feedback != "CORRECT") {
			for (int j=0; j<n; j++) {
				char c=feedback[j];
				if (c != '_') {
					idxs.push_back(j);
					correct.push_back(c);
				}
			}
			string guess;
			for (int j=0; j<n; j++) {
			    guess += "_";
			}
			for (int j=0; j<idxs.size(); j++) {
				guess[idxs[j]]=correct[j];
			}
			for (int j=0; j<n; j++) {
				char c=guess[j];
				if (c == '_') {
					random_device rd;
					mt19937 gen(rd());
					uniform_int_distribution<int> distrib(0,m-1);
					int rng=distrib(gen); 
					guess[j]=letters[rng];
				}
			}
			cout << guess << "\n" << flush;
			cin >> feedback;
		}
	}
}
