#include <bits/stdc++.h>
using namespace std;
int main()
{
        int T;
        cin>>T;
        for(int x = 0; x<T; x++){
	int drone, night;
	cin>>drone>>night;

	vector<vector<string>>e;
	vector<vector<string>>n;                                     //   (stoi(n[j][2])) - (stoi(e[i][2])) + (stoi(e[j][i]))
	string str;
	cin.ignore();
	int64_t ans = drone*night;
	for(int i=0; i<drone; i++) {
	        vector<string>v;
		string str;
		getline(cin, str);
		stringstream ss(str);
		string abc;
		while(ss>>abc){
		     
		        v.push_back(abc);  
		}
		if (v[v.size()-1] == "E") e.push_back(v);
		else n.push_back(v);
                
	}
        
	for (int i= 0; i<n.size(); i++) {
               for (int j = 0; j<e.size(); j++) {
		 if((stoi(n[i][1]))+night-1>=(stoi(e[j][1]))&& (stoi(n[i][1]))<=(stoi(e[j][1]))) {
		         int a =  (stoi(e[j][1])) - (stoi(n[i][1])) + (stoi(e[j][0]));
		         if((stoi(n[i][0])) == a)
		         ans--;
		}
	
		}
	}
	cout<<ans<<endl;
}
	
}