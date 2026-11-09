#include <bits/stdc++.h>
using namespace std;

const int INF= 1000000000;

int num_rows, num_cols;
vector<string> grid;

struct Query {
    int start_row, start_col, end_row, end_col, time_limit;
};
vector<Query> queries;
vector<long long> best_time;

bool is_active(char tile_char, int mode) {
    return tile_char=='.' || (tile_char== 'B' && mode==0) || (tile_char=='R' && mode== 1);
}

void solve(int left_col, int right_col, vector<int>& query_ids) {
    if (left_col> right_col || query_ids.empty()) return;

    int mid_col= (left_col+right_col) / 2;
    int width= right_col-left_col + 1;
    int total_states= num_rows*width*2;
    int num_mid_states= 2*num_rows;

    int dir_row[4]= {1, -1, 0, 0};
    int dir_col[4]= {0, 0, 1, -1};

    vector<int> dist_from_mid((size_t)total_states*num_mid_states, INF);
    {
        vector<int> dist(total_states);
        vector<int> bfs_queue(total_states);

        for (int row=0; row< num_rows; row++) {
            for (int mode= 0; mode< 2; mode++) {
                if (!is_active(grid[row][mid_col], mode)) continue;
                int mid_index= row*2 + mode;

                fill(dist.begin(), dist.end(), -1);
                int head= 0, tail=0;
                int source= (row*width + (mid_col-left_col))*2 + mode;
                dist[source]= 0;
                bfs_queue[tail++]= source;

                while (head< tail) {
                    int current= bfs_queue[head++];
                    int current_mode= current & 1;
                    int cell= current >> 1;
                    int curr_row= cell / width;
                    int curr_col= cell % width;
                    int curr_dist= dist[current];

                    for (int dir=0; dir< 4; dir++) {
                        int new_row= curr_row + dir_row[dir];
                        int new_col= curr_col+dir_col[dir];
                        if (new_row< 0 || new_row>= num_rows || new_col< 0 || new_col>= width) continue;
                        if (!is_active(grid[new_row][new_col + left_col], current_mode)) continue;
                        int neighbor_id= (new_row*width + new_col)*2 + current_mode;
                        if (dist[neighbor_id]< 0) {
                            dist[neighbor_id]= curr_dist+1;
                            bfs_queue[tail++]= neighbor_id;
                        }
                    }

                    if (grid[curr_row][curr_col + left_col]=='.') {
                        int neighbor_id= cell*2 + (1-current_mode);
                        if (dist[neighbor_id]< 0) {
                            dist[neighbor_id]= curr_dist+1;
                            bfs_queue[tail++]= neighbor_id;
                        }
                    }
                }

                for (int state=0; state< total_states; state++) {
                    if (dist[state]>= 0) dist_from_mid[(size_t)state*num_mid_states + mid_index]= dist[state];
                }
            }
        }
    }

    vector<int> left_ids, right_ids;
    for (int id : query_ids) {
        Query& query= queries[id];
        int start_state= (query.start_row*width + (query.start_col-left_col))*2 + 0;
        int end_state_blue= (query.end_row*width + (query.end_col-left_col))*2;
        int end_state_red= end_state_blue + 1;

        for (int mid_index=0; mid_index< num_mid_states; mid_index++) {
            int dist_to_start= dist_from_mid[(size_t)start_state*num_mid_states + mid_index];
            if (dist_to_start>= INF) continue;
            int dist_to_end= min(dist_from_mid[(size_t)end_state_blue*num_mid_states + mid_index], dist_from_mid[(size_t)end_state_red*num_mid_states + mid_index]);
            if (dist_to_end>= INF) continue;
            best_time[id]= min(best_time[id], (long long)dist_to_start + dist_to_end);
        }

        if (query.start_col< mid_col && query.end_col< mid_col) left_ids.push_back(id);
        else if (query.start_col> mid_col && query.end_col> mid_col) right_ids.push_back(id);
    }

    vector<int>().swap(dist_from_mid);

    solve(left_col, mid_col-1, left_ids);
    solve(mid_col+1, right_col, right_ids);
}

int main() {
    int t;
    cin>> t;
    while (t--) {
        int num_queries;
        cin>> num_rows>> num_cols>> num_queries;

        grid.assign(num_rows, "");
        for (int i=0; i< num_rows; i++) cin>> grid[i];

        queries.assign(num_queries, Query());
        best_time.assign(num_queries, LLONG_MAX);
        for (int i=0; i < num_queries; i++) {
            cin>> queries[i].start_row>> queries[i].start_col>> queries[i].end_row>> queries[i].end_col>> queries[i].time_limit;
        }

        vector<int> query_ids(num_queries);
        for (int i=0; i< num_queries; i++) query_ids[i]= i;
        solve(0, num_cols-1, query_ids);
        for (int i=0; i< num_queries; i++) {
            if (best_time[i]<= queries[i].time_limit) cout<< "YES\n";
            else cout<< "NO\n";
        }
    }
}