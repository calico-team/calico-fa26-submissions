#include <bits/stdc++.h>
using namespace std;
struct Edge {
	int U, V;
};
vector<int> encode(int N, const vector<Edge> &edges) {
	vector<set<int>> adjacent(N + 1);
	vector<int> degree(N + 1);
	for (const auto &edge : edges) {
		adjacent[edge.U].insert(edge.V);
		adjacent[edge.V].insert(edge.U);
		degree[edge.U]++;
		degree[edge.V]++;
	}
	set<int> leaves;
	for (int i = 0; i < N; i++) {
		if (degree[i + 1] == 1) {
			leaves.insert(i + 1);
		}
	}
	vector<int> encoded(N);
	for (int i = 0; i < N - 2; i++) {
		int leaf = *leaves.begin();
		leaves.erase(leaves.begin());
		int neighbor = *adjacent[leaf].begin();
		encoded[i] = neighbor;
		adjacent[neighbor].erase(leaf);
		degree[neighbor]--;
		if (degree[neighbor] == 1) {
			leaves.insert(neighbor);
		}
	}
	vector<int> remaining;
	for (int i = 0; i < N; i++) {
		if (degree[i + 1] > 0) {
			remaining.push_back(i);
		}
	}
	sort(remaining.begin(), remaining.end());
	encoded[N - 2] = remaining[0];
	encoded[N - 1] = remaining[1];
	return encoded;
}
vector<Edge> decode(int N, const vector<int> &encoded) {
	vector<int> degree(N + 1);
	for (int node : encoded) {
		degree[node]++;
	}
	set<int> leaves;
	for (int i = 0; i < N; i++) {
		if (degree[i + 1] == 1) {
			leaves.insert(i + 1);
		}
	}
	vector<Edge> edges(N - 1);
	for (int i = 0; i < N - 2; i++) {
		int neighbor = encoded[i];
		int leaf = *leaves.begin();
		leaves.erase(leaves.begin());
		edges[i] = {leaf, neighbor};
		degree[neighbor]--;
		if (degree[neighbor] == 1) {
			leaves.insert(neighbor);
		}
	}
	edges[N - 1] = {encoded[N - 2], encoded[N - 1]};
	return edges;
}
vector<Edge> decode_corrupted(int N, vector<int> encoded) {
	auto it = find(encoded.begin(), encoded.end(), -1);
	if (it == encoded.end()) {
		return decode(N, encoded);
	}
	int corrupted = distance(encoded.begin(), it);
	if (corrupted >= N - 2) {
		vector<int> degree(N + 1);
		for (int i = 0; i < N - 2; i++) {
			degree[encoded[i]]++;
		}
		set<int> leaves;
		for (int i = 0; i < N; i++) {
			if (degree[i + 1] == 1) {
				leaves.insert(i + 1);
			}
		}
		vector<int> curr_degree = degree;
		for (int i = 0; i < N - 2; i++) {
			int neighbor = encoded[i];
			leaves.erase(leaves.begin());
			curr_degree[neighbor]--;
			if (curr_degree[neighbor] == 1) {
				leaves.insert(neighbor);
			}
		}
		vector<int> remaining;
		for (int i = 0; i < N; i++) {
			if (curr_degree[i + 1] > 0) {
				remaining.push_back(i + 1);
			}
		}
		int other_idx = (corrupted == N - 2) ? N - 1 : N - 2;
		int known = encoded[other_idx];
		if (remaining[0] == known) {
			encoded[corrupted] = remaining[1];
		} else {
			encoded[corrupted] = remaining[0];
		}
	} else {
		int solved = -1;
		for (int guess = 1; guess <= N; guess++) {
			encoded[corrupted] = guess;
			vector<int> degree(N + 1, 1);
			for (int i = 0; i < N - 2; i++) {
				degree[encoded[i]]++;
			}
			set<int> leaves;
			for (int i = 0; i < N; i++) {
				if (degree[i + 1] == 1) {
					leaves.insert(i + 1);
				}
			}
			bool valid = true;
			vector<int> curr_degree = degree;
			for (int i = 0; i < N - 2; i++) {
				if (leaves.empty()) {
					valid = false;
					break;
				}
				int leaf = *leaves.begin();
				leaves.erase(leaves.begin());
                int neighbor = encoded[i];
                curr_degree[neighbor]--;
                if (curr_degree[neighbor] == 1) {
                    leaves.insert(neighbor);
                }
			}
			if (valid) {
				std::vector<int> final_nodes;
                for (int i = 1; i <= N; ++i) {
                    if (curr_degree[i] == 1) final_nodes.push_back(i);
                }
                if (final_nodes.size() == 2) {
                    std::vector<int> expected = {encoded[N - 2], encoded[N - 1]};
                    std::sort(final_nodes.begin(), final_nodes.end());
                    std::sort(expected.begin(), expected.end());
                    if (final_nodes == expected) {
                        solved = guess;
                        break;
                    }
                }
			}
		}
		encoded[corrupted] = solved;
	}
	return decode(N, encoded);
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	string curr;
	cin >> curr;
	if (curr == "FIRST") {
		int N;
		cin >> N;
		vector<Edge> edges(N - 1);
		for (int i = 0; i < N - 1; i++) cin >> edges[i].U >> edges[i].V;
		for (int i : encode(N, edges)) {
			cout << i << " ";
		}
	} else {
		int N;
		cin >> N;
		vector<int> encoded(N);
		for (int i = 0; i < N; i++) cin >> encoded[i];
		vector<Edge> edges = decode_corrupted(N, encoded);
		for (const auto &edge : edges) {
			cout << edge.U << " " << edge.V << "\n";
		}
	}
}