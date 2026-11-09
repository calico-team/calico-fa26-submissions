#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int T;
    cin>> T;
    while (T--) {
        int n, m, k;
        cin>> n>> m>> k;
        vector<int> p(n+1);
        vector<vector<int>> children(n+1);
        for (int i=1; i<= n; i++) {
            cin>> p[i];
            if (p[i]!=0) children[p[i]].push_back(i);
        }

        vector<int> order;
        for (int i= 1; i<= n; i++) {
            if (p[i]== 0) order.push_back(i);
        }

        for (int idx= 0; idx< (int)order.size(); idx++) {
            int v= order[idx];
            for (int c: children[v]){
                order.push_back(c);
            }
        }

        vector<int> height(n+1, 1);
        for (int idx= (int)order.size()-1; idx>= 0; idx--) {
            int v= order[idx];
            if (p[v]!= 0 && height[v]+1> height[p[v]]) {
                height[p[v]]= height[v]+1;
            }
        }

        priority_queue<pair<int, int>> pq;
        for (int i= 1; i<= n; i++) {
            if (p[i]== 0) pq.push({height[i], i});
        }

        int taken= 0;
        for (int sem= 0; sem< m && !pq.empty(); sem++) {
            vector<int> chosen;
            while ((int)chosen.size()< k && !pq.empty()) {
                chosen.push_back(pq.top().second);
                pq.pop();
            }
            taken+= chosen.size();
            for (int v: chosen) {
                for (int c: children[v]) {
                    pq.push({height[c], c});
                }
            }
        }

        cout<< taken<< "\n";
    }
}