#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <cmath>
#include <cctype>
#include <numeric>
#include <iomanip>
#include <climits>
#include <list>
using namespace std;



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(12);

    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        int N, M, K;
        cin >> N >> M >> K;


        vector<vector<int>> adj(N + 1);
        vector<int> parent(N + 1);
        vector<int> numchild(N + 1);

        for (int i = 1; i <= N; i++) {
            cin >> parent[i];

            if (parent[i] != 0) {
                adj[parent[i]].push_back(i);
                numchild[parent[i]]++;
            }
        }

        vector<int> height(N + 1, 1);
        vector<int> st;

        for (int i = 1; i <= N; i++) {
            if (numchild[i] == 0) {
                st.push_back(i);
            }
        }

        while (!st.empty()) {
            int v = st.back();
            st.pop_back();

            int w = parent[v];
            if (w != 0) {
                height[w] = max(height[w], height[v] + 1);
                numchild[w] -= 1;
                if (numchild[w] == 0) {
                    st.push_back(w);
                }
            }
        }


        priority_queue<pair<int, int>> pq;

        for (int i = 1; i <= N; i++) {
            if (parent[i] == 0) {
                pq.push({height[i], i});
            }
        }

        int numcourses = 0;

        for (int i = 0; i < M; i++) {
            vector<int> courses_taken;

            for (int j = 0; j < K; j++) {
                if (pq.empty()) {break;}
                int w = get<1>(pq.top());
                pq.pop();

                courses_taken.push_back(w);
                numcourses += 1;
            }

            for (int w : courses_taken) {
                for (int v : adj[w]) {
                    pq.push({height[v], v});
                }
            }

            if (pq.empty()) {break;}
        }

        cout << numcourses << '\n';
    }

    return 0;
}