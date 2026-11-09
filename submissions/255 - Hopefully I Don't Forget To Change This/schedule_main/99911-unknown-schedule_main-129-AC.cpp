#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;
    while(t--){
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> p(n + 1);
        vector<vector<int>> ch(n + 1);
        for (int i=1;i<= n;i++){
            cin >> p[i];
            ch[p[i]].push_back(i);
        }
        vector<int> b,h(n+1,0);
        queue<int> q;
        for(int j=0;j<ch[0].size();j++) q.push(ch[0][j]);
        while(!q.empty()){
            int cur = q.front();
            q.pop();
            b.push_back(cur);
            for (int j=0;j<ch[cur].size();j++) q.push(ch[cur][j]);
        }
        for(int i=b.size()-1;i>=0;i--){
            int cur = b[i];
            if (p[cur]) h[p[cur]] = max(h[p[cur]],h[cur]+1);
        }
        priority_queue<pair<int,int>> pq;
        for(int i=0;i<ch[0].size();i++) pq.push(make_pair(h[ch[0][i]],ch[0][i]));
        int total = 0;
        for(int i=0;i<m && !pq.empty();i++){
            vector<int> now;
            while(!pq.empty() && (int)now.size()<k){
                now.push_back(pq.top().second);
                pq.pop();
            }
            total += now.size();
            for(int j=0;j<now.size();j++){
                int cur = now[j];
                for (int k=0;k<ch[cur].size();k++)
                    pq.push(make_pair(h[ch[cur][k]],ch[cur][k]));
            }
        }
        cout << total << endl;
    }
}
