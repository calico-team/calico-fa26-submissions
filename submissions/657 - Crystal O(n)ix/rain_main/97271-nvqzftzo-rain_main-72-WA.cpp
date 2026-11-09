// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int solve(pair<int,int>* drones, int N, int K, char* dir) {
    int tot = N*K;
    K--;
    int east = 0;
    int north = 0;
    for (int i = 0; i < N; i++) {
        if (dir[i] == 'E') {
            east++;
        }

        else {
            north++;
        }
    }

    pair<int,int> e[east];
    pair<int,int> n[north];
    int ei = 0;
    int ni = 0;
    for (int i = 0; i < N; i++) {
        if (dir[i] == 'E') {
            e[ei] = drones[i];
            ei++;
        }

        else {
            n[ni] = drones[i];
            //ei++;
            ni++;
        }
    }

    sort(n, n+north);
    std::sort(e, e + east, [](const auto& a, const auto& b) {
        return a.second < b.second; 
    });


    for (int i = 0; i < east; i++) {
        for (int j = 0; j < north; j++) {
            if (n[j].first > e[i].first+K) {
                //cout << " TOO FAR";
                break;
            }

            else if (n[j].first - e[i].first == e[i].second - n[j].second && 
            (e[i].second - n[j].second > 0 ) 
            && e[i].second - n[j].second <= K) {
                // cout << "Intersection between " << e[i].first << " " << e[i].second 
                // << " and " << n[j].first << " " << n[j].second << " ";
                tot--;
            }
        }  
    } 

    return tot;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N,K;
        cin >> N; 
        cin >> K;
        pair<int,int> drones[N];
        char dir[N];

        for (int i = 0; i < N; i++) {
            int Z;
            cin >> drones[i].first >> drones[i].second;
            cin >> Z;
            cin >> dir[i];
        }

        cout << solve(drones, N, K, dir) << "\n";
    }
}
