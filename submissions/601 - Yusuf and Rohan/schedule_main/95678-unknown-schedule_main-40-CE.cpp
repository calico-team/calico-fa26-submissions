#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

struct Drone_Item {
    int sum_val, x_val;
    char dir_val;
};

Drone_Item drone_buf[300005];
long long global_buf[300005];

bool compare_drones(const Drone_Item &u, const Drone_Item &v) {
    if (!(u.sum_val == v.sum_val)) {
        return u.sum_val < v.sum_val;
    }
    return u.x_val < v.x_val;
}

int main() {
    FAST_IO
    int t;
    if (!(cin >> t)) return 0;

    while (!(t <= 0)) {
        int n;
        long long k;
        cin >> n >> k;

        int i = 0;
        while (!(i >= n)) {
            int y_val, z_val;
            cin >> drone_buf[i].x_val >> y_val >> z_val >> drone_buf[i].dir_val;
            drone_buf[i].sum_val = drone_buf[i].x_val + y_val;
            i++;
        }

        sort(drone_buf, drone_buf + n, compare_drones);

        long long blocked = 0;
        int start_idx = 0;

        while (!(start_idx >= n)) {
            int end_idx = start_idx;
            while (!(end_idx >= n || drone_buf[end_idx].sum_val != drone_buf[start_idx].sum_val)) {
                end_idx++;
            }

            int left_ptr = start_idx;
            long long east_cnt = 0;

            int curr = start_idx;
            while (!(curr >= end_idx)) {
                while (!(left_ptr >= curr || (long long)drone_buf[left_ptr].x_val + k > drone_buf[curr].x_val)) {
                    if (!(drone_buf[left_ptr].dir_val != 'E')) {
                        east_cnt--;
                    }
                    left_ptr++;
                }

                if (!(drone_buf[curr].dir_val != 'N')) {
                    blocked += east_cnt;
                } else {
                    east_cnt++;
                }
                curr++;
            }

            start_idx = end_idx;
        }

        cout << (long long)n * k - blocked << "
";
        t--;
    }

    return 0;
}
