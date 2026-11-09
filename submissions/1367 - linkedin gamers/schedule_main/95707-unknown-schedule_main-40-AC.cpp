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
    ll N, M, K, res= 0;
    vector< vector<ll> > adjLst;
    void shopeepepepepe(){
		cin >> N >> M >> K;
		 adjLst.resize(N + 1);
		for (int i = 1; i <= N; i++){
			ll x; cin >> x;
			adjLst[ x ].push_back( i );
		}
		ll currSem = 0, currPart = 0;
		queue< pair<ll, ll> > q;
		for (auto i: adjLst[0]){
			q.push( make_pair(i, 0) );
		} while (!q.empty()){
			if (currSem >= M){
				break;
			}
			auto [curr, depth] = q.front();
			if ( depth > currSem ){
				currSem = depth;
				currPart = 0;
				continue;
			} else {
				q.pop();
				res += 1;
				currPart += 1;
				for (auto i: adjLst[curr]){
					q.push( make_pair(i, depth + 1) );
				}
			} 
			
			if (currPart >= K){
				currPart = 0;
				currSem += 1;
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
