#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

struct Earthquake {
    int row, col, power;
};

int successor(vector<int>& next, int cell) {
    while (next[cell] != cell) {
        next[cell] = next[next[cell]];
        cell = next[cell];
    }
    return cell;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while (tests--) {
        int rows, cols, count;
        cin >> rows >> cols >> count;
        vector<Earthquake> earthquakes(count);
        for (auto& quake : earthquakes) cin >> quake.row >> quake.col >> quake.power;

        int stride = cols + 1;
        vector<int> reading(rows * stride), next(rows * stride);
        iota(next.begin(), next.end(), 0);
        for (int i = count - 1; i >= 0; --i) {
            auto [row, col, power] = earthquakes[i];
            int half = power;
            auto record = [&](int r, int level) {
                int center = r * stride + col;
                int end = center + half;
                for (int cell = successor(next, center - half); cell <= end; cell = next[cell]) {
                    int dx = cell - center;
                    reading[cell] = level - dx * dx;
                    next[cell] = successor(next, cell + 1);
                }
            };

            for (int dy = 0; dy <= power; ++dy) {
                int remaining = power * power - dy * dy;
                while (half * half > remaining) --half;
                record(row + dy, remaining + 1);
                if (dy != 0) record(row - dy, remaining + 1);
            }
        }
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < cols; ++c)
                cout << reading[r * stride + c] << (c + 1 == cols ? '\n' : ' ');
    }
}
