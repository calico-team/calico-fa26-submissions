#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

vector<int> solve_phase1(int N, vector<pair<int, int>>& E) {
    vector<vector<int>> adj(N);
    vector<int> deg(N,0);

    for(int i=0; i< N-1; i++) {
        int k = E[i].first-1;
        int y = E[i].second-1;

        adj[k].push_back(y);
        adj[y].push_back(k);
        deg[k]++;
        deg[y]++;
    }

    priority_queue<int, vector<int>, greater<int>> queue;

    for(int i = 0; i<N; i++) {
        if(deg[i] == 1) queue.push(i);
    }
    vector<int> p;

    for(int i=0; i<N-2; i++) {
        int k = queue.top();
        queue.pop();
        int y;
        for(int x: adj[k]) {
            if(deg[x] > 0) {
                y=x;
                break;
            }
        }
        p.push_back(y);
        deg[k]=0;
        deg[y]--;
        if(deg[y]==1) queue.push(y);
    }

    vector<int> a(N, 0);
    for(int i=0; i<N-2;i++) {
        a[i]=p[i];
        a[N-1] ^= p[i];
    }
    return a;
}

vector<pair<int, int>> solve_phase2(int N, vector<int>& A) {
    int missing=-1;
    for(int i=0; i<N; i++) {
        if(A[i] == -1) missing=i;
    }

    if(missing != N-1) {
        A[missing] = A[N-1];
        for(int i=0; i<N-1; i++) {
            if(i != missing) A[missing]^=A[i];
        }
    }

    vector<int> deg(N,1);
    for(int i=0; i<N-2; i++) {
        deg[A[i]]++;
    }

    priority_queue<int, vector<int>, greater<int>> queue;
    for(int i=0; i < N; i++) {
        if(deg[i] == 1) queue.push(i);
    }

    vector<pair<int, int>> edges;
    for(int i=0; i<N-2; i++) {
        int l = queue.top();
        queue.pop();

        int y = A[i];
        edges.push_back({l+1, y+1});

        deg[l]--;
        deg[y]--;
        if(deg[y] == 1) queue.push(y);
    }

    int x = queue.top();
    queue.pop();
    int y=queue.top();
    edges.push_back({x+1, y+1});

    return edges;
}

int main() {
    string phase;
    cin >> phase;
    int N;
    cin >> N;

    if (phase == "FIRST") {
        vector<pair<int, int>> E(N - 1);
        for (int i = 0; i < N - 1; i++) {
            cin >> E[i].first >> E[i].second;
        }
        vector<int> A = solve_phase1(N, E);
        for (int i = 0; i < N; i++) {
            if (i > 0) cout << ' ';
            cout << A[i];
        }
        cout << '\n';
    } else {
        vector<int> A(N);
        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }
        vector<pair<int, int>> edges = solve_phase2(N, A);
        for (auto& e : edges) {
            cout << e.first << ' ' << e.second << '\n';
        }
    }
}
