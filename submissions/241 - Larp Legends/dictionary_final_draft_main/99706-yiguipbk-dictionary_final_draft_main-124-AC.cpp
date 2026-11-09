#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

const int BITS = 30;

// binary trie that finds the max xor with a number
struct XorTrie {
    // node 0 is the root and 0 also means no child
    vector<array<int, 2>> children;
    // how many stored numbers go through each node
    vector<int> pass_count;

    XorTrie() { reset(); }

    // clear the trie but keep the memory for reuse
    void reset() {
        children.clear();
        pass_count.clear();
        children.push_back({0, 0});
        pass_count.push_back(0);
    }

    int new_node() {
        children.push_back({0, 0});
        pass_count.push_back(0);
        return (int)children.size() - 1;
    }

    void update(int number, int change) {
        int node = 0;
        pass_count[node] += change;
        for (int bit_position = BITS - 1; bit_position >= 0; --bit_position) {
            int bit = (number >> bit_position) & 1;
            if (children[node][bit] == 0) {
                int created = new_node();  // may reallocate, so assign after
                children[node][bit] = created;
            }
            node = children[node][bit];
            pass_count[node] += change;
        }
    }

    void add(int number) { update(number, +1); }
    void remove(int number) { update(number, -1); }

    int max_xor_with(int number) const {
        int node = 0;
        int best = 0;
        for (int bit_position = BITS - 1; bit_position >= 0; --bit_position) {
            int bit = (number >> bit_position) & 1;
            // going the opposite way sets this bit of the xor
            int wanted_child = children[node][1 - bit];
            if (wanted_child != 0 && pass_count[wanted_child] > 0) {
                best |= 1 << bit_position;
                node = wanted_child;
            } else {
                node = children[node][bit];
            }
        }
        return best;
    }
};

// each word points to one word so the graph is cycles with trees on them
void find_cycles(int word_count, const vector<int>& next_word,
                 vector<vector<int>>& cycles, vector<char>& is_on_cycle) {
    const char unvisited = 0, in_current_walk = 1, finished = 2;
    vector<char> status(word_count, unvisited);
    is_on_cycle.assign(word_count, false);
    cycles.clear();

    vector<int> walk;
    for (int start = 0; start < word_count; ++start) {
        if (status[start] != unvisited) continue;

        walk.clear();
        int word = start;
        while (status[word] == unvisited) {
            status[word] = in_current_walk;
            walk.push_back(word);
            word = next_word[word];
        }

        // we hit our own walk so this is a new cycle
        if (status[word] == in_current_walk) {
            auto it = find(walk.begin(), walk.end(), word);
            vector<int> cycle(it, walk.end());
            for (int cycle_word : cycle) is_on_cycle[cycle_word] = true;
            cycles.push_back(std::move(cycle));
        }

        for (int walked_word : walk) status[walked_word] = finished;
    }
}

vector<int> solve_test_case(int word_count, const vector<int>& next_word,
                            const vector<int>& value, XorTrie& trie) {
    vector<vector<int>> cycles;
    vector<char> is_on_cycle;
    find_cycles(word_count, next_word, cycles, is_on_cycle);

    // tree words that point straight to each word
    vector<vector<int>> tree_words_pointing_to(word_count);
    for (int word = 0; word < word_count; ++word)
        if (!is_on_cycle[word])
            tree_words_pointing_to[next_word[word]].push_back(word);

    vector<int> answer(word_count, 0);

    // stopping just before a later word p gives key[word] ^ key[p]
    vector<int> key(word_count, 0);

    vector<pair<int, int>> stack;
    for (const auto& cycle : cycles) {
        // prefix_xor[k] is the xor of the cycle values up to k
        vector<int> prefix_xor;
        prefix_xor.reserve(cycle.size());
        int running_xor = 0;
        for (int cycle_word : cycle) {
            running_xor ^= value[cycle_word];
            prefix_xor.push_back(running_xor);
        }
        int full_lap_xor = running_xor;

        // all stopping points on the cycle
        // the full lap version covers going around again
        trie.reset();
        for (int prefix : prefix_xor) {
            trie.add(prefix);
            trie.add(prefix ^ full_lap_xor);
        }

        for (size_t position = 0; position < cycle.size(); ++position) {
            int entry_word = cycle[position];
            int entry_offset = position > 0 ? prefix_xor[position - 1] : 0;
            key[entry_word] = entry_offset;
            answer[entry_word] = trie.max_xor_with(entry_offset);

            // walk the tree that leads into entry_word
            // the trie holds the cycle values plus the keys on the path to the cycle
            trie.add(key[entry_word]);
            // stack items are a word and the next child to visit
            stack.clear();
            stack.push_back({entry_word, 0});
            while (!stack.empty()) {
                int word = stack.back().first;
                int child_index = stack.back().second;
                const auto& children = tree_words_pointing_to[word];

                if (child_index == (int)children.size()) {
                    // done with this word so take its key out
                    trie.remove(key[word]);
                    stack.pop_back();
                    continue;
                }

                stack.back().second = child_index + 1;
                int child = children[child_index];
                key[child] = value[child] ^ key[word];
                answer[child] = trie.max_xor_with(key[child]);
                trie.add(key[child]);
                stack.push_back({child, 0});
            }
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    if (!(cin >> test_count)) return 0;

    XorTrie trie;
    string output;
    for (int t = 0; t < test_count; ++t) {
        int word_count;
        cin >> word_count;

        // words are 0 based here
        vector<int> next_word(word_count);
        for (int& x : next_word) { cin >> x; --x; }

        vector<int> value(word_count);
        for (int& x : value) cin >> x;

        vector<int> answer = solve_test_case(word_count, next_word, value, trie);
        for (int i = 0; i < word_count; ++i) {
            if (i) output += ' ';
            output += to_string(answer[i]);
        }
        output += '\n';
    }

    cout << output;
    return 0;
}