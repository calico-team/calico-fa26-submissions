
import sys
from collections import deque, defaultdict

def solve():
    input = sys.stdin.readline

    t = int(input())

    for _ in range(t):
        n, m, q = map(int, input().split())
        grid = [input().strip() for _ in range(n)]

        queries = []
        groups = defaultdict(list)

        for i in range(q):
            sr, sc, er, ec, k = map(int, input().split())
            queries.append((er, ec, k))
            groups[(sr, sc)].append(i)

        answers = ["NO"] * q

        def bfs(sr, sc):
            dist = [[[-1, -1] for _ in range(m)] for _ in range(n)]
            queue = deque([(sr, sc, 0)])
            dist[sr][sc][0] = 0

            while queue:
                r, c, mode = queue.popleft()
                steps = dist[r][c][mode] + 1

                for dr, dc in ((0, 1), (0, -1), (1, 0), (-1, 0)):
                    nr, nc = r + dr, c + dc

                    if 0 <= nr < n and 0 <= nc < m:
                        tile = grid[nr][nc]

                        if tile == '.' or (tile == 'B' and mode == 0) or (tile == 'R' and mode == 1):
                            if dist[nr][nc][mode] == -1:
                                dist[nr][nc][mode] = steps
                                queue.append((nr, nc, mode))

                if grid[r][c] == '.' and dist[r][c][1 - mode] == -1:
                    dist[r][c][1 - mode] = steps
                    queue.append((r, c, 1 - mode))

            return dist

        for (sr, sc), ids in groups.items():
            dist = bfs(sr, sc)

            for i in ids:
                er, ec, k = queries[i]

                best = min(
                    d for d in dist[er][ec] if d != -1
                ) if any(d != -1 for d in dist[er][ec]) else float('inf')

                if best <= k:
                    answers[i] = "YES"

        print("\n".join(answers))


if __name__ == "__main__":
    solve()
