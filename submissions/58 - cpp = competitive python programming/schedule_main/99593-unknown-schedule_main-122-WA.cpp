#include <bits/stdc++.h>
#include <cassert>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int P[10000], dep[10000], deg[10000];
bool isleaf[10000], visited[10000];

void dfs(int node) {
    if (visited[node]) return;
    visited[node] = true;
    if (P[node] == -1) dep[node] = 0;
    else {
        dfs(P[node]);
        dep[node] = dep[P[node]] + 1;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M, K;
        cin >> N >> M >> K;
        fill(dep, dep + N, 0);
        fill(isleaf, isleaf + N, true);
        fill(visited, visited + N, false);
        set<pii> course;
        for (int i = 0; i < N; i++) {
            cin >> P[i];
            if (0 <= --P[i]) {
                isleaf[P[i]] = false;
                deg[P[i]]++;
            }
        }

        for (int i = 0; i < N; i++) {
            if (isleaf[i]) {
                dfs(i);
            }
        }
        for (int i = 0; i < N; i++){
            //cout << i + 1 << ' ' << dep[i] << ' ' << isleaf[i] << '\n';
            if (isleaf[i]){
                course.insert({dep[i], i});
            }
        }

        vector<int> pre, tmp;
        int ans = 0;

        for (int i = M - 1; i >= 0; i--) {
            while (!course.empty() && (--course.end())->first > i) {
                auto it = --course.end();
                course.insert({dep[P[it->second]], P[it->second]});
                course.erase(it);
            }
            for (int j : pre) {
                if (course.find({dep[P[j]], P[j]}) != course.end()) {
                    tmp.push_back(P[j]);
                    course.erase({dep[P[j]], P[j]});
                }
            }
            //cout << "course : ";
            //for (pii j : course) cout << '(' << j.first << ' ' << j.second + 1 << ") ";
            //cout << '\n';
            while (tmp.size() < K && !course.empty()) {
                //cout << "tmp back " << (--course.end())->first << ' ' << (--course.end())->second + 1 << '\n';
                tmp.push_back({(--course.end())->second});
                course.erase({dep[tmp.back()], tmp.back()});
            }
            for (int j : tmp) if (dep[j]) course.insert({dep[P[j]], P[j]});
            ans += tmp.size();
            swap(pre, tmp);
            tmp.clear();
            //cout << i << " : ";
            //for (int j : pre) cout << j + 1 << ' ';
            //cout << '\n';
            //cout << "course : ";
            //for (pii j : course) cout << '(' << j.first << ' ' << j.second + 1 << ") ";
            //cout << '\n';
        }

        cout << ans << '\n';
    }
}