/*
ID: connorl3   
TASK: valorant
LANG: C++17
*/

#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <queue>

using namespace std;

ifstream fin("valorant.in");
ofstream fout("valorant.out");

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        int n, r;
        fin >> n >> r;
        vector<int> a(n);

        for(int i = 0; i < n; i++){
            fin >> a[i];
        }

        int smokesCharges = 1;
        int current = 0;
        int prev = a[0];
        bool flag = true;
        for(int i = 1; i < n; i++){
            current = a[i];
            if(current - prev >= r){
                smokesCharges++;
            }

            smokesCharges--;
            if(smokesCharges < 0){
                flag = false;
                break;
            }
            
            prev = current;
        }
        cout << (flag ? "YES\n" : "NO\n");

    }
    
    return 0;
}
