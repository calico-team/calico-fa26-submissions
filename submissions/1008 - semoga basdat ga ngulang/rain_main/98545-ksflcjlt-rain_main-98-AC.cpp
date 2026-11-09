#include <bits/stdc++.h>
#define ll long long
#define endl "\n"
using namespace std;



int main() {
	// your code goes here
	ll t;
	cin >> t;
	while(t--){
	    ll n,k;
	    cin >>n>>k;
	    unordered_map<ll, pair<vector<ll>, vector<ll>>> grup;
	    
	    for(int i=0; i<n; i++){
	        ll x,y,z;
	        char d;
	        cin >> x >> y >> z >> d;
	        
	        if (d=='E'){
	            grup[x+y].first.push_back(x);
	        }
	        else{
	            grup[x+y].second.push_back(x);
	        }
	    }
	    ll makswater= n*k;
	    ll count=0;
	    
	    for(auto&x: grup){
	        vector<ll>& E_list= x.second.first;
	        vector<ll>& N_list= x.second.second;
	        
	        if(E_list.empty() || N_list.empty()) continue;
	        sort(E_list.begin(), E_list.end());
	        
	        for(ll j: N_list){
	            auto kanan= upper_bound(E_list.begin(), E_list.end(), j);
	            auto kiri= upper_bound(E_list.begin(), E_list.end(), j-k);
	            
	            ll temp= distance(kiri, kanan);
	            makswater -= temp;
	        }
	    }
	    cout << makswater << endl;
	        
	}

}
