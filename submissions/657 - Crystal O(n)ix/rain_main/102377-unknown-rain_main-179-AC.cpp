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
    long long maxN = 0;
    for (long long i = 0; i < N; i++) {
        if (dir[i] == 'E') {
            e[ei] = drones[i];
            ei++;
        }

        else {

            if (drones[i].second > maxN) {
                maxN = drones[i].second;
            }
            n[ni] = {drones[i].first + drones[i].second, drones[i].first};
            //ei++;
            ni++;
        }
    }

    //cout << maxN << " ";
    sort(n, n+north);
    std::sort(e, e + east, [](const auto& a, const auto& b) {
        return a.second < b.second; 
    });


    for (long long i = 0; i < east; i++) {
        if (e[i].second > maxN+K) {
            //cout << "TOO SHORT";
            break;
        }
        
        long long sum = e[i].first + e[i].second;

        long long left = 0;
        long long right = north;

        while(left < right) {
            long long mid = left + (right - left) / 2;
            pair<long long, long long> temp = {sum, e[i].first + 1};
            if(n[mid] < temp) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }

        long long first = left;
        left = 0;
        right = north;

        while (left < right) {
            long long mid = left + (right - left) / 2;
            pair<long long, long long> temp = {sum, e[i].first + K};
            if(n[mid] <= temp) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }

        long long last = left;

        tot -= last - first;
    } 

    return tot;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
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
