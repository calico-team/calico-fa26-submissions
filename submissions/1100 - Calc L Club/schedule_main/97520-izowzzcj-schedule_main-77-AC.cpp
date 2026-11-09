#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

void find_root(int current, const vector<int>& backward_neighbor, unordered_set<int>& roots) {
    if (backward_neighbor[current] == -1) {
        roots.insert(current);
        return;
    }
    find_root(backward_neighbor[current], backward_neighbor, roots);
}

void search(int current, const vector<vector<int>>& neighbors, vector<int>& weights, int current_depth, int max_depth) {
    if (neighbors[current].size() == 0 || current_depth >= max_depth) {
        weights[current] = 0;
        return;
    }
    int weight = 0;
    for (int neighbor: neighbors[current]) {
        search(neighbor, neighbors, weights, current_depth + 1, max_depth);
        weight += weights[neighbor] + 1;
    }
    weights[current] = weight;
}

int max_semesters(int num_semesters, int max_classes, const vector<int>& backward_neighbor, const vector<vector<int>>& neighbors) {
    unordered_set<int> roots;
    for (int i = 0; i < backward_neighbor.size(); i++) {
        find_root(i, backward_neighbor, roots);
    }
    vector<int> weights(backward_neighbor.size(), 0);
    for (int root: roots) {
        search(root, neighbors, weights, 0, num_semesters);
    }
    int classes = 0;
    priority_queue available([&](const int& a, const int& b) {return weights[a] < weights[b];}, vector<int>(roots.begin(), roots.end()));
    for (int i = 0; i < num_semesters; i++) {
        vector<int> now_available;
        int used = 0;
        while (used < max_classes && !available.empty()) {
            int best = available.top();
            for (int next: neighbors[best]) {
                now_available.push_back(next);
            }
            available.pop();
            classes++;
            used++;
        }
        for (int new_class: now_available) {
            available.push(new_class);
        }
    }
    return classes;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int num_testcases, num_classes, num_semesters, max_classes, neighbor;
    cin >> num_testcases;
    while (num_testcases--) {
        cin >> num_classes >> num_semesters >> max_classes;
        vector<int> backward_neighbor(num_classes);
        vector<vector<int>> neighbors(num_classes);
        for (int i = 0; i < num_classes; i++) {
            cin >> neighbor;
            neighbor--;
            backward_neighbor[i] = neighbor;
            if (neighbor == -1) continue;
            neighbors[neighbor].push_back(i);
        }
        int result = max_semesters(num_semesters, max_classes, backward_neighbor, neighbors);
        cout << result << "\n";
    }
    return 0;
}