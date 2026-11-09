// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

long long solve(pair<long long,long long>* drones, long long N, long long K, char* dir) {
    long long tot = N*K;
    K--;
    long long east = 0;
    long long north = 0;
    for (long long i = 0; i < N; i++) {
        if (dir[i] == 'E') {
            east++;
        }

        else {
            north++;
        }
    }

    pair<long long,long long> e[east];
    pair<long long,long long> n[north];
    long long ei = 0;
    long long ni = 0;
    for (long long i = 0; i < N; i++) {
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


    for (long long i = 0; i < east; i++) {
        for (long long j = 0; j < north; j++) {
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
    long long T;
    cin >> T;
    while (T--) {
        long long N,K;
        cin >> N; 
        cin >> K;
        pair<long long,long long> drones[N];
        char dir[N];

        for (long long i = 0; i < N; i++) {
            long long Z;
            cin >> drones[i].first >> drones[i].second;
            cin >> Z;
            cin >> dir[i];
        }

        cout << solve(drones, N, K, dir) << "\n";
    }
}
