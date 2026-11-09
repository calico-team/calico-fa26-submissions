#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// largest w with w * w <= number
int integer_sqrt(int number) {
    int root = (int)sqrt((double)number);
    // fix any rounding from the floating point sqrt
    while (root * root > number) --root;
    while ((root + 1) * (root + 1) <= number) ++root;
    return root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    if (!(cin >> test_count)) return 0;

    string output;
    vector<int> reading;
    vector<int> next_open;
    vector<int> quake_row, quake_column, quake_power;

    for (int t = 0; t < test_count; ++t) {
        int row_count, column_count, quake_count;
        cin >> row_count >> column_count >> quake_count;

        quake_row.resize(quake_count);
        quake_column.resize(quake_count);
        quake_power.resize(quake_count);
        for (int i = 0; i < quake_count; ++i) {
            cin >> quake_row[i] >> quake_column[i] >> quake_power[i];
        }

        reading.assign((size_t)row_count * column_count, 0);

        // next_open[row][column] points to the first unfilled column at or after column
        // column_count is a sentinel that means the rest of the row is filled
        int stride = column_count + 1;
        next_open.resize((size_t)row_count * stride);
        for (int row = 0; row < row_count; ++row) {
            for (int column = 0; column <= column_count; ++column) {
                next_open[(size_t)row * stride + column] = column;
            }
        }

        auto find_open = [&](int row, int column) {
            int* row_start = next_open.data() + (size_t)row * stride;
            // jump ahead and shorten the path while we go
            while (row_start[column] != column) {
                row_start[column] = row_start[row_start[column]];
                column = row_start[column];
            }
            return column;
        };

        // a block only keeps the last quake that reached it
        // so go from the newest quake to the oldest and fill each block once
        for (int i = quake_count - 1; i >= 0; --i) {
            int center_row = quake_row[i];
            int center_column = quake_column[i];
            int power = quake_power[i];
            int power_squared = power * power;

            // the circle always fits inside the grid
            for (int row = center_row - power; row <= center_row + power; ++row) {
                int row_offset = row - center_row;
                int left_over = power_squared - row_offset * row_offset;
                int half_width = integer_sqrt(left_over);
                int last_column = center_column + half_width;

                int column = find_open(row, center_column - half_width);
                while (column <= last_column) {
                    int column_offset = column - center_column;
                    reading[(size_t)row * column_count + column] =
                        left_over - column_offset * column_offset + 1;
                    // mark it filled by pointing past it
                    next_open[(size_t)row * stride + column] = column + 1;
                    column = find_open(row, column + 1);
                }
            }
        }

        // write the grid out
        char buffer[16];
        for (int row = 0; row < row_count; ++row) {
            for (int column = 0; column < column_count; ++column) {
                if (column) output += ' ';
                int value = reading[(size_t)row * column_count + column];
                int length = 0;
                do {
                    buffer[length++] = char('0' + value % 10);
                    value /= 10;
                } while (value);
                while (length) output += buffer[--length];
            }
            output += '\n';
        }
    }

    cout << output;
    return 0;
}