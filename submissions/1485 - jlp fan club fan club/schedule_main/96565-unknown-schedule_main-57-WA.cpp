#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <set>
#include <map>
#include <stack>
#include <cstdio>
#include <unordered_map>
#include <map>
#include <numeric>
#include <utility>
#include <functional>
#include <string>
#include <list>
using namespace std;
typedef long long ll;


int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;cin>>t;

    while(t--){
        int n, m, k;cin>>n>>m>>k;

        vector<int> nums(n);

        for(int i = 0; i<n; i++){
            cin>>nums[i];
        }

        unordered_map<int, pair<int, int>> deg;

        for(int i = 0; i<n; i++){
            
        }

        vector<int> done(n);


        vector<int> todo;
        int added = 0;
        for(int i = 0; i<n && added<k; i++){
            if(nums[i] == 0){
                todo.push_back(i);
                added++;
            }
        }
        unordered_set<int> fulfilled;

        int res = 0;
        for(int i = 0; i<m; i++){

            for(int j = 0; j<k && j<todo.size(); j++){
                int cur = todo[j];

                fulfilled.insert(cur);
                done[cur] = 1;
                res++;
            }
            vector<int> newtodo;
            added = 0;
            for(int i = 0; i<n && added<k; i++){
                if((nums[i] == 0 || fulfilled.count(nums[i]-1)) && !done[i]){
                    newtodo.push_back(i);
                    added++;
                }
            }

            swap(newtodo, todo);
        }

        cout<<res<<"\n";
    }

}