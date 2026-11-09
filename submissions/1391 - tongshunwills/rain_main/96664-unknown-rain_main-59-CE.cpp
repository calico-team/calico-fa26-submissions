#include <iostream>
using namespace std;

long long solve(int N, long long K, const vector<array<long long, 3>>& L, const vector<char>& dirs) {
    // key: x + y  ->  {east xs, north xs}
    unordered_map<long long, pair<vector<long long>, vector<long long>>> groups;

    for (int i = 0; i < N; i++) {
        long long X = L[i][0], Y = L[i][1];
        long long s = X + Y;
        if (dirs[i] == 'E') groups[s].first.push_back(X);
        else groups[s].second.push_back(X);
    }

    long long meetings = 0;
    for (auto& g : groups) {
        vector<long long>& east = g.second.first;
        vector<long long>& north = g.second.second;
        sort(east.begin(), east.end());
        sort(north.begin(), north.end());

        size_t lo = 0, hi = 0;
        for (long long x1 : east) {
            while (lo < north.size() && north[lo] < x1) lo++;
            while (hi < north.size() && north[hi] <= x1 + K - 1) hi++;
            meetings += hi - lo;
        }
    }

    return (long long)N * K - meetings;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N;
        long long K;
        scanf("%d %lld", &N, &K);

        vector<array<long long, 3>> L(N);
        vector<char> dirs(N);
        for (int i = 0; i < N; i++) {
            long long X, Y, Z;
            char D;
            scanf("%lld %lld %lld %c", &X, &Y, &Z, &D);
            L[i] = {X, Y, Z};
            dirs[i] = D;
        }

        printf("%lld\n", solve(N, K, L, dirs));
    }
    return 0;
}