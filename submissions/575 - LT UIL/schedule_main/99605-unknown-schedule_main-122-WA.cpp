/*
ID: connorl3   
TASK: averageberkeleycsmajor
LANG: C++17
*/

#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <queue>

using namespace std;

ifstream fin("averageberkeleycsmajor.in");
ofstream fout("averageberkeleycsmajor.out");

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> p(n);
        set<pair<int, int>> a;
        int ans = 0;
        int ansAct = 0;
        
        for(int i = 0; i < n; i++){
            cin >> p[i];
            a.insert({p[i], i + 1});
        }
        int cnt = 0;
        int leftOvers = 0;
        while(!a.empty()){
            auto it = a.begin();
            auto [x, i] = *it;
            a.erase(it);
            if(cnt == m) break;
            cnt++;
            for(int j = 0; j < n; j++){
                if(i - 1 == p[j]){
                    if(ansAct > k){
                        leftOvers++;
                    }else{
                        ansAct++;
                    }
                }
            }
            ans += ansAct;
            ansAct = leftOvers;
            leftOvers = 0;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
