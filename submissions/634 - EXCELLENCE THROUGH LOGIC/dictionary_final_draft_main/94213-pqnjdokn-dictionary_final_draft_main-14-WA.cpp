#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    int next_bit[2] = {0, 0};
    int total_nodes = 0;
};

struct AdvancedTrie {
    vector<TrieNode> nodes_pool;

    AdvancedTrie(int total_capacity) {
        nodes_pool.reserve(total_capacity);
        nodes_pool.push_back(TrieNode());
    }

    int append_num(int base_root, int target_val) {
        int fresh_root = (int)nodes_pool.size();
        nodes_pool.push_back(nodes_pool[base_root]);
        nodes_pool[fresh_root].total_nodes++;

        int source_curr = base_root;
        int target_curr = fresh_root;

        for (int i = 29; i >= 0; i--) {
            int bit_side = (target_val >> i) & 1;

            int link_old = nodes_pool[source_curr].next_bit[bit_side];
            int link_new = (int)nodes_pool.size();

            nodes_pool.push_back(nodes_pool[link_old]);
            nodes_pool[link_new].total_nodes++;

            nodes_pool[target_curr].next_bit[bit_side] = link_new;

            source_curr = link_old;
            target_curr = link_new;
        }

        return fresh_root;
    }

    int fetch_max_xor(int start_root, int end_root, int base_xor) {
        int max_res = 0;

        for (int i = 29; i >= 0; i--) {
            int active_bit = (base_xor >> i) & 1;
            int optimal_bit = active_bit ^ 1;

            int left_path = nodes_pool[start_root].next_bit[optimal_bit];
            int right_path = nodes_pool[end_root].next_bit[optimal_bit];

            if (nodes_pool[right_path].total_nodes - nodes_pool[left_path].total_nodes > 0) {
                max_res |= (1 << i);
                start_root = left_path;
                end_root = right_path;
            } else {
                start_root = nodes_pool[start_root].next_bit[active_bit];
                end_root = nodes_pool[end_root].next_bit[active_bit];
            }
        }

        return max_res;
    }
};

void execute_solver();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    execute_solver();

    return 0;
}

void execute_solver() {
    int total_tasks;
    cin >> total_tasks;

    while (total_tasks--) {
        int element_count;
        cin >> element_count;

        vector<int> target_link(element_count);
        vector<int> element_weight(element_count);
        vector<int> incoming_edges(element_count, 0);
        vector<int> optimal_score(element_count, 0);

        for (int idx = 0; idx < element_count; idx++) {
            cin >> target_link[idx];
            --target_link[idx];
            incoming_edges[target_link[idx]]++;
        }

        for (int idx = 0; idx < element_count; idx++) {
            cin >> element_weight[idx];
        }

        queue<int> zero_in_nodes;
        vector<int> topo_sequence;

        for (int idx = 0; idx < element_count; idx++) {
            if (incoming_edges[idx] == 0) {
                zero_in_nodes.push(idx);
            }
        }

        while (!zero_in_nodes.empty()) {
            int active_node = zero_in_nodes.front();
            zero_in_nodes.pop();

            topo_sequence.push_back(active_node);

            int linked_dest = target_link[active_node];
            incoming_edges[linked_dest]--;

            if (incoming_edges[linked_dest] == 0) {
                zero_in_nodes.push(linked_dest);
            }
        }

        vector<bool> process_status(element_count, false);
        int component_counter = 0;

        for (int idx = 0; idx < element_count; idx++) {
            if (incoming_edges[idx] == 0 || process_status[idx]) {
                continue;
            }

            vector<int> graph_cycle;
            int curr_track = idx;

            while (!process_status[curr_track]) {
                process_status[curr_track] = true;
                graph_cycle.push_back(curr_track);
                curr_track = target_link[curr_track];
            }

            int len_cycle = (int)graph_cycle.size();
            int combined_xor = 0;

            for (int component : graph_cycle) {
                combined_xor ^= element_weight[component];
            }

            int boundary = combined_xor == 0 ? len_cycle : 2 * len_cycle;
            vector<int> xor_prefix(boundary + 1, 0);

            for (int step = 0; step < boundary; step++) {
                xor_prefix[step + 1] = xor_prefix[step] ^ element_weight[graph_cycle[step % len_cycle]];
            }

            AdvancedTrie trie_instance((boundary + 2) * 31 + 1);
            vector<int> step_roots(boundary + 2, 0);

            for (int step = 0; step <= boundary; step++) {
                step_roots[step + 1] = trie_instance.append_num(step_roots[step], xor_prefix[step]);
            }

            for (int step = 0; step < len_cycle; step++) {
                optimal_score[graph_cycle[step]] = trie_instance.fetch_max_xor(
                    step_roots[step],
                    step_roots[step + boundary + 1],
                    xor_prefix[step]
                );
            }

            component_counter++;
        }

        for (int idx = (int)topo_sequence.size() - 1; idx >= 0; idx--) {
            int active_node = topo_sequence[idx];
            int linked_dest = target_link[active_node];

            optimal_score[active_node] = max(
                element_weight[active_node],
                element_weight[active_node] ^ optimal_score[linked_dest]
            );
        }

        for (int idx = 0; idx < element_count; idx++) {
            if (idx > 0) cout << ' ';
            cout << optimal_score[idx];
        }
        cout << '\n';
    }
}
