import sys
import heapq


def solve():
    data = sys.stdin.read().split()
    if not data:
        return

    iterator = iter(data)
    T = int(next(iterator))

    out = []
    for _ in range(T):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))

        grid = [next(iterator) for _ in range(N)]

        queries = []
        for _ in range(Q):
            r1 = int(next(iterator))
            c1 = int(next(iterator))
            r2 = int(next(iterator))
            c2 = int(next(iterator))
            k = int(next(iterator))
            queries.append((r1, c1, r2, c2, k))

        for r1, c1, r2, c2, limit in queries:
            pq = [(0, r1, c1, 0)]
            dist = {(r1, c1, 0): 0}
            possible = False

            while pq:
                d, r, c, mode = heapq.heappop(pq)

                if r == r2 and c == c2:
                    if d <= limit:
                        possible = True
                    break

                if d > dist.get((r, c, mode), float('inf')):
                    continue
                if d > limit:
                    continue

                dr = [-1, 1, 0, 0]
                dc = [0, 0, -1, 1]

                for i in range(4):
                    nr, nc = r + dr[i], c + dc[i]
                    if 0 <= nr < N and 0 <= nc < M:
                        tile = grid[nr][nc]
                        active = False
                        if tile == '.':
                            active = True
                        elif mode == 0 and tile == 'B':
                            active = True
                        elif mode == 1 and tile == 'R':
                            active = True

                        if active:
                            nd = d + 1
                            if nd < dist.get((nr, nc, mode), float('inf')):
                                dist[(nr, nc, mode)] = nd
                                heapq.heappush(pq, (nd, nr, nc, mode))

                if grid[r][c] == '.':
                    nmode = 1 - mode
                    nd = d + 1
                    if nd < dist.get((r, c, nmode), float('inf')):
                        dist[(r, c, nmode)] = nd
                        heapq.heappush(pq, (nd, r, c, nmode))

            if possible:
                out.append("YES")
            else:
                out.append("NO")

    print('\n'.join(out))


if __name__ == '__main__':
    solve()