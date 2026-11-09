import sys
from math import isqrt

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    iterator = iter(input_data)
    T = int(next(iterator))

    for _ in range(T):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))

        total = N * M
        grid = [0] * total

        parent = list(range(total + N))

        def find(index):
            root = index
            while parent[root] != root:
                root = parent[root]
            while parent[index] != index:
                next_index = parent[index]
                parent[index] = root
                index = next_index
            return root

        earthquakes = []

        for _ in range(Q):
            R = int(next(iterator))
            C = int(next(iterator))
            P = int(next(iterator))
            earthquakes.append((R, C, P))

        seen = set()
        for R, C, P in reversed(earthquakes):
            event = (R, C, P)
            if event in seen:
                continue
            seen.add(event)
            p_squared = P * P
            for dr in range(-P, P + 1):
                row = R + dr
                dr_squared = dr * dr
                radius = isqrt(p_squared - dr_squared)
                left = C - radius
                right = C + radius
                row_start = row * M
                row_end = row_start + M
                sentinel = total + row

                index = find(row_start + left)
                while index <= row_start + right:
                    dc = index - row_start - C
                    grid[index] = p_squared - dr_squared - dc * dc + 1
                    parent[index] = sentinel if index == row_end - 1 else index + 1
                    index = find(index)

        for r in range(N):
            row_slice = grid[r * M : (r + 1) * M]
            sys.stdout.write(" ".join(map(str, row_slice)) + "\n")

if __name__ == "__main__":
    solve()