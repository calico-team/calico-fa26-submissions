#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Query {
    int start, end, limit;
    bool normalEnd;
};

class Galaxy {
    int stride;
    vector<array<int, 5>> edges;
    vector<int> degree, distance, queue;
    vector<Query> queries;
    vector<int> pending;
    vector<char> answer;

    void addEdge(int a, int b) {
        edges[a][degree[a]++] = b;
        edges[b][degree[b]++] = a;
    }

    void search(int source, int low, int high) {
        fill(distance.begin() + low, distance.begin() + high, -1);
        int tail = 0;
        queue[tail++] = source;
        distance[source] = 0;
        for (int head = 0; head < tail; ++head) {
            int current = queue[head];
            int nextDistance = distance[current] + 1;
            for (int i = 0; i < degree[current]; ++i) {
                int next = edges[current][i];
                if (next < low || next >= high || distance[next] != -1) continue;
                distance[next] = nextDistance;
                queue[tail++] = next;
            }
        }
    }

    void solve(int left, int right, int begin, int end) {
        if (begin == end) return;
        int mid = (left + right) / 2;
        int cut = mid * stride;
        for (int source = cut; source < cut + stride && begin < end; ++source) {
            if (degree[source] == 0) continue;
            search(source, left * stride, (right + 1) * stride);
            for (int i = begin; i < end;) {
                int id = pending[i];
                const auto& query = queries[id];
                int a = distance[query.start], b = distance[query.end];
                if (query.normalEnd) {
                    int other = distance[query.end + 1];
                    if (other >= 0 && (b < 0 || other < b)) b = other;
                }
                if (a >= 0 && b >= 0 && a + b <= query.limit) {
                    answer[id] = true;
                    pending[i] = pending[--end];
                } else {
                    ++i;
                }
            }
        }

        auto first = pending.begin() + begin;
        auto last = pending.begin() + end;
        auto leftEnd = partition(first, last, [&](int id) {
            return max(queries[id].start, queries[id].end) < cut;
        });
        auto rightEnd = partition(leftEnd, last, [&](int id) {
            return min(queries[id].start, queries[id].end) >= cut + stride;
        });
        if (left < mid) solve(left, mid - 1, begin, leftEnd - pending.begin());
        if (mid < right) solve(mid + 1, right, leftEnd - pending.begin(), rightEnd - pending.begin());
    }

public:
    explicit Galaxy(const vector<string>& grid)
        : stride(2 * grid.size()), edges(stride * grid[0].size()), degree(edges.size()),
          distance(edges.size()), queue(edges.size()) {
        int rows = grid.size(), cols = grid[0].size();
        for (int c = 0; c < cols; ++c) {
            for (int r = 0; r < rows; ++r) {
                char tile = grid[r][c];
                int cell = c * stride + 2 * r;
                if (tile == '.') addEdge(cell, cell + 1);
                for (int mode = 0; mode < 2; ++mode) {
                    char color = mode == 0 ? 'B' : 'R';
                    if (tile != '.' && tile != color) continue;
                    if (r + 1 < rows && (grid[r + 1][c] == '.' || grid[r + 1][c] == color))
                        addEdge(cell + mode, cell + 2 + mode);
                    if (c + 1 < cols && (grid[r][c + 1] == '.' || grid[r][c + 1] == color))
                        addEdge(cell + mode, cell + stride + mode);
                }
            }
        }
    }

    void answerQueries(const vector<string>& grid, int count) {
        queries.resize(count);
        answer.resize(count);
        pending.reserve(count);
        for (int i = 0; i < count; ++i) {
            int r1, c1, r2, c2, limit;
            cin >> r1 >> c1 >> r2 >> c2 >> limit;
            char target = grid[r2][c2];
            queries[i] = {c1 * stride + 2 * r1, c2 * stride + 2 * r2 + (target == 'R'),
                          limit, target == '.'};
            if (r1 == r2 && c1 == c2)
                answer[i] = true;
            else if (abs(r1 - r2) + abs(c1 - c2) <= limit)
                pending.push_back(i);
        }

        solve(0, grid[0].size() - 1, 0, pending.size());
        for (bool yes : answer) cout << (yes ? "YES\n" : "NO\n");
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while (tests--) {
        int rows, cols, count;
        cin >> rows >> cols >> count;
        vector<string> grid(rows);
        for (auto& row : grid) cin >> row;
        Galaxy galaxy(grid);
        galaxy.answerQueries(grid, count);
    }
}
