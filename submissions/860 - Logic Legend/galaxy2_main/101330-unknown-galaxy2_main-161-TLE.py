# Source: https://usaco.guide/general/io
import sys
from collections import deque, defaultdict

def main():
    data = sys.stdin.buffer
    t_line = data.readline()
    if not t_line:
        return

    t = int(t_line)
    output = []

    for _ in range(t):
        n, m, q = map(int, data.readline().split())
        grid = [data.readline().decode().strip() for _ in range(n)]

        queries = []
        groups = defaultdict(list)

        for i in range(q):
            rs, cs, re, ce, k = map(int, data.readline().split())
            queries.append((rs, cs, re, ce, k))
            groups[(rs, cs)].append(i)

        answers = ["NO"] * q

        for (sr, sc), query_ids in groups.items():
            max_k = max(queries[i][4] for i in query_ids)

            start_cell = sr * m + sc
            start_state = start_cell * 2 + 1
            dist = [-1] * (n * m * 2)
            dist[start_state] = 0
            queue = deque([start_state])

            while queue:
                state = queue.popleft()
                d = dist[state]

                if d == max_k:
                    continue

                cell = state // 2
                mode = state % 2
                r = cell // m
                c = cell % m

                if grid[r][c] == ".":
                    next_state = cell * 2 + (1 - mode)
                    if dist[next_state] == -1:
                        dist[next_state] = d + 1
                        queue.append(next_state)

                for nr, nc in ((r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)):
                    if nr < 0 or nr >= n or nc < 0 or nc >= m:
                        continue

                    tile = grid[nr][nc]

                    if tile == "R" and mode != 0:
                        continue
                    if tile == "B" and mode != 1:
                        continue

                    next_cell = nr * m + nc
                    next_state = next_cell * 2 + mode

                    if dist[next_state] == -1:
                        dist[next_state] = d + 1
                        queue.append(next_state)

            for i in query_ids:
                _, _, er, ec, k = queries[i]
                end_state = (er * m + ec) * 2
                red_dist = dist[end_state]
                blue_dist = dist[end_state + 1]

                if (red_dist != -1 and red_dist <= k) or (blue_dist != -1 and blue_dist <= k):
                    answers[i] = "YES"

        output.extend(answers)

    sys.stdout.write("\n".join(output))

if __name__ == "__main__":
    main()
