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

        int actualAns = 0;
        int ans = 0;
        int leftOvers = 0;
        int cnt = 0;

        queue<int> q;
        for(int i = 0; i < n; i++){
            cin >> p[i];
            q.push(i + 1);
            if(p[i] == 0){
                if(ans > k){
                    leftOvers++;
                }else{
                    ans++;
                }
            }
        }
        cnt++;
        while(leftOvers != 0){
            if(cnt == m) break;
            cnt++;
            leftOvers -= min(leftOvers, k);
            ans += min(leftOvers, k);
        }
        actualAns += ans;
        ans = 0;

        while(!q.empty()){
            if(cnt == m) break;
            cnt++;
            int first = q.front();
            q.pop();
            for(int i = 0; i < n; i++){
                if(first == p[i]){
                    if(ans > k){
                        leftOvers++;
                    }else{
                        ans++;
                    }
                }
            }
            actualAns += ans;
            while(leftOvers != 0){
                if(cnt == m) break;
                cnt++;
                leftOvers -= min(leftOvers, k);
                ans += min(leftOvers, k);
            }
            ans = 0;
            }
        cout << actualAns << "\n";
    }
    
    return 0;
}
