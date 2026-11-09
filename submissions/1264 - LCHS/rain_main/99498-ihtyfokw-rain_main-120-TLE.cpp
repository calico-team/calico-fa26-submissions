#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        
        int rain = 0;
        
        vector<pair<int, int>> pos(n);
        vector<int> hei(n, 0);
        vector<char> dir(n);
        
        int maxX = 0;
        int maxY = 0;
        
        for (int i = 0; i < n; i++) {
            int x, y, z;
            char d;
            cin >> x >> y >> z >> d;
            
            pos[i] = {x, y};
            dir[i] = d;
            hei[i] = z;
        }
        
        for (int a = 0; a < k; a++) {
            for (int i = 0; i < n; i++) {
                pair<int, int> cur = pos[i];
                int curx = cur.first;
                int cury = cur.second;
                int curz = hei[i];
                bool b = false;
                
                int h = 0;
                for (int j = 0; j < n; j++) {
                    if (pos[j].first == curx && pos[j].second == cury && hei[j] > curz) {
                        b = true;
                        break;
                    }
                }
                
                if (!b) {
                    rain++;
                }
            }
            
            for (int i = 0; i < n; i++) {
                if (dir[i] == 'E') {
                    pos[i].first++;
                } else {
                    pos[i].second++;
                }
            }
        }
        cout << rain << endl;
    }
    
    return 0;
}