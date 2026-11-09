#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<algorithm>
#include <vector>
#include<utility>
#include<queue>
#include<map>
#include<set>
using ll = long long;
using pii=std::pair<int,int>;
using pll=std::pair<ll,ll>;
using namespace std;
void setIO(const string& s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
int main() {
	// setIO("berries");
	int t;
	cin>>t;
	while (t--) {
		string s;
		cin>>s;
		int n=s.size();
		int mode=0;
		for (int i=0;i<n;i++) {
			string x;
			for (int j=i;j<n;j++) {
				x.push_back(s[j]);
				if (x=="write_me") {
					mode=1;
				}else if (x=="solve") {
					mode=2;
				}else if (x=="what_is") {
					mode=3;
				}
			}
		}
		cout<<s;
		if (mode==1) {
			cout<<"make_it_sound_human\n";
		}else if (mode==2) {
			cout<<"make_no_mistakes\n";
		}else if (mode==3) {
			cout<<"do_not_hallucinate\n";
		}else {
			cout<<"thank_you\n";
		}
	}
	return 0;
}
