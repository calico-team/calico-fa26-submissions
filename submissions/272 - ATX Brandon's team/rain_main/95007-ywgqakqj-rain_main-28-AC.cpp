#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>> T;
    while (T--){
        int N;
        long long K;
        cin >>N>> K;
        map<long long, pair<vector<long long>,vector<long long>>> groups;
        for(int i = 0; i <N; i++){
            long long x, y, z;
            char d;
            cin >>x >>y >> z >> d;
            if (d =='E') {
                groups[x + y].first.push_back(x);
            }else {
                groups[x + y].second.push_back(x);
            }
        }
        long long collisions =0;
        for (auto &entry : groups) {
            auto &east =entry.second.first;
            auto &north = entry.second.second;
            sort(east.begin(), east.end());
            for(long long nx : north) {
                auto left =lower_bound(
                    east.begin(), east.end(), nx- K + 1
                );
                auto right =lower_bound(
                    east.begin(), east.end(), nx
                );
                collisions+= right - left;
            }
        }
        cout <<1LL * N*K - collisions << '\n';
    }
    return 0;
}