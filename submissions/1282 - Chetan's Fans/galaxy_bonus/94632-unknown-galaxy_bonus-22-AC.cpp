#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while (tests--) {
        int rows, cols, queries;
        cin >> rows >> cols >> queries;
        string grid, row;
        grid.reserve(rows * cols);
        for (int r = 0; r < rows; ++r) {
            cin >> row;
            grid += row;
        }

        vector<int> component(grid.size(), -1), queue;
        queue.reserve(grid.size());
        for (int start = 0; start < rows * cols; ++start) {
            if (component[start] != -1) continue;
            component[start] = start;
            queue.clear();
            queue.push_back(start);
            for (size_t head = 0; head < queue.size(); ++head) {
                int cell = queue[head];
                auto visit = [&](int next) {
                    if (component[next] == -1 &&
                        (grid[cell] == grid[next] || grid[cell] == '.' || grid[next] == '.')) {
                        component[next] = start;
                        queue.push_back(next);
                    }
                };
                if (cell >= cols) visit(cell - cols);
                if (cell + cols < rows * cols) visit(cell + cols);
                if (cell % cols != 0) visit(cell - 1);
                if (cell % cols != cols - 1) visit(cell + 1);
            }
        }

        while (queries--) {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            cout << (component[r1 * cols + c1] == component[r2 * cols + c2] ? "YES\n" : "NO\n");
        }
    }
}
