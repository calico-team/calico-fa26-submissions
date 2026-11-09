#include <bits/stdc++.h>
using namespace std;

long long solve(int N, int K, vector<tuple<int, int, int, char>>& L) {
    long long answer = 0;
    unordered_map<uint64_t, int> highestZ;
    highestZ.reserve(L.size());

    for (int night = 0; night < K; night++) {
        highestZ.clear();

        // Find the highest drone at each (X, Y).
        for (const auto& item : L) {
            int x = get<0>(item);
            int y = get<1>(item);
            int z = get<2>(item);

            uint64_t pos =
                uint64_t(uint32_t(x)) * 4294967296ULL + uint32_t(y);

            auto it = highestZ.find(pos);
            if (it == highestZ.end() || z > it->second) {
                highestZ[pos] = z;
            }
        }

        for (auto& item : L) {
            int& x = get<0>(item);
            int& y = get<1>(item);
            int z = get<2>(item);
            char direction = get<3>(item);

            uint64_t pos =
                uint64_t(uint32_t(x)) * 4294967296ULL + uint32_t(y);

            if (z == highestZ[pos]) {
                answer++;
            }

            switch (direction) {
                case 'N': y++; break;
                case 'S': y--; break;
                case 'E': x++; break;
                case 'W': x--; break;
            }
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin>>t;
    while (t--){
        int N, K; cin>>N>>K;
        vector<tuple<int, int, int, char>> L;
        for (int i = 0; i < N; i++){
            int X, Y, Z;
            char D;
            cin>>X>>Y>>Z>>D;
            L.push_back({X, Y, Z, D});
        }
        cout<<solve(N, K, L)<<endl;
    }
}