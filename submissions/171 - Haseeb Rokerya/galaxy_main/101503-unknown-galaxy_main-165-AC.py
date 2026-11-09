# cook your dish here
from collections import deque
import sys


def solve():
    lines = [
        line.strip() for line in sys.stdin.read().splitlines() if line.strip()
    ]
    if not lines:
        return

    line_idx = 0
    first_parts = lines[0].split()

    # Check if the first line specifies T (number of test cases) or starts directly with N M Q
    if len(first_parts) == 1:
        num_cases = int(first_parts[0])
        line_idx = 1
    else:
        num_cases = 1

    results = []
    # Four cardinal directions: up, down, left, right
    cardinal_dirs = ((-1, 0), (1, 0), (0, -1), (0, 1))

    for _ in range(num_cases):
        if line_idx >= len(lines):
            break

        header = lines[line_idx].split()
        if len(header) != 3:
            break

        n, m, q = map(int, header)
        line_idx += 1

        if line_idx + n > len(lines):
            break

        grid = lines[line_idx : line_idx + n]
        line_idx += n

        # State index = mode * (n * m) + r * m + c
        # mode 0 = Blue Tile Mode, mode 1 = Red Tile Mode
        nm = n * m
        comp = [-1] * (2 * nm)
        comp_id = 0

        for mode in range(2):
            blocked = "R" if mode == 0 else "B"
            offset = mode * nm

            for r in range(n):
                for c in range(m):
                    start_state = offset + r * m + c
                    if comp[start_state] != -1 or grid[r][c] == blocked:
                        continue

                    comp[start_state] = comp_id
                    queue = deque([(mode, r, c)])

                    while queue:
                        curr_mode, cr, cc = queue.popleft()
                        curr_idx = curr_mode * nm + cr * m + cc

                        # 1. Spin action on a normal tile ('.') toggles between Blue and Red mode
                        if grid[cr][cc] == ".":
                            next_mode = 1 - curr_mode
                            spun_idx = next_mode * nm + cr * m + cc
                            if comp[spun_idx] == -1:
                                comp[spun_idx] = comp_id
                                queue.append((next_mode, cr, cc))

                        # 2. Walk up, down, left, or right to an adjacent active tile
                        curr_blocked = "R" if curr_mode == 0 else "B"
                        for dr, dc in cardinal_dirs:
                            nr, nc = cr + dr, cc + dc
                            if 0 <= nr < n and 0 <= nc < m:
                                if grid[nr][nc] != curr_blocked:
                                    nxt_idx = curr_mode * nm + nr * m + nc
                                    if comp[nxt_idx] == -1:
                                        comp[nxt_idx] = comp_id
                                        queue.append((curr_mode, nr, nc))

                    comp_id += 1

        # Answer queries for this test case
        for _ in range(q):
            if line_idx >= len(lines):
                break

            query_parts = lines[line_idx].split()
            if len(query_parts) != 4:
                break

            r1, c1, r2, c2 = map(int, query_parts)
            line_idx += 1

            # Ben always starts on a normal tile in Blue Tile Mode (mode 0)
            start_group = comp[r1 * m + c1]
            end_blue = comp[r2 * m + c2]
            end_red = comp[nm + r2 * m + c2]

            if start_group != -1 and (
                end_blue == start_group or end_red == start_group
            ):
                results.append("YES")
            else:
                results.append("NO")

    if results:
        sys.stdout.write("\n".join(results) + "\n")


if __name__ == "__main__":
    solve()
