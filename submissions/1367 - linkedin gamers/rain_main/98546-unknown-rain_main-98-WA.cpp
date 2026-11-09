// Working off my teammate's WA

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
    map< ll, vector< ll > > v1;
    map< ll, vector< ll > > v2;
    void shopeepepepepe(){
        cin >> N >> K;
        res = N * K;
        for (int i = 0 ; i < N ; i++){
            ll Xi, Yi, Zi; char dir;
            cin >> Xi >> Yi >> Zi; cin >> dir;
            if (dir == 'E'){
                v1[ Xi + Yi ].push_back(Xi);
            } else {
                v2[ Xi + Yi ].push_back(Xi);
            }
        } 
        for ( auto [i, vec] : v2 ){
            sort( vec.begin(), vec.end() );
        }
        //cout << '\t' << N * K << '\n';
        for ( auto [i, vec] : v1 ){
			sort( vec.begin(), vec.end() );
            for (auto xi: vec){
                // cout<<(typeid(xi+K-1)==typeid(int))<<endl;
                if(v2.count(i)==0)continue;
                auto lb = upper_bound(v2[i].begin(), v2[i].end(), xi),
                     rb = lower_bound(v2[i].begin(), v2[i].end(), xi + K);
                res -= distance(lb, rb);
                //cout << '\t' << i << '\t' << res << '\n';
            }
        }
        cout << res << '\n';
    }
};

/*
1
4 3
0 0 0 E
8 8 2 E
8 9 2 E
2 1 1 N
*/

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    
    ll TC; cin >> TC;
    for (int i = 0; i < TC; i++){
        Solution p;
        p.shopeepepepepe();
    }
    
}
