
import sys
from math import isqrt
from array import array


def solve():
    data = iter(map(int, sys.stdin.buffer.read().split()))
    t = next(data)
    results = []

    for _ in range(t):
        n = next(data)
        m = next(data)
        q = next(data)

        earthquakes = []
        for _ in range(q):
            r = next(data)
            c = next(data)
            p = next(data)
            earthquakes.append((r, c, p))

        # DSU for unassigned columns in each row.
        # Each row has m + 1 entries, with m as its sentinel.
        stride = m + 1
        parent = array('i', range(n * stride))

        # DSU for rows that are not completely filled.
        row_parent = array('i', range(n + 1))

        # Final answers, initially zero.
        ans = array('i', [0]) * (n * m)

        def find_col(x):
            root = x
            while parent[root] != root:
                root = parent[root]

            while parent[x] != x:
                nxt = parent[x]
                parent[x] = root
                x = nxt

            return root

        def find_row(x):
            root = x
            while row_parent[root] != root:
                root = row_parent[root]

            while row_parent[x] != x:
                nxt = row_parent[x]
                row_parent[x] = root
                x = nxt

            return root

        # Process earthquakes in reverse chronological order.
        for R, C, P in reversed(earthquakes):

            p_squared = P * P

            # Only rows within the earthquake's radius.
            r = find_row(R - P)
            last_row = R + P

            while r <= last_row:

                base = r * stride
                dx = r - R

                # Maximum horizontal distance in this row.
                dy = isqrt(p_squared - dx * dx)

                left = C - dy
                right = C + dy

                # Find the first unassigned column.
                x = find_col(base + left)

                while x <= base + right:

                    c = x - base

                    # Calculate the shock level.
                    dist_sq = dx * dx + (c - C) * (c - C)
                    ans[r * m + c] = p_squared - dist_sq + 1

                    # Remove this cell from future consideration.
                    parent[x] = find_col(x + 1)

                    x = parent[x]

                # If the entire row is assigned, skip it forever.
                if find_col(base) == base + m:
                    row_parent[r] = find_row(r + 1)

                # Move to the next non-completely-filled row.
                r = find_row(r + 1)

        # Prepare output.
        for r in range(n):
            start = r * m
            results.append(' '.join(map(str, ans[start:start + m])))

    sys.stdout.write('\n'.join(results))


if __name__ == "__main__":
    solve()
