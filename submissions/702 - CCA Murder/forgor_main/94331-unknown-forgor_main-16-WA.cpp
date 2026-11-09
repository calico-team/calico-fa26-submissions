#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int main() {
    string s; cin >> s;
    
    int i,j,x,y,z,n;
    
    if (s == "FIRST") {
        cin >> n;
        
        vector<int> edges[n];
        
        for (i = 0; i < n - 1; ++i) {
            cin >> x >> y; --x; --y;
            
            edges[x].push_back(y);
            edges[y].push_back(x);
        }
        
        queue<pair<int, int>> q;
        
        for (i = 0; i < edges[0].size(); ++i) {
            q.push({0, edges[0][i]});
        }
        
        int a[n - 1];
        
        while (!q.empty()) {
            x = q.front().first;
            y = q.front().second;
            q.pop();
            
            a[y - 1] = x;
            
            for (i = 0; i < edges[y].size(); ++i) {
                if (edges[y][i] != x) {
                    q.push({y, edges[y][i]});
                }
            }
        }
        
        x = 0;
        
        for (i = 0; i < n - 1; ++i) {
            x = (x + a[i]) % n;
            
            cout << a[i] << ' ';
        }
        
        cout << x;
    }
    else {
        cin >> n;
        
        int a[n];
        
        x = 0;
        
        for (i = 0; i < n; ++i) {
            cin >> a[i];
            
            if (a[i] == -1) {
                y = i;
            }
            else {
                x = (x + a[i]) % n;
            }
        }
        
        a[y] = (n - x) % n;
        
        for (i = 0; i < n - 1; ++i) {
            cout << i + 2 << ' ' << a[i] + 1 << '\n';
        }
    }
}