#include <bits/stdc++.h>
using namespace std;
#define int long long


vector<vector<int>> child(10005); // store the children of the i'th node
vector<int> depth_num_nodes(1005); // store the number of nodes on the i'th layer
int N, M, K;

void dfs(int u, int depth) {
	if (depth > M){ // max_depth is the number of semesters we have
		return;
	}
	depth_num_nodes[depth] += 1;
//	cout << "Node " << u << " is increasing depth at " << depth << " by 1\n";
	for (int v : child[u]) {
	//	cout << "V is " << v << '\n';
		if (v != 0) dfs(v, depth+1);
    }
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);



int T; cin >> T;


while (T--){
	child = vector<vector<int>>(10005);
	depth_num_nodes = vector<int>(1005);
	
	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++){
		int p; cin >> p;
		child[p].push_back(i);
	//	cout << child[p][0] << '\n';
	}
	
	dfs(0, 0);
	
	int rem = 0;
	int total = 0;
	
	for (int i = 1; i <= M; i++){
		int depth_count = depth_num_nodes[i]; // number of nodes on layer
//		cout << "Count for layer " << i << " is " << depth_count << '\n';
		rem += depth_count;
		if (rem > K){
			rem -= K;
			total += K;
		}
		else{
			total += rem;
			rem = 0;
		}
	}
	
	cout << total << '\n';
}






	return 0;
}
