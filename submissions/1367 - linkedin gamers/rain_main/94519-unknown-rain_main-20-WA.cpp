#include <iostream>
#include <bits/stdc++.h>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unistd.h>     //required for usleep()


using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef unsigned int uint;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tuple<ll, ll, ll> tll;


class Solution {
    public:
    ll N, K, res;
    unordered_map< ll, vector< tuple<ll, ll, ll> > > v1;
    unordered_map< ll, vector< tuple<ll, ll, ll> > > v2;
    void shopeepepepepe(){
		cin >> N >> K;
		res = N * K;
		for (int i = 0 ; i < N ; i++){
			ll Xi, Yi, Zi; char dir;
			cin >> Xi >> Yi >> Zi; cin >> dir;
			if (dir == 'E'){
				v1[ Xi + Yi ].push_back( make_tuple( Xi, Yi, Zi ) );
			} else {
				v2[ Xi + Yi ].push_back( make_tuple( Xi, Yi, Zi ) );
			}
		} 
		for ( auto [i, vec] : v2 ){
			sort( vec.begin(), vec.end() );
		}
		//cout << '\t' << N * K << '\n';
		for ( auto [i, vec] : v1 ){
			for (auto [xi, yi, zi]: vec){
				auto lb = lower_bound( v2[i].begin(), v2[i].end(), make_tuple( xi, -1, -1) ) - v2[i].begin(),
				     rb = upper_bound( v2[i].begin(), v2[i].end(), make_tuple( xi + K - 1, INT_MAX, INT_MAX) ) - v2[i].begin();
				res -= (rb - lb);
				//cout << '\t' << i << '\t' << res << '\n';
			}
		}
		cout << res << '\n';
	}
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    
    ll TC; cin >> TC;
    for (int i = 0; i < TC; i++){
		Solution p;
		p.shopeepepepepe();
	}
    
}
