
import sys
import math
from array import array


def find(parent, x):
    while parent[x] != x:
        parent[x] = parent[parent[x]]
        x = parent[x]
    return x


def solve():
    data = iter(map(int, sys.stdin.buffer.read().split()))

    input_data = next(data)
    output = []

    for _ in range(input_data):
        n = next(data)
        m = next(data)
        q = next(data)

        earthquakes = []

        for _ in range(q):
            r = next(data)
            c = next(data)
            p = next(data)

            earthquakes.append((r, c, p))

        # Initially, every seismometer reads zero.
        ans = [0] * (n * m)

        # Each row has its own DSU and one extra sentinel.
        width = m + 1
        next_cell = array('i', range(n * width))

        # Process earthquakes in reverse order.
        for R, C, P in reversed(earthquakes):

            p_squared = P * P

            first_row = max(0, R - P)
            last_row = min(n - 1, R + P)

            for r in range(first_row, last_row + 1):

                dy = r - R
                dx = math.isqrt(p_squared - dy * dy)

                left = C - dx
                right = C + dx

                base = r * width

                # Find the first unprocessed column.
                pos = find(next_cell, base + left)

                end = base + right

                while pos <= end:

                    c = pos - base

                    # Calculate the shock level.
                    dc = c - C

                    shock = p_squared - dy * dy - dc * dc + 1

                    ans[r * m + c] = shock

                    # Remove this column from future consideration.
                    next_cell[pos] = find(next_cell, pos + 1)

                    # Jump to the next unprocessed column.
                    pos = next_cell[pos]

        # Print the completed grid.
        for r in range(n):
            start = r * m
            output.append(
                " ".join(map(str, ans[start:start + m]))
            )

    sys.stdout.write("\n".join(output))


if __name__ == "__main__":
    solve()
