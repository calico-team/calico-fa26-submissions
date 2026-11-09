from collections import deque

def build_trall(n, m, mappe):
    total = 2 * n * m
    ridg = [[] for _ in range(total)]

    def link_camp(a, b):
        ridg[a].append(b)
        ridg[b].append(a)

    for r in range(n):
        for c in range(m):
            tile = mappe[r][c]

            for mode in range(2):
                if tile != '.' and not (
                    (tile == 'B' and mode == 0) or
                    (tile == 'R' and mode == 1)
                ):
                    continue

                peak = 2 * (r * m + c) + mode

                if tile == '.':
                    link_camp(peak, peak ^ 1)

                if r + 1 < n:
                    nxt_tile = mappe[r + 1][c]

                    if nxt_tile == '.' or (
                        nxt_tile == 'B' and mode == 0
                    ) or (
                        nxt_tile == 'R' and mode == 1
                    ):
                        nxt = 2 * ((r + 1) * m + c) + mode
                        link_camp(peak, nxt)

                if c + 1 < m:
                    nxt_tile = mappe[r][c + 1]

                    if nxt_tile == '.' or (
                        nxt_tile == 'B' and mode == 0
                    ) or (
                        nxt_tile == 'R' and mode == 1
                    ):
                        nxt = 2 * (r * m + c + 1) + mode
                        link_camp(peak, nxt)

    return ridg


def check_hike(source, goals, limit, ridg):
    if source in goals:
        return True

    dist = {source: 0}
    camp = deque([source])

    while camp:
        peak = camp.popleft()
        current = dist[peak]

        if current >= limit:
            continue

        for nxt in ridg[peak]:
            if nxt not in dist:
                new_dist = current + 1

                if nxt in goals:
                    return True

                dist[nxt] = new_dist
                camp.append(nxt)

    return False


def solve(N: int, M: int, Q: int, G: list[str],
          start: list[tuple[int, int]],
          end: list[tuple[int, int]],
          K: list[int]) -> list[str]:

    ridg = build_trall(N, M, G)
    ans = []

    for i in range(Q):
        sr, sc = start[i]
        er, ec = end[i]

        source = 2 * (sr * M + sc)
        dest = 2 * (er * M + ec)

        if G[er][ec] == '.':
            goals = {dest, dest + 1}
        elif G[er][ec] == 'B':
            goals = {dest}
        else:
            goals = {dest + 1}

        possible = check_hike(
            source, goals, K[i], ridg
        )

        ans.append("YES" if possible else "NO")

    return ans


def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = []
        for _ in range(N):
            G.append(input())
        start, end, K = [], [], []
        for _ in range(Q):
            start_row, start_col, end_row, end_col, k = map(int, input().split())
            start.append((start_row, start_col))
            end.append((end_row, end_col))
            K.append(k)
        for s in solve(N, M, Q, G, start, end, K):
            print(s)


if __name__ == '__main__':
    main()
