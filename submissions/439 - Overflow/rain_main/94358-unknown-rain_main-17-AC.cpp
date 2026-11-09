#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

struct AerialUnit {
    int u, v;
    char heading;
};

void evaluate_campaign() {
    int fleet_count;
    long long mission_horizon;
    if (!(std::cin >> fleet_count >> mission_horizon)) return;

    // Group drone x-coordinates by their anti-diagonal invariant S = X + Y
    constexpr int MAX_DIAG = 200000 + 7;
    static std::vector<int> east_tracks[MAX_DIAG];
    static std::vector<int> north_tracks[MAX_DIAG];
    std::vector<int> active_diagonals;
    active_diagonals.reserve(fleet_count);

    for (int idx = 0; idx < fleet_count; ++idx) {
        int x, y, z;
        char dir;
        std::cin >> x >> y >> z >> dir;

        const int diag = x + y;
        if (dir == 'E') {
            east_tracks[diag].push_back(x);
        } else {
            north_tracks[diag].push_back(x);
        }
        active_diagonals.push_back(diag);
    }

    // Retain only unique anti-diagonals that contain at least one drone
    std::sort(active_diagonals.begin(), active_diagonals.end());
    active_diagonals.erase(std::unique(active_diagonals.begin(), active_diagonals.end()), active_diagonals.end());

    long long blocked_opportunities = 0;

    for (int d : active_diagonals) {
        auto& e_vec = east_tracks[d];
        auto& n_vec = north_tracks[d];

        if (!e_vec.empty() && !n_vec.empty()) {
            std::sort(e_vec.begin(), e_vec.end());
            std::sort(n_vec.begin(), n_vec.end());

            // Sliding two-pointer interval [win_lo, win_hi) over northbound units
            auto win_lo = n_vec.begin();
            auto win_hi = n_vec.begin();

            for (int xe : e_vec) {
                while (win_lo != n_vec.end() && *win_lo < xe) {
                    ++win_lo;
                }
                while (win_hi != n_vec.end() && *win_hi < xe + mission_horizon) {
                    ++win_hi;
                }
                blocked_opportunities += std::distance(win_lo, win_hi);
            }
        }

        e_vec.clear();
        n_vec.clear();
    }

    const long long gross_capacity = static_cast<long long>(fleet_count) * mission_horizon;
    const long long net_collection = gross_capacity - blocked_opportunities;

    std::cout << net_collection << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int test_rounds;
    if (std::cin >> test_rounds) {
        while (test_rounds--) {
            evaluate_campaign();
        }
    }
    return 0;
}