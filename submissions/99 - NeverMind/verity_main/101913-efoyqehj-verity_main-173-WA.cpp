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
		int a,b; cin >> a >> b;
		vector<char>letters(b); 
		for (int i=0; i<b; i++) cin >> letters[i];
		string answer;
		for (int i=0; i<a; i++) {
			answer += '_';
		}
		string response;
		for (int i=0; i<a; i++) {
			string guess;
			for (int j=0; j<a; j++) {
				guess += letters[i];
			}
			cout << guess << endl;
			cin >> response;
			for (int j=0; j<a; j++) {
				if (response[j] != '_') {
					answer[j] = response[j];
				}
			}
		}
		cout << answer << endl;
		cin >> response;
	}
}

