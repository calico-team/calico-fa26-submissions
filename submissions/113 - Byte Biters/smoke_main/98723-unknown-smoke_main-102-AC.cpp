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
    int t; cin >> t;
    while(t--){
        int n, r; cin >> n >> r;
        vector<int> arr(n);
        for(int i = 0 ; i < n; ++i)cin >> arr[i];
        int sc = 2, sr1 = -1, sr2 = -1;
        bool passed = true;
        for(int i = 0; i < n && passed; ++i){
            int time = arr[i];
            if(sr1 <= time && sr1 != -1){
                sc++;
                sr1 = -1;
            }
            if(sr2 <= time && sr2 != -1){
                sc++;
                sr2 = -1;
            }
            if(sc == 2){
                if(sr1 == -1){
                    sr1 = r+time;
                    sc--;
                }
                else if (sr2 == -1){
                    sr2 = r+time;
                }
            }
            else if(sc == 1){
                if(sr1 == -1){
                    sr1 = sr2+r;
                    sc--;
                }
                else if(sr2 == -1){
                    sr2 = sr1+r;
                    sc--;
                }
            }
            else{
                passed = false;
            }
        }
        if (passed){
            cout << "YES" << endl;
        } else{
            cout << "NO" << endl;
        }
    }
    return 0;
}