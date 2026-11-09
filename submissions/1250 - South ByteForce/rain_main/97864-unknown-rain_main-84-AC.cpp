// Source: https://usaco.guide/general/io


#include <bits/stdc++.h>
using namespace std;

struct Drone {
    int x,y,z;
    char c;
};
int main() {
    int t;cin>>t;
    while (t--) {
        int n; long long k; cin >> n >> k;
        map<int, vector<Drone>> groups;

        for (int i = 0; i < n; i++) {
            int x, y, z; char c;
            cin>>x>> y>> z >> c;
            groups[x + y].push_back({x, y, z, c});
        }

        long long meetings = 0;
        for (auto group : groups) {
            vector<Drone> d = group.second;

            sort(d.begin(), d.end(), [](Drone a, Drone b) {return a.x < b.x;});
            map<int, int> count;
            int total = 0;
            int left = 0;

            for (int i = 0; i < (int)d.size(); i++) {
                while (left<i && d[left].x <= d[i].x-k) {
                    if (d[left].c == 'E') {
                        count[d[left].z]--;
                        total--;
                    }
                    left++;
                }
                if (d[i].c == 'N') meetings += total-count[d[i].z];
                else {
                    count[d[i].z]++;
                    total++;
                }
            }
        }
        long long answer = (long long) n*k - meetings;
        cout << answer << '\n';
    }
}