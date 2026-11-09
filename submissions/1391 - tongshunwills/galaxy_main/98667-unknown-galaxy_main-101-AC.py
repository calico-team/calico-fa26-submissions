def solve(N, M, Q, G, start, end):
    def ok(r, c, m):
        return G[r][c] == '.' or (G[r][c] == 'B' and m == 0) or (G[r][c] == 'R' and m == 1)

    seen = {}
    label = 0
    for r0 in range(N):
        for c0 in range(M):
            for m0 in range(2):
                if (r0, c0, m0) in seen or not ok(r0, c0, m0):
                    continue
                seen[(r0, c0, m0)] = label
                stack = [(r0, c0, m0)]
                while stack:
                    r, c, m = stack.pop()
                    nxt = [(r + 1, c, m), (r - 1, c, m), (r, c + 1, m), (r, c - 1, m)]
                    if G[r][c] == '.':
                        nxt.append((r, c, 1 - m))
                    for nr, nc, nm in nxt:
                        if 0 <= nr < N and 0 <= nc < M and ok(nr, nc, nm) and (nr, nc, nm) not in seen:
                            seen[(nr, nc, nm)] = label
                            stack.append((nr, nc, nm))
                label += 1

    ans = []
    for i in range(Q):
        sr, sc = start[i]
        er, ec = end[i]
        group = seen[(sr, sc, 0)]
        good = False
        for m in range(2):
            if ok(er, ec, m) and seen.get((er, ec, m)) == group:
                good = True
        ans.append("yes" if good else "no")
    return ans


def read():
    line = input().strip()
    while line == "":
        line = input().strip()
    return line


def main():
    T = int(read())
    for _ in range(T):
        N, M, Q = map(int, read().split())
        G = []
        for _ in range(N):
            G.append(read())
        start, end = [], []
        for _ in range(Q):
            a, b, c, d = map(int, read().split())
            start.append((a, b))
            end.append((c, d))
        for s in solve(N, M, Q, G, start, end):
            print(s)


if __name__ == '__main__':
    main()