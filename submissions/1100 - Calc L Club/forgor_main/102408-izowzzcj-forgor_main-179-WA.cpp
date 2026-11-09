#include <iostream>
#include <vector>
#include <utility>
#include <numeric>
#include <algorithm>

using namespace std;

long long from_bits(const vector<int>& bitstring) {
    long long value = 0;
    for (int i = 0; i < bitstring.size(); i++) {
        value <<= 1;
        value += bitstring[i];
    }
    return value;
}

void search(int current, const vector<vector<int>>& neighbors, vector<int>& parent, vector<bool>& visited) {
    visited[current] = true;
    for (int neighbor: neighbors[current]) {
        if (visited[neighbor]) continue;
        parent[neighbor] = current;
        search(neighbor, neighbors, parent, visited);
    }
}

vector<int> make_list(const vector<vector<int>>& neighbors) {
    vector<int> parent(neighbors.size(), 0);
    vector<bool> visited(neighbors.size(), false);
    search(0, neighbors, parent, visited);
    long long sum = accumulate(parent.begin(), parent.end(), 0LL);
    vector<int> list;
    if (sum <= 1000000) {
        for (int i = 1; i < parent.size(); i++) {
            list.push_back(parent[i]);
        }
        list.push_back(sum);
        return list;
    }
    vector<int> bitstring;
    while (sum != 0) {
        bitstring.push_back(sum & 1);
        sum >>= 1;
    }
    reverse(bitstring.begin(), bitstring.end());
    vector<int> extra_bit_values;
    int extra_bits = extra_bit_values.size() - 19;
    extra_bit_values.push_back(1);
    for (int i = 1; i < bitstring.size() - 18; i++) {
        extra_bit_values.push_back(2 * bitstring[i - 1] + bitstring[i]);
    }
    long long last = from_bits(vector<int>(bitstring.end() - 19, bitstring.end()));
    for (int i = 1; i < parent.size() - extra_bit_values.size(); i++) {
        list.push_back(parent[i]);
    }
    int index = 0;
    for (int i = parent.size() - extra_bit_values.size(); i < parent.size(); i++) {
        list.push_back(extra_bit_values[index] * 200000 + parent[i]);
        index++;
    }
    list.push_back(last);
    return list;
}

vector<pair<int, int>> reconstruct(int num_nodes, vector<int>& list) {
    if (list.back() != -1) {
        long long sum = 0;
        vector<int> bitstring(list.size() - 1);
        int negative_index = list.size() - 1;
        for (int i = 0; i < list.size() - 1; i++) {
            if (list[i] == -1) {
                negative_index = i;
                continue;
            }
            sum += list[i] % 200000;
            int bits = list[i] / 200000;
            bitstring[i] = bits & 1;
            if (i - 1 == negative_index) bitstring[i -1] = bits >> 1;
        }
        vector<int> last;
        int value = list.back();
        while (value != 0) {
            last.push_back(value & 1);
            value >>= 1;
        }
        reverse(last.begin(), last.end());
        for (int bit: last) {
            bitstring.push_back(bit);
        }
        long long expected = from_bits(bitstring);
        long long missing = expected - sum;
        list[negative_index] = missing;
    }
    vector<pair<int, int>> reconstruction;
    for (int i = 0; i < list.size() - 1; i++) {
        reconstruction.push_back({i + 2, list[i] + 1});
    }
    return reconstruction;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int num_nodes;
    string phase;
    cin >> phase >> num_nodes;
    if (phase == "FIRST") {
        int first, last;
        vector<vector<int>> neighbors(num_nodes);
        for (int i = 0; i < num_nodes - 1; i++) {
            cin >> first >> last;
            first--;
            last--;
            neighbors[first].push_back(last);
            neighbors[last].push_back(first);
        }
        vector<int> results = make_list(neighbors);
        for (int result: results) {
            cout << result << " ";
        }
        cout << "\n";
    } else {
        vector<int> list;
        int value;
        for (int i = 0; i < num_nodes; i++) {
            cin >> value;
            list.push_back(value);
        }
        vector<pair<int, int>> results = reconstruct(num_nodes, list);
        for (const pair<int, int>& result: results) {
            cout << result.first << " " << result.second << "\n";
        }
    }
    return 0;
}