#include <bits/stdc++.h>

using namespace std;

/**
 * Return an array of Q strings, the i-th of which is "YES"
 * if Big Ben can travel from start[i] to end[i], and "NO"
 * otherwise.
 *
 * N: the number of rows in the G
 * M: the number of columns in the G
 * Q: the number of queries
 * G: the G, where each tile is 'R', 'B', or '.'
 * start: the (row, column) of the starting tile of each query
 * end: the (row, column) of the ending tile of each query
 */
vector<vector<bool>> visited;

vector<string> G;
int N, M, Q;
vector<int> parent;
vector<int> size;

void make_set(int v) {
    parent[v] = v; //root node
    size[v] = 1;
}

int find_set(int v) {
	if (v == parent[v]){
		return v;
	}
	else{
		return parent[v] = find_set(parent[v]); //flatten the tree
	}
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (size[a] < size[b]){
			parent[a] = b;
			size[b] += size[a];
		}
		else{
			parent[b] = a;
			size[a] += size[b]; //attach smaller to bigger
		}
	}
}

void BFS(int posY, int posX){
    if (visited[posY][posX]){
        return;
    }

    visited[posY][posX] = true;
    make_set(posY * M + posX); //encode position
    if (posY > 0){
        if (G[posY][posX] == '.' || G[posY-1][posX] == '.' || G[posY-1][posX] == G[posY][posX]){
            BFS(posY-1, posX);
            union_sets(posY* M + posX, (posY-1)*M + posX);
        }
    }
    if (posX > 0){
        if (G[posY][posX] == '.' || G[posY][posX-1] == '.' || G[posY][posX-1] == G[posY][posX]){
            BFS(posY, posX-1);
            union_sets(posY* M + posX, (posY)*M + posX-1);

        }
    }
    if (posX < M-1){
        if (G[posY][posX] == '.' || G[posY][posX+1] == '.' || G[posY][posX+1] == G[posY][posX]){
            BFS(posY, posX+1);
            union_sets(posY* M + posX, (posY)*M + posX+1);

        }
    }
    if (posY < N-1){
        if (G[posY][posX] == '.' || G[posY+1][posX] == '.' || G[posY+1][posX] == G[posY][posX]){
            BFS(posY+1, posX);
            union_sets(posY* M + posX, (posY+1)*M + posX);

        }
    }
    
}
 vector<string> solve(int N, int M, int Q, vector<pair<int, int>>& start, vector<pair<int, int>>& end) {
    // YOUR CODE HERE
    visited.assign(N, vector<bool>(M, false));
	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++){
			BFS(i, j);
		}
	}
    vector<string> answer;
    for (int i = 0; i < Q; i++){
        if (find_set(start[i].first * M + start[i].second) == find_set(end[i].first * M + end[i].second)){
            answer.push_back("YES");
        }
        else{
            answer.push_back("NO");
        }
    }

    return answer;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> N >> M >> Q;
        G.assign(N, "");
        parent.assign(N*M, 0);
        size.assign(N*M, 0);

        for (int j = 0; j < N; j++) {
            cin >> G[j];
        }
        vector<pair<int, int>> start, end;
        for (int j = 0; j < Q; j++) {
            int start_row, start_col, end_row, end_col;
            cin >> start_row >> start_col >> end_row >> end_col;
            start.push_back({start_row, start_col});
            end.push_back({end_row, end_col});
        }

        for (string s : solve(N, M, Q, start, end)) {
            cout << s << '\n';
        }
    }
}
