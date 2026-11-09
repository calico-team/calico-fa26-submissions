// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
    cin >> t; 
    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;
       vector<vector<char>> stage(n); 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                char charcter;
                cin >> charcter;
                stage[i].push_back(charcter);
        }
        }
        map<pair<int, int>, int> good; 

       for (int i = n-1; i >= 0; i--) {
            for (int j = m-1; j >= 0; j--) {
                pair<int, int> pairy = {i , j};
                if (i == n-1 && j == m-1) {
                    good[pairy]=1; 
                }
                else {
                    if( stage[i][j] == '.') {
                       if (good[{i+1, j}] >= 1 || good[{i, j+1}] >= 1 || good[{i, j-1}] >= 1 || good[{i-1, j}] >= 1) {
                            good[pairy] = 1; 
                       }
                    }
                    else if (stage [i][j] == 'R') {
                        if ((good[{i+1, j}] >= 1 && i+1 < n && stage[i+1][j] != 'B') || ( good[{i, j+1}] >= 1  && j+1 < m && stage[i][j+1] != 'B') || (good[{i, j-1}] >= 1 && j-1 >= 0 && stage[i][j-1] != 'B')|| (good[{i-1, j}]>= 1  && i-1 >= 0 && stage[i-1][j] != 'B')) {
                            good[pairy] = 1; 
                       }
                    }
                    else if (stage [i][j] == 'B') {
                        if ((good[{i+1, j}] >= 1 && i+1 < n && stage[i+1][j] != 'R') || ( good[{i, j+1}] >= 1  && j+1 < m  && stage[i][j+1] != 'R') || (good[{i, j-1}] >= 1 && j-1 >= 0 && stage[i][j-1] != 'R')|| (good[{i-1, j}]>= 1  && i-1 >= 0 && stage[i-1][j] != 'R')) {
                            good[pairy] = 1; 
                       }
                }
            }
        }
    } 
    for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                pair<int, int> pairy = {i , j};
                if (i == n-1 && j == m-1) {
                    good[pairy]=1; 
                }
                else {
                    if( stage[i][j] == '.') {
                       if (good[{i+1, j}] >= 1 || good[{i, j+1}] >= 1 || good[{i, j-1}] >= 1 || good[{i-1, j}] >= 1) {
                            good[pairy] = 1; 
                       }
                    }
                    else if (stage [i][j] == 'R') {
                        if ((good[{i+1, j}] >= 1 && i+1 < n && stage[i+1][j] != 'B') || ( good[{i, j+1}] >= 1  && j+1 < m && stage[i][j+1] != 'B') || (good[{i, j-1}] >= 1 && j-1 >= 0 && stage[i][j-1] != 'B')|| (good[{i-1, j}]>= 1  && i-1 >= 0 && stage[i-1][j] != 'B')) {
                            good[pairy] = 1; 
                       }
                    }
                    else if (stage [i][j] == 'B') {
                        if ((good[{i+1, j}] >= 1 && i+1 < n && stage[i+1][j] != 'R') || ( good[{i, j+1}] >= 1  && j+1 < m  && stage[i][j+1] != 'R') || (good[{i, j-1}] >= 1 && j-1 >= 0 && stage[i][j-1] != 'R')|| (good[{i-1, j}]>= 1  && i-1 >= 0 && stage[i-1][j] != 'R')) {
                            good[pairy] = 1; 
                       }
                }
            }
        }
    } 
    for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                pair<int, int> pairy = {i , j};
                if (i == n-1 && j == m-1) {
                    good[pairy]=1; 
                }
                else {
                    if( stage[i][j] == '.') {
                       if (good[{i+1, j}] >= 1 || good[{i, j+1}] >= 1 || good[{i, j-1}] >= 1 || good[{i-1, j}] >= 1) {
                            good[pairy] = 1; 
                       }
                    }
                    else if (stage [i][j] == 'R') {
                        if ((good[{i+1, j}] >= 1 && i+1 < n && stage[i+1][j] != 'B') || ( good[{i, j+1}] >= 1  && j+1 < m && stage[i][j+1] != 'B') || (good[{i, j-1}] >= 1 && j-1 >= 0 && stage[i][j-1] != 'B')|| (good[{i-1, j}]>= 1  && i-1 >= 0 && stage[i-1][j] != 'B')) {
                            good[pairy] = 1; 
                       }
                    }
                    else if (stage [i][j] == 'B') {
                        if ((good[{i+1, j}] >= 1 && i+1 < n && stage[i+1][j] != 'R') || ( good[{i, j+1}] >= 1  && j+1 < m  && stage[i][j+1] != 'R') || (good[{i, j-1}] >= 1 && j-1 >= 0 && stage[i][j-1] != 'R')|| (good[{i-1, j}]>= 1  && i-1 >= 0 && stage[i-1][j] != 'R')) {
                            good[pairy] = 1; 
                       }
                }
            }
        }
    } 
    for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                pair<int, int> pairy = {i , j};
                if (i == n-1 && j == m-1) {
                    good[pairy]=1; 
                }
                else {
                    if( stage[i][j] == '.') {
                       if (good[{i+1, j}] >= 1 || good[{i, j+1}] >= 1 || good[{i, j-1}] >= 1 || good[{i-1, j}] >= 1) {
                            good[pairy] = 1; 
                       }
                    }
                    else if (stage [i][j] == 'R') {
                        if ((good[{i+1, j}] >= 1 && i+1 < n && stage[i+1][j] != 'B') || ( good[{i, j+1}] >= 1  && j+1 < m && stage[i][j+1] != 'B') || (good[{i, j-1}] >= 1 && j-1 >= 0 && stage[i][j-1] != 'B')|| (good[{i-1, j}]>= 1  && i-1 >= 0 && stage[i-1][j] != 'B')) {
                            good[pairy] = 1; 
                       }
                    }
                    else if (stage [i][j] == 'B') {
                        if ((good[{i+1, j}] >= 1 && i+1 < n && stage[i+1][j] != 'R') || ( good[{i, j+1}] >= 1  && j+1 < m  && stage[i][j+1] != 'R') || (good[{i, j-1}] >= 1 && j-1 >= 0 && stage[i][j-1] != 'R')|| (good[{i-1, j}]>= 1  && i-1 >= 0 && stage[i-1][j] != 'R')) {
                            good[pairy] = 1; 
                       }
                }
            }
        }
    } 
 
   
    for (int i = 0; i < q; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if (good[{a, b}] >= 1) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
        
    }
    
}
}