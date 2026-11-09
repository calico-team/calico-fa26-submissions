from math import isqrt
 
 
def solve(N, M, Q, earthquakes):
    grid = [[0] * M for _ in range(N)]
    nxt = [list(range(M + 1)) for _ in range(N)]
    for idx in range(Q - 1, -1, -1):
        X, Y, P = earthquakes[idx]
        PP = P * P
        for r in range(max(0, X - P), min(N - 1, X + P) + 1):
            dr = r - X
            w = isqrt(PP - dr * dr)
            lo = Y - w
            if lo < 0:
                lo = 0
            hi = Y + w
            if hi > M - 1:
                hi = M - 1
            nr = nxt[r]
            row = grid[r]
            base = PP - dr * dr + 1
            c = lo
            while True:
                root = c
                while nr[root] != root:
                    root = nr[root]
                while nr[c] != root:
                    nr[c], c = root, nr[c]
                c = root
                if c > hi:
                    break
                dc = c - Y
                row[c] = base - dc * dc
                nr[c] = c + 1
                c += 1
    return grid
 
 
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
 