#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<int>> children(n);
    vector<int> roots;
    int inp;
    for(int i=0;i<n;i++){
        cin >> inp;
        inp--;
        if(inp==-1) roots.push_back(i);
        else children[inp].push_back(i);
    }
    vector<int> order=roots;
    for(int i=0;i<n;i++) for(int o:children[order[i]]) order.push_back(o);
    vector<int> h(n);
    for(int i=n-1;i>=0;i--) for(int o:children[order[i]]) h[order[i]]=max(h[order[i]],h[o]+1);
    priority_queue<vector<int>> available;
    for(int i:roots) available.push({h[i],i});
    int out=0;
    for(int i=0;i<m and available.size()>0;i++){
        vector<int> comp;
        for(int o=0;o<k and available.size()>0;o++){
            comp.push_back(available.top()[1]);
            available.pop();
            out++;
        }
        for(int o:comp) for(int p:children[o]) available.push({h[p],p});
    }
    cout << out << '\n';
}


int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tc=1;
  cin >> tc;
  for (int t=1;t<=tc;t++){
    solve();
  }
}