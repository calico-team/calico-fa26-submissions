#include <bits/stdc++.h>
using namespace std;
int main()
{
        int T;
        cin>>T;
        for(int x = 0; x<T; x++){
	int drone, night;
	cin>>drone>>night;

	vector<string>e;
	vector<string>n;                                     //   (n[j][2] - '0') - (e[i][2] - '0') + (e[j][i] - '0')
	string str;
	cin.ignore();
	int ans = drone*night;
	for(int i=0; i<drone; i++) {
		string str;
		getline(cin, str);
		if (str.back() == 'E') e.push_back(str);
		else n.push_back(str);
                
	}
        
	for (int i= 0; i<n.size(); i++) {
               for (int j = 0; j<e.size(); j++) {
		 if((n[i][2] - '0')+night>(e[j][2] - '0')&& (n[i][2] - '0')<(e[j][2] - '0')) {
		         int a =  (e[j][2] - '0') - (n[i][2] - '0') + (e[j][0] - '0');
		         if((n[i][0] - '0') == a)
		         ans--;
		}
	
		}
	}
	cout<<ans<<endl;
}
	
}