from math import isqrt
def solve(N, M, Q, earthquakes):
    W = M + 1
    nxt = list(range(N * W))
    res = [0] * (N * M)
    wcache = {}
    for i in range(Q - 1, -1, -1):
        R, C, P = earthquakes[i]
        ws = wcache.get(P)
        if ws is None:
            ws = [isqrt(P * P - d * d) for d in range(P + 1)]
            wcache[P] = ws
        PP = P * P + 1
        for dr in range(-P, P + 1):
            d = dr if dr >= 0 else -dr
            w = ws[d]
            base = (R + dr) * W
            hi = base + C + w
            j = base + C - w
            x = j
            while nxt[x] != x:
                nxt[x] = nxt[nxt[x]]
                x = nxt[x]
            j = x
            if j > hi:
                continue
            rb = (R + dr) * M - base
            v0 = PP - dr * dr
            while j <= hi:
                dc = j - base - C
                res[j + rb] = v0 - dc * dc
                nxt[j] = j + 1
                x = j + 1
                while nxt[x] != x:
                    nxt[x] = nxt[nxt[x]]
                    x = nxt[x]
                j = x
    return [res[r * M:(r + 1) * M] for r in range(N)]
def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        earthquakes = []
        for i in range(Q):
            X, Y, P = map(int, input().split())
            earthquakes.append((X, Y, P))
        answer = solve(N, M, Q, earthquakes)
        for row in answer:
            print(' '.join(map(str, row)))
if __name__ == '__main__':
    main()
