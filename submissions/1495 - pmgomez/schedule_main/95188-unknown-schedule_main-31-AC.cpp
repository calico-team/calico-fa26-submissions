#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll solve() {

    ll N, M, K;
    cin >> N >> M >> K;
        
    vector<ll> numPrereq(N, 0);
    vector<vector<ll> > adjList(N);
    
    for (ll i = 0; i < N; i++) {
        ll pi; cin >> pi;
        pi--;
        if (pi != -1) {
            adjList[pi].push_back(i);
            numPrereq[i]++;
        }
    }

    queue<pair<ll, ll> > noPrereq;
    for (ll i = 0; i < N; i++) {
        if (numPrereq[i] == 0) {
            noPrereq.push({0, i});
        }
    }

    ll coursesDone = 0;

    for (ll sem = 0; sem < M; sem++) {

        ll takenRn = 0;

        while (!noPrereq.empty()) {

            if (takenRn == K) break;

            auto [minSem, u] = noPrereq.front();
            if (minSem > sem) break;
            
            noPrereq.pop();

            takenRn++;
            coursesDone++;

            for (auto &v: adjList[u]) {
                noPrereq.push({minSem+1, v});
            }

        }

    }

    return coursesDone;

}

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(false);

    ll T;
    cin >> T;

    while (T--) {

        ll res = solve();
        cout << res << endl;

    }

}