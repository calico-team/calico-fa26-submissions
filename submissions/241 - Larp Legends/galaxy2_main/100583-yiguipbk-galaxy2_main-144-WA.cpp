#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int INF = 1000000000;
const int BLUE = 0, RED = 1;

int row_count, column_count;
vector<string> grid;

// one search from a start state in blue mode to an end tile
// a red start becomes one search per blue neighbour that costs 1 more
struct Query {
    int start_row, start_column;
    int end_row, end_column;
    int extra_time;
    int owner;
    int best_time;
};
vector<Query> queries;

// distances from every source on the middle column
// laid out as source, then row, then column inside the range, then mode
vector<int> distances;
vector<int> bfs_queue;

bool is_active(int row, int column, int mode) {
    char tile = grid[row][column];
    if (tile == '.') return true;
    if (tile == 'B') return mode == BLUE;
    return mode == RED;
}

// bfs from one source but only using columns from left to right
void bfs(int left, int right, int source_row, int source_column, int source_mode, int* dist) {
    int width = right - left + 1;
    int state_count = row_count * width * 2;
    fill(dist, dist + state_count, INF);

    // a state is (row * width + column - left) * 2 + mode
    auto state_of = [&](int row, int column, int mode) {
        return (row * width + (column - left)) * 2 + mode;
    };

    bfs_queue.clear();
    int source = state_of(source_row, source_column, source_mode);
    dist[source] = 0;
    bfs_queue.push_back(source);

    const int row_step[4] = {1, -1, 0, 0};
    const int column_step[4] = {0, 0, 1, -1};

    for (size_t head = 0; head < bfs_queue.size(); ++head) {
        int state = bfs_queue[head];
        int mode = state & 1;
        int cell = state >> 1;
        int row = cell / width;
        int column = cell % width + left;
        int next_dist = dist[state] + 1;

        // walk to a neighbour that is active in the same mode
        for (int direction = 0; direction < 4; ++direction) {
            int next_row = row + row_step[direction];
            int next_column = column + column_step[direction];
            if (next_row < 0 || next_row >= row_count) continue;
            if (next_column < left || next_column > right) continue;
            if (!is_active(next_row, next_column, mode)) continue;
            int next_state = state_of(next_row, next_column, mode);
            if (dist[next_state] == INF) {
                dist[next_state] = next_dist;
                bfs_queue.push_back(next_state);
            }
        }

        // spin on a normal tile to swap the mode
        if (grid[row][column] == '.') {
            int next_state = state ^ 1;
            if (dist[next_state] == INF) {
                dist[next_state] = next_dist;
                bfs_queue.push_back(next_state);
            }
        }
    }
}

// answer every query whose start and end both lie in columns left to right
// a best path either touches the middle column or stays fully on one side
void solve_range(int left, int right, vector<int>& query_ids) {
    if (left > right || query_ids.empty()) return;

    int middle = (left + right) / 2;
    int width = right - left + 1;
    int state_count = row_count * width * 2;

    // every active state on the middle column is a source
    // moves and spins can be undone so distances work both ways
    int source_count = 0;
    for (int row = 0; row < row_count; ++row) {
        for (int mode = 0; mode < 2; ++mode) {
            if (!is_active(row, middle, mode)) continue;
            int* dist = distances.data() + (size_t)source_count * state_count;
            bfs(left, right, row, middle, mode, dist);
            ++source_count;
        }
    }

    for (int id : query_ids) {
        Query& query = queries[id];
        int start_state = (query.start_row * width + (query.start_column - left)) * 2 + BLUE;
        int end_cell = (query.end_row * width + (query.end_column - left)) * 2;

        for (int source = 0; source < source_count; ++source) {
            int* dist = distances.data() + (size_t)source * state_count;
            int to_start = dist[start_state];
            if (to_start == INF) continue;
            // the end can be reached in either mode
            int to_end = min(dist[end_cell + BLUE], dist[end_cell + RED]);
            if (to_end == INF) continue;
            query.best_time = min(query.best_time, to_start + to_end);
        }
    }

    // queries fully on one side might still have a shorter path on that side
    vector<int> left_ids, right_ids;
    for (int id : query_ids) {
        const Query& query = queries[id];
        if (query.start_column < middle && query.end_column < middle) left_ids.push_back(id);
        else if (query.start_column > middle && query.end_column > middle) right_ids.push_back(id);
    }
    query_ids.clear();
    query_ids.shrink_to_fit();

    solve_range(left, middle - 1, left_ids);
    solve_range(middle + 1, right, right_ids);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    if (!(cin >> test_count)) return 0;

    string output;
    for (int t = 0; t < test_count; ++t) {
        int query_count;
        cin >> row_count >> column_count >> query_count;

        grid.assign(row_count, "");
        for (int row = 0; row < row_count; ++row) cin >> grid[row];

        const int row_step[4] = {1, -1, 0, 0};
        const int column_step[4] = {0, 0, 1, -1};

        queries.clear();
        vector<int> time_limit(query_count);
        vector<int> answer_time(query_count, INF);
        for (int i = 0; i < query_count; ++i) {
            int start_row, start_column, end_row, end_column;
            cin >> start_row >> start_column >> end_row >> end_column >> time_limit[i];

            // already standing on the destination
            if (start_row == end_row && start_column == end_column) {
                answer_time[i] = 0;
                continue;
            }

            if (is_active(start_row, start_column, BLUE)) {
                queries.push_back({start_row, start_column, end_row, end_column, 0, i, INF});
                continue;
            }

            // the start should be normal but if it is red ben can only step off it
            for (int direction = 0; direction < 4; ++direction) {
                int next_row = start_row + row_step[direction];
                int next_column = start_column + column_step[direction];
                if (next_row < 0 || next_row >= row_count) continue;
                if (next_column < 0 || next_column >= column_count) continue;
                if (!is_active(next_row, next_column, BLUE)) continue;
                queries.push_back({next_row, next_column, end_row, end_column, 1, i, INF});
            }
        }

        vector<int> query_ids(queries.size());
        for (size_t i = 0; i < queries.size(); ++i) query_ids[i] = (int)i;

        // at most 2 sources per row and the top range is the widest
        distances.assign((size_t)row_count * 2 * row_count * column_count * 2, INF);

        solve_range(0, column_count - 1, query_ids);

        for (const Query& query : queries) {
            if (query.best_time == INF) continue;
            int total = query.best_time + query.extra_time;
            answer_time[query.owner] = min(answer_time[query.owner], total);
        }

        for (int i = 0; i < query_count; ++i) {
            output += answer_time[i] <= time_limit[i] ? "YES\n" : "NO\n";
        }
    }

    cout << output;
    return 0;
}