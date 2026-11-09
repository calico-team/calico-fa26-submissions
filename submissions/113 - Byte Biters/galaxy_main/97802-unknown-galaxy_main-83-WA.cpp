#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>
#include <deque>
using namespace std;

vector<vector<int>> g;
vector<int> ccs;
int cc = 0;
vector<bool> found;

void dfs(int curr){
    found[curr] = true;
    for (auto &n: g[curr]){
        if (!found[n]){
            ccs[n] = ccs[curr];
            dfs(n);
        }
    }
}

int main(){
    int t; cin >> t;
    while (t--){
        int n,m,q; cin >> n >> m >> q;
        found.clear();
        found.resize(n*m,false);
        g.clear();
        g.resize(n*m,vector<int>());
        cc = 0;
        ccs.clear();
        ccs.resize(n*m,0);
        vector<string> grid(n);
        for (int i = 0; i < n; i++){
            cin >> grid[i];
            for (int j = 0; j < m; j++){
                char colour = grid[i][j];
                if (colour == '.'){
                    if (i!=0){
                        g[i*m+j].push_back((i-1)*m+j);
                    }
                    if (i!=n-1){
                        g[i*m+j].push_back((i+1)*m+j);
                    } 
                    if (j!=0){
                        g[i*m+j].push_back(i*m+(j-1));
                    }
                    if (j!=m-1){
                        g[i*m+j].push_back(i*m+(j+1));
                    } 
                } else if (colour == 'R'){
                    if (i!=0 && grid[i-1][j]!='B'){
                        g[i*m+j].push_back((i-1)*m+j);
                    }
                    if (i!=n-1 && grid[i+1][j]!='B'){
                        g[i*m+j].push_back((i+1)*m+j);
                    } 
                    if (j!=0 && grid[i][j-1]!='B'){
                        g[i*m+j].push_back(i*m+(j-1));
                    }
                    if (j!=m-1 && grid[i][j+1]!='B'){
                        g[i*m+j].push_back(i*m+(j+1));
                    }
                } else{
                    if (i!=0 && grid[i-1][j]!='R'){
                        g[i*m+j].push_back((i-1)*m+j);
                    }
                    if (i!=n-1 && grid[i+1][j]!='R'){
                        g[i*m+j].push_back((i+1)*m+j);
                    } 
                    if (j!=0 && grid[i][j-1]!='R'){
                        g[i*m+j].push_back(i*m+(j-1));
                    }
                    if (j!=m-1 && grid[i][j+1]!='R'){
                        g[i*m+j].push_back(i*m+(j+1));
                    }
                }
            }
        }

        for (int i = 0; i < n*m; i++){
            if (!found[i]){
                cc++;
                ccs[i] = cc;
                dfs(i);
            }
        }

        for (int i = 0; i < q; i++){
            int rs,cs,re,ce; cin >> rs >> cs >> re >> ce;
            if (ccs[rs*m+cs]==ccs[re*m+ce]){
                cout << "YES" << endl;
            } else{
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}

// white move anywhere
// red move not blue
// blue move not red