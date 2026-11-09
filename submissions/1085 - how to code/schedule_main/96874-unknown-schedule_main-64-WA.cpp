#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--){
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> times(n+1); //index i stores amt of courses that require course i
        vector<vector<int>> edges(n+1);
        priority_queue<pair<int, int>> q; //# courses that need course i, i
        for(int i = 0; i<n; i++){
            int a;
            cin >> a;
            edges[a].push_back(i+1);
            times[a]++;
        }
        for(auto node:edges[0]){
            q.push({times[node], node});
        }
        int taken = 0;
        int sems_over=0;
        while(!q.empty() && sems_over<m && taken<n){
            int semester=0;
            vector<int> needs;
            while(!q.empty() && semester<k){
                pair<int, int> p = q.top();
                q.pop();
                int course = p.second; //the course you just took
                semester++;
                needs.push_back(course);
            }
            for(int i = 0; i<needs.size(); i++){
                for(auto node:edges[needs[i]]){
                    q.push({times[node], node});
                    // cout << needs[i] << "\n";
                }
                taken++;
            }
            sems_over++;
        }
        cout << taken << "\n";
        
    }
}