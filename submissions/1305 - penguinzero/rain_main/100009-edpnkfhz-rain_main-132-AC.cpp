#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int main() {
    int t;
    cin >> t;
    for(int q = 0; q < t; q++){
        long long n, k;
        cin >> n >> k;
        vector<vector<int>> east(N), north(N);

        for(int i = 0; i < n; i++){
            int x, y, z;
            char d;
            cin >> x >> y >> z >> d;
            if(d == 'E'){
                east[x+y].push_back(x);
            }else{
                north[x+y].push_back(x);
            }
        }

        long long cnt = 0;
        for(int i = 0; i < N; i++){
            sort(east[i].begin(), east[i].end());
            sort(north[i].begin(), north[i].end());
            int l = 0;
            int r = 0;
            int m = north[i].size();
            for(int x1 : east[i]){
                while(l < m && north[i][l] < x1){
                    l++;
                }
                while(r < m && north[i][r] <= x1 + k - 1){
                    r++;
                }
                cnt += r - l;
            }
        }
        cout << n * k - cnt << '\n';
    }
}
