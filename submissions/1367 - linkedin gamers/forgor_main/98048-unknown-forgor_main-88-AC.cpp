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
    string S; ll N;
    vector< ll > A;
    vector< vector<ll> > adjLst;
    void DFS(ll curr, ll par){
		for ( auto i: adjLst[curr] ){
			if (i != par){
				A[i] = curr;
				DFS(i, curr);
			}
		}
	}
    void shopeepepepepe(){
		cin >> S; cin >> N;
		A.resize(N + 4); adjLst.resize(N + 4);
		if ( S == "FIRST" ){
			
			for (int i = 0 ; i < N - 1; i++){
				ll ui, vi; cin >> ui >> vi;
				adjLst[ ui ].push_back( vi );
				adjLst[ vi ].push_back( ui );
			}
			DFS( 1, -1 );
			A[1] = 0;
			for ( int i = 2; i <= N; i++){
				A[1] ^= A[i];
			}
			for ( int i = 1; i <= N; i++){
				cout << A[i] << ' ';
				
			} cout << '\n';
		}
		if ( S == "SECOND" ){
			ll cum = 0, targ = -1;
			for (int i = 1; i <= N; i++){
				cin >> A[i];
			}
			for ( int i = 2; i <= N; i++){
				if (A[i] == -1){
					targ = i;
				} else {
					cum ^= A[i];
				}
			} if (targ != -1){
				A[targ] = A[1] ^ cum;
			}for (int i = 2; i <= N; i++){
				cout << i << ' ' << A[i] << '\n';
			}
		}
	}
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    ll TC = 1;
    for (int i = 0; i < TC; i++){
		Solution p;
		p.shopeepepepepe();
	}
}
