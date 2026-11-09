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
    while (t--){
        int n, k; cin >> n >> k;
        vector<string> a(k);
        for (int i = 0; i < k; i++){
            cin >> a[i];
        }

        string guess = "";
        for (int i = 0; i < n; i++){
            guess+="_";
        }
        int i = 0;
        while (guess!="CORRECT" && i < k){
            for (auto&c:guess){
                if (c=='_'){
                    cout << a[i];
                } else{
                    cout << c;
                }
            }
            cout << endl;
            cin >> guess;
            i++;
        }
    }

    return 0;
}