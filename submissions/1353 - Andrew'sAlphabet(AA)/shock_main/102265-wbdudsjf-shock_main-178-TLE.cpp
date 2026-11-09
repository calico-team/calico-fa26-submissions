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

int main(){
    int T;
    cin >> T;
    while (T--){
        int row, column; cin >> row >> column;
        int num; cin >> num;
        vector<vector<int>> map(row,vector<int>(column)); 
        for (int i=0;i<num;i++){
            for (int r=0;r<map.size();r++){
                for (int c=0;c<map[0].size();c++){
                    map[r][c] = 0;
                }
            }
        }
        for (int i = 0; i < num; i++){
            int R, C, P; cin >> R >> C >> P;
            for (int r=0;r<map.size();r++){
                for (int c=0;c<map[0].size();c++){
                    int calc = P*P-(((r-R)*(r-R))+((c-C)*(c-C)))+1;
                    if (calc>0){
                        map[r][c] = calc;
                    }
                }
            }
        }


        for (int r=0;r<map.size();r++){
            for (int c=0;c<map[0].size();c++){
                cout << map[r][c]<< " ";
            }
            cout << endl;
        }
    }

    return 0;
}