def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]]) -> list[str]:
    size = N * M
    parent = list(range(size))
    rank = [0] * size

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def join(a, b):
        a, b = find(a), find(b)
        if a == b:
            return
        if rank[a] < rank[b]:
            a, b = b, a
        parent[b] = a
        if rank[a] == rank[b]:
            rank[a] += 1

    for r in range(N):
        for c in range(M):
            ch = G[r][c]
            pos = r * M + c
            if r and (ch == '.' or G[r-1][c] == '.' or ch == G[r-1][c]):
                join(pos, pos - M)
            if c and (ch == '.' or G[r][c-1] == '.' or ch == G[r][c-1]):
                join(pos, pos - 1)

    return ['YES' if find(r*M+c) == find(x*M+y) else 'NO'
            for (r, c), (x, y) in zip(start, end)]


def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = [input() for _ in range(N)]
        start, end = [], []
        for _ in range(Q):
            r, c, x, y = map(int, input().split())
            start.append((r, c))
            end.append((x, y))
        print('\n'.join(solve(N, M, Q, G, start, end)))


if __name__ == '__main__':
    main()
